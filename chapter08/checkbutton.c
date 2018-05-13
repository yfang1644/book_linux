/* checkbutton.c
 */

#include <gtk/gtk.h>

static void hello(GtkWidget *widget,
                   gpointer data)
{
    gboolean state;
    state = gtk_toggle_button_get_active((GtkToggleButton *)widget);
    if (state)
        g_print("check button is active.\n");
    else
        g_print("check button is in-active.\n");
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    button = gtk_check_button_new_with_mnemonic("_Press me");
    g_signal_connect(button, "toggled", G_CALLBACK(hello), NULL);
    gtk_container_add(GTK_CONTAINER(window), button);
    gtk_widget_show_all(window);
    
    gtk_main();

    return 0;
}
