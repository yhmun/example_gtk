#include <gtk/gtk.h>

static void activate(GtkApplication* app, gpointer user_data)
{
    auto window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Simple");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    g_print("Start application..\n");

    auto app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), nullptr);

    auto status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    g_print("Exit..\n");
    return status;
}
