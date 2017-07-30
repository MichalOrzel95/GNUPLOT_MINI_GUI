//
// Created by orzelm on 30/07/17.
//

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "gplot.h"

//Loading components from GLADE to C-program
void LoadGUIComponents(void)
{
    window=GTK_WINDOW(gtk_builder_get_object(builder,"MainWindow"));
    plot_window=GTK_APPLICATION_WINDOW(gtk_builder_get_object(builder,"PlotWindow"));
    dialog=GTK_DIALOG(gtk_builder_get_object(builder,"dialog"));
    dialog1=GTK_DIALOG(gtk_builder_get_object(builder,"dialog1"));
    about_dialog=GTK_ABOUT_DIALOG(gtk_builder_get_object(builder,"AboutDialog"));
    help_dialog=GTK_ABOUT_DIALOG(gtk_builder_get_object(builder,"HelpDialog"));
    plot_resolution=GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder,"choose_resolution"));
    button=GTK_BUTTON(gtk_builder_get_object(builder,"generate_plot"));
    author=GTK_BUTTON(gtk_builder_get_object(builder,"author"));
    help=GTK_BUTTON(gtk_builder_get_object(builder,"help"));
    image=GTK_IMAGE(gtk_builder_get_object(builder,"ImagePlot"));
    data_file_chooser=GTK_FILE_CHOOSER(gtk_builder_get_object(builder,"data_file_chooser"));
    plot_folder=GTK_FILE_CHOOSER(gtk_builder_get_object(builder,"folder_plot"));
    plot_name=GTK_ENTRY(gtk_builder_get_object(builder,"plot_name_text"));
    title=GTK_ENTRY(gtk_builder_get_object(builder,"plot_title_text"));
    xlabel=GTK_ENTRY(gtk_builder_get_object(builder,"plot_xlabel_text"));
    ylabel=GTK_ENTRY(gtk_builder_get_object(builder,"plot_ylabel_text"));
}

//Pressing major button
void on_generate_plot_clicked(void)
{
    if((plot=popen("gnuplot","w"))==NULL)
    {
        exit(EXIT_FAILURE);
    }

    //Taking data from GUI
    text.file=gtk_file_chooser_get_filename(data_file_chooser);
    text.plot=gtk_entry_get_text(plot_name);
    text.reso=gtk_combo_box_text_get_active_text(plot_resolution);
    text.folder=gtk_file_chooser_get_current_folder(plot_folder);
    text.ptitle=gtk_entry_get_text(title);
    text.pxlab=gtk_entry_get_text(xlabel);
    text.pylab=gtk_entry_get_text(ylabel);

    //Sending data to GNUPLOT
    //Selecting terminal
    fprintf(plot,"set term png size %s\n",text.reso);
    //Selecting name for plot
    fprintf(plot,"set output \"%s/%s.png\"\n",text.folder,text.plot);
    //Selecting title
    fprintf(plot,"set title \"%s\"\n",text.ptitle);
    //Selecting x label
    fprintf(plot,"set xlabel \"%s\"\n",text.pxlab);
    //Selecting y label
    fprintf(plot,"set ylabel \"%s\"\n",text.pylab);
    //Selecting equal axes-length
    fprintf(plot,"set size ratio -1\n");
    //Generating plot
    fprintf(plot,"plot \"%s\" with lines\n",text.file);

    //Closing gnuplot
    pclose(plot);

    //Checking if all the necessary fields are filled
    size_t plot_length=strlen(text.plot);
    void *ptr=gtk_file_chooser_get_uri(data_file_chooser);
    void *ptr2=gtk_file_chooser_get_uri(plot_folder);

    if(plot_length==0 || ptr==NULL || ptr2==NULL)
    {
        gtk_dialog_run(dialog1);
    } else
    {
        char path_array[PATH_SIZE];
        strcpy(path_array,text.folder);
        strcat(path_array,"/");
        strcat(path_array,text.plot);
        strcat(path_array,".png");
        //Check if plot was generated
        gtk_dialog_run(check_if_plot_was_generated(path_array) ? dialog : dialog1);

        //Previewing generated plot
        gtk_image_set_from_file(image,path_array);
        gtk_widget_show((GtkWidget *)plot_window);
    }
}

//OK Button Success Clicked
void on_ok_button_clicked(void)
{
    gtk_widget_hide((GtkWidget *)dialog);
}

//OK Button Failure Clicked
void on_ok_button1_clicked(void)
{
    gtk_widget_hide((GtkWidget *)dialog1);
}

//AUTHOR Button Clicked
void on_author_clicked(void)
{
    gtk_dialog_run((GtkDialog *)about_dialog);
}

//Close in ABOUT Button Clicked
void on_close_about_button_press_event(void)
{
    gtk_widget_hide((GtkWidget *) about_dialog);
}

//HELP Button Clicked
void on_help_clicked(void)
{
    gtk_dialog_run((GtkDialog *)help_dialog);
}

//Close in  HELP Button Clicked
void on_close_help_button_press_event(void)
{
    gtk_widget_hide((GtkWidget *)help_dialog);
}

//Checking whether the plot was generated or not
int check_if_plot_was_generated(char *filename)
{
    struct stat buffer;
    return (stat (filename, &buffer) == 0);
}