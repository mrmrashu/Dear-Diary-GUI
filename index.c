#include <gtk/gtk.h>

void on_button_clicked(GtkWidget *widget, gpointer data) {
	gtk_main_quit();
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	// Application Widgets


	// Main Window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Dear Diary - v1.1");

	// Headerbar
	GtkWidget *headerbar;
	headerbar = gtk_header_bar_new();
	gtk_widget_set_name(headerbar, "headerbar");
	gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "Dear Diary - v1.1");

	// Setting headerbar as title bar of the window
	gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

	// Loading Stylesheet
	GtkCssProvider *provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, "style.css", NULL);

	// Style Context for overriding default styles
	GtkStyleContext *context = gtk_widget_get_style_context(headerbar);
	gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	// Redirecting Default Styles to Custom Styles
    const gchar *class_name = "entry-style";
    GtkStyleContext *context_entry = gtk_widget_get_style_context(window);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    gtk_style_context_add_class(context_entry, class_name);

    /*
		Containership
		window -> windowbox(box) -> box.start -> headerbar -> headerbox(box) -> box.end -> close-button
    */

    // windowbox(box)
    GtkWidget *windowbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), windowbox);

    // headerbox(box)
    GtkWidget *headerbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), headerbox);

    // Exit Session Button
    GtkWidget *button;
    button = gtk_button_new_with_label("");
    gtk_widget_set_name(button, "close-button");
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "close-button"); // close-button widget class

    gtk_box_pack_start(GTK_BOX(headerbox), button, TRUE, TRUE, 0);

    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), window);

	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}