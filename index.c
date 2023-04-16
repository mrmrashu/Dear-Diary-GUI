
// Core Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// GUI Library
#include <gtk/gtk.h>

// Custom Libraries
#include "TimeString.h" // To Get the Current Time for Diary in a String


// Core Diary Functions ---------------------------


// Create a new Entry
void add_entry()
{
	FILE *fp; // file pointer
	int n = 3, i = 0;
	char **text;					   // 2D array
	text = malloc(n * sizeof(char *)); // Allocating only One block of memory for first line

	char terminate[] = "exit()\n"; // Termination array for exit diary writing
	g_print("\nStart Writting...");
	// Just Storing Time and a line break as default for every file ------>
	char Date_Time[50];
	sprintf(Date_Time, "\n%s\n@%s\nDear Diary,", DD_Str, TT_Str);
	g_print("\n%s\n", Date_Time);
	text[0] = malloc(10 * sizeof(char));
	text[0] = Date_Time;
	text[1] = malloc(2 * sizeof(char));
	text[1] = "\n";
	// --------------------------------------------------------------------<
	for (i = 2; i < n; i++)
	{
		text[i] = malloc(100 * sizeof(char));

		fgets(text[i], 100, stdin);

		if (strcmp(text[i], terminate) == 0)
		{
			break;
		}
		if (i >= n - 1)
		{
			n++;
			text = realloc(text, (n + 1) * sizeof(char *));
		}
	}
	if (text == NULL)
	{
		printf("Error: out of memory ...\n");
		exit(1);
	}

	fp = fopen(DD_Str, "a+");
	if (fp == NULL)
	{
		printf("Failed to Open the File, Please check the file name\n");
		exit(0);
	}
	for (int i = 0; i < n - 1; i++)
	{

		fputs(text[i], fp);
	}

	fclose(fp);
}
// Opening Diary
void open_Diary(void)
{
	char *file_name;
	printf("Enter the Date for Dairy Entry in the following format :  DD-MM-YY \n for eg:(23-4-2023) \n");
	scanf("%s", file_name);

	FILE *file = fopen(file_name, "r");
	if (file == NULL)
	{
		printf("%s\n", "No Dairy exist");
	}
	else
	{
		char c;
		while ((c = fgetc(file)) != EOF) //Read the file contents and print them.
		{
			printf("%c", c);
		}
	}
	fclose(file);
}
// Displaying Help Menu
void help_menu()
{
	g_print("\n\nDear-Diary GUI is a Simple & Elegant Diary Writting Software that provides an easy to use Interface.\nYou can support the development by forking the Github repository at 'https://github.com/mrmrashu/Dear-Diary-GUI'\n");
	g_print("\nYou can also launch GUI by using direct CLI commands :\n\t main <command>\n");
	g_print("\nAvailable Commands : \n");
	g_print("\t-new : Create a New Diary Entry\n\t-h : Open Help Menu\n\t-o : Open an old Diary Entry\n");
}

// Handling invalid arguments
void invalid_args()
{
	g_print("Invalid Argument(s), Please use '-h' for more information\n");
}


// GUI Elemental functions --------------------------

// Loading the CSS for GUI

static void load_css (void)
	{
		GtkCssProvider *provider;
		GdkDisplay *display;
		GdkScreen *screen;

		const gchar *css_style_file = "theme.css";
		GFile *css_fp = g_file_new_for_path(css_style_file);
		GError *error = 0;

		provider = gtk_css_provider_new();
		display = gdk_display_get_default();
		screen = gdk_display_get_default_screen(display);

		gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		gtk_css_provider_load_from_file (provider, css_fp, &error);

		 g_object_unref (provider);
	}


static void 
	print_hello ()
	{
		g_print("Button Clicked!\n");
	}

static void 
	activate ( GtkApplication *app,
				gpointer user_data)
	{
		GtkWidget
		*window,
		*grid, 
		*new_button,
		*help_button,
		*open_button,
		*ntextview,
		*entry,
		*label;

		GtkTextBuffer *nbuffer;

		gtk_init(NULL, NULL);
		load_css();

		// Create a new window and set it's title
		window = gtk_application_window_new(app);
		gtk_window_set_title (GTK_WINDOW (window), "Dear-Diary");
		gtk_window_set_default_size(GTK_WINDOW (window), 500, 200);
		gtk_container_set_border_width (GTK_CONTAINER (window), 10);

		// Constructing the Container that will pack the buttons
		grid = gtk_grid_new();

		// Pack the container in a window
		gtk_container_add (GTK_CONTAINER (window), grid);
		
		new_button = gtk_button_new_with_label ("New Entry");
		gtk_grid_attach (GTK_GRID (grid), new_button, 0, 1, 1, 1);
		// g_signal_connect (new_button, "clicked", G_CALLBACK (add_entry), NULL);

		open_button = gtk_button_new_with_label ("Open Entry");
		gtk_grid_attach(GTK_GRID(grid), open_button, 1,1,1,1);	

		help_button = gtk_button_new_with_label ("Help Menu");
		gtk_grid_attach(GTK_GRID(grid), help_button, 2,1,1,1);

		g_signal_connect(help_button, "clicked", G_CALLBACK(help_menu), NULL);
		/*
			Place the first button in the grid cell (0, 0), and make it fill
			just one cell horizontally and vertically (ie no spanning)
		*/

		label = gtk_label_new ("Dear Diary");
		gtk_grid_attach(GTK_GRID(grid), label, 1,0,1,1);
		gtk_widget_set_name(label, "title");

		ntextview = gtk_text_view_new();
		nbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (ntextview));

		gtk_text_buffer_set_text (nbuffer, "Dear Diary,\n", -1);

		gtk_grid_attach(GTK_GRID (grid), ntextview, 0,4,4,1);
		// gtk_widget_set_name(ntextview, "workOnFocus");

		/*entry = gtk_entry_new ();
		gtk_grid_attach (GTK_GRID (grid), entry, 0, 1, 2, 1);
		
		gtk_widget_set_name(entry, "workOnFocus");*/

		gtk_widget_show_all(window);
	}

int main(int argc, char ** argv)
{
	printf("starting...\n");
	GtkApplication *app;
	int ret;
	// Giving the application a unique ID to assosiate with
	app = gtk_application_new("org.ashu", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
	ret = g_application_run(G_APPLICATION(app), argc, argv);

	cairo_font_options_t *options = cairo_font_options_create();
	cairo_font_options_set_antialias(options, CAIRO_ANTIALIAS_SUBPIXEL);
	cairo_font_options_destroy(options);

	g_object_unref(app);


	// Diary CLI functionalities
	int tm_isdst; /* Daylight Savings Time flag */
	getTheTime();
	// printf("THE TIME IS : %s\n", TT_Str);
	// int i = 0;
	if (argc > 1)
	{
		printf("%d Argument(s) Recieved,\n", argc - 1); // Checking the Arguments
		for (int i = 1; i < argc; i++)
		{
			printf("Argument %d : %s\n", i, argv[i]);
			// Redirecting to help menu
			if (!strcmp(argv[i], "-h"))
			{
				help_menu();
			}
			// Redirecting to New Entry
			else if (!strcmp(argv[i], "-new"))
			{
				add_entry();
			}
			// Opening the diary
			else if (!strcmp(argv[i], "-o"))
			{
				open_Diary();
			}
			// Handling any other argument entered other than above
			else
			{
				invalid_args();
			}
		}
	}
	// Handling no arguments passed
	else
	{
		help_menu();
		printf("\n---------------------------------------------\nPlease use '-new' to create a new Diary Entry\n---------------------------------------------\n");
	}

	return ret;
}