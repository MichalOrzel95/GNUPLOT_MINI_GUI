/*
 * PROJECT:     GNUPLOT MINI GUI
 * AUTHOR:      Michal Orzel
 * PLATFORM:    LINUX
 * GITHUB:      YES
 * FILES:       main.c,gplot.c,gplot.h
 */

#include <gtk/gtk.h>
#include "gplot.h"

int main(int argc,char *argv[])
{
    //Initialization
    gtk_init(&argc,&argv);

    //Creating builder object
    builder=gtk_builder_new();

    //Loading interface from GLADE
    gtk_builder_add_from_file(builder,PATH_TO_GLADE_FILE,NULL);

    //Linking signals and functions in GUI
    gtk_builder_connect_signals(builder,NULL);

    //Loading GUI components
    LoadGUIComponents();

    //Releasing builder object
    g_object_unref(builder);

    //Showing window
    gtk_widget_show((GtkWidget *)window);

    //Entering GUI loop
    gtk_main();

    return 0;
}