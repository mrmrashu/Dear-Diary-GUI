#include <gtk/gtk.h>

static void
  activate ( GtkApplication *app, gpointer user_data)
  {

  }


int main(int argc, char *argv[]) {
    GtkApplication *app;


    app = gtk_application_new("org.ashu", G_APPLICATION_DEFAULT_FLAGS);
    

    return 0;
}