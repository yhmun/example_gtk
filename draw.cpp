#include "common.h"

static cairo_surface_t *surface = nullptr;

static void close_window(void)
{
    g_print("close_window()\n");
    if (surface) {
        cairo_surface_destroy(surface);
        surface = nullptr;
    }
}

static void clear_surface(void)
{
    g_print("clear_surface()\n");
    auto cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_destroy(cr);
}

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    g_print("draw_cb()\n");
    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);
    return FALSE;
}

static void draw_brush(GtkWidget *widget, gdouble x, gdouble y)
{
    g_print("draw_brush()\n");
    auto cr = cairo_create(surface);
    cairo_rectangle(cr, x - 3, y - 3, 6, 6);
    cairo_fill(cr);
    cairo_destroy(cr);

    gtk_widget_queue_draw_area(widget, x - 3, y - 3, 6, 6);
}

static gboolean configure_event_cb(GtkWidget *widget, GdkEventConfigure *event, gpointer data)
{
    g_print("configure_event_cb()\n");
    if (surface) {
        cairo_surface_destroy(surface);
    }

    surface = gdk_window_create_similar_surface(gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR,
        gtk_widget_get_allocated_width(widget), gtk_widget_get_allocated_height(widget));
    if (!surface) {
        return FALSE;
    }
    clear_surface();
    return TRUE;
}

static gboolean button_press_event_cb(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    g_print("button_press_event_cb()\n");
    if (!surface) {
        return FALSE;
    }

    if (event->button == GDK_BUTTON_PRIMARY) {
        draw_brush(widget, event->x, event->y);
    } else if (event->button == GDK_BUTTON_SECONDARY) {
        clear_surface();
        gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

static gboolean motion_notify_event_cb(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
    g_print("motion_notify_event_cb()\n");
    if (!surface) {
        return FALSE;
    }

    if (event->state & GDK_BUTTON1_MASK) {
        draw_brush(widget, event->x, event->y);
    }
    return TRUE;
}

static void activate(GtkApplication* app, gpointer user_data)
{
    g_print("activate()\n");
    auto window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Drawing Area");
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), nullptr);

    gtk_container_set_border_width(GTK_CONTAINER(window), 8);

    auto frame = gtk_frame_new(nullptr);
    gtk_frame_set_shadow_type(GTK_FRAME(frame), GTK_SHADOW_IN);
    gtk_container_add(GTK_CONTAINER(window), frame);

    auto drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 100, 100);
    gtk_container_add(GTK_CONTAINER(frame), drawing_area);

    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_cb), nullptr);
    g_signal_connect(drawing_area, "configure-event", G_CALLBACK(configure_event_cb), nullptr);

    g_signal_connect(drawing_area, "motion-notify-event", G_CALLBACK(motion_notify_event_cb), nullptr);
    g_signal_connect(drawing_area, "button-press-event", G_CALLBACK(button_press_event_cb), nullptr);
    gtk_widget_set_events(drawing_area, gtk_widget_get_events(drawing_area) | GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    g_print("Start application..\n");

    auto app = gtk_application_new("org.gtk.example", app_flags);
    g_signal_connect(app, "activate", G_CALLBACK(activate), nullptr);

    auto status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    g_print("Exit..\n");
    return status;
}
