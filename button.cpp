#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer user_data)
{
    g_print("Hello World\n");
}

static void activate(GtkApplication* app, gpointer user_data)
{
    auto window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Button");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    auto button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), button_box);

    auto button = gtk_button_new_with_label("Hello World");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), nullptr);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(button_box), button);

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
