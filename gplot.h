//
// Created by orzelm on 27/07/17.
//

#ifndef GTK_TEST_GPLOT_H
#define GTK_TEST_GPLOT_H

#include <glib/gtypes.h>

//Path to .glade file
#define PATH_TO_GLADE_FILE "/home/orzelm/PROGRAMMING/GTK_TEST/cmake-build-release/test_glade.glade"
//Max number of signs in names
#define ARRAY_SIZE  20
//Max number of signs in path
#define PATH_SIZE   50

struct
{
    const gchar *file;
    const gchar *plot;
    const gchar *reso;
    const gchar *folder;
    const gchar *ttype;
    const gchar *ptitle;
    const gchar *style;
    const gchar *pxlab;
    const gchar *pylab;
}text;

//Global variables
FILE *plot; //File handler
guint contex_id;

//GLADE components
GtkWindow                  *window;
GtkApplicationWindow       *plot_window;
GtkDialog                  *dialog;
GtkDialog                  *dialog1;
GtkAboutDialog             *about_dialog;
GtkAboutDialog             *help_dialog;
GtkComboBoxText            *plot_resolution;
GtkButton                  *button;
GtkButton                  *author;
GtkButton                  *help;
GtkImage                   *image;
GtkFileChooser             *data_file_chooser;
GtkFileChooser             *plot_folder;
GtkEntry                   *plot_name;
GtkEntry                   *title;
GtkEntry                   *xlabel;
GtkEntry                   *ylabel;
GtkStatusbar               *statusbar;
GtkBuilder                 *builder;
GList                      *list;
GtkComboBoxText            *line_style;

//Functions prototypes
void LoadGUIComponents(void);
void on_generate_plot_clicked(void);
void on_ok_button_clicked(void);
void on_ok_button1_clicked(void);
void on_author_clicked(void);
void on_close_about_button_press_event(void);
void on_help_clicked(void);
void on_close_help_button_press_event(void);
int check_if_plot_was_generated(char *filename);
void on_data_file_chooser_file_set(void);
void on_plot_name_text_insert_text(void);
void on_folder_plot_file_set(void);

#endif //GTK_TEST_GPLOT_H
