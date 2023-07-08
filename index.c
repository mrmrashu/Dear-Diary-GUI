#include <gtk/gtk.h>

void on_process_quit(GtkWidget *widget, gpointer data) {
	gtk_main_quit();
}

void on_close_button(GtkWidget *widget, gpointer data) {
	GtkWidget *window = GTK_WIDGET(data);
    gtk_window_close(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	// Application Widgets


	// Main Window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Dear Diary - GTK+");

	// Headerbar
	GtkWidget *headerbar;
	headerbar = gtk_header_bar_new();
	gtk_widget_set_name(headerbar, "headerbar");
	gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "Dear Diary - GTK+");

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

    // Scrollwindow
    // windowbox(box)
    GtkWidget *windowbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), windowbox);

    //contentbox(box)
    GtkWidget *contentbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(windowbox), contentbox);

    gtk_style_context_add_class(gtk_widget_get_style_context(contentbox), "contentbox");

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_style_context_add_class(gtk_widget_get_style_context(scrolled_window), "scrolled_window");

    GtkWidget *text_view = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
    gtk_style_context_add_class(gtk_widget_get_style_context(text_view), "text_view");
    gtk_widget_set_name(text_view, "text_view");

    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "", -1);

    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    gtk_container_add(GTK_CONTAINER(contentbox), scrolled_window);
    // gtk_box_pack_start(GTK_BOX(scrolled_window), contentbox, TRUE, TRUE, 0);

    // headerbox(box)
    GtkWidget *headerbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), headerbox);


    // Exit Session Button
    GtkWidget *button;
    button = gtk_button_new_with_label("");
    gtk_widget_set_name(button, "close-button");
    gtk_style_context_add_class(gtk_widget_get_style_context(button), "close-button"); // close-button widget class

    gtk_box_pack_start(GTK_BOX(headerbox), button, TRUE, TRUE, 0);

    g_signal_connect(button, "clicked", G_CALLBACK(on_close_button), window);
	
	// Connect the "destroy" signal to the window close event
    g_signal_connect(window, "destroy", G_CALLBACK(on_process_quit), NULL);

	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}