#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer user_data)
{
    g_print("Hello World\n");
}

static void activate(GtkApplication* app, gpointer user_data)
{
    auto window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Grid");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    auto grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    auto button = gtk_button_new_with_label("Button 1");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), nullptr);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    button = gtk_button_new_with_label("Button 2");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), nullptr);
    gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

    button = gtk_button_new_with_label("Quit");
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);

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
