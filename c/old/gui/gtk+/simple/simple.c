#include <gtk/gtk.h>
#include <stdio.h>

int main(int cli_argc, char **cli_argv){
	GtkWidget *window;
	gtk_init(&cli_argc, &cli_argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
	gtk_widget_show(window);
	g_signal_connect(
	   window,
	   "destroy",
	   G_CALLBACK(gtk_main_quit),
	   NULL
	);

	gtk_main();
	printf("I returend from 'gtk_main'!\n");
	return 0 ;
}
