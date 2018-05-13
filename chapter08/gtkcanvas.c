/* gtkcanvas.c
 */

#include <gtk/gtk.h>

/* Redraw the window */
gboolean expose_callback(GtkWidget *widget,
                         GdkEventExpose *e,
                         gpointer data)
{
    GdkGC *gc;
    GdkColor color;
    GdkFont *font;

    color.red = 0;
    color.blue=0xffff;
    color.green = 0;

    gc = gdk_gc_new(widget->window);
    gdk_gc_set_rgb_fg_color(gc, &color);
    gdk_draw_arc(widget->window,
                 gc,
                 TRUE,
                 20, 20,
                 widget->allocation.width-40,
                 widget->allocation.height-40,
                 0, 64*360);

    color.blue = 0;
    color.red = 0xffff;
    gdk_gc_set_rgb_fg_color(gc ,&color);
    font = gdk_font_load("lucidasans-bolditalic-14");
    gdk_draw_string(widget->window,
                    font,
                    gc,
                    20, 20, "hello");

    return TRUE;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *draw;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    draw = gtk_drawing_area_new();
    gtk_widget_set_size_request(draw, 400, 300);


    gtk_container_add(GTK_CONTAINER(window), draw);  
    g_signal_connect (G_OBJECT (draw), "expose-event",
                      G_CALLBACK (expose_callback), NULL);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
