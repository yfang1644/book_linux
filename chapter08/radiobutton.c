/* radiobutton.c
 */

#include <gtk/gtk.h>

static void rbutton1(GtkWidget *widget, gpointer data)
{
    gboolean state;
    state = gtk_toggle_button_get_active((GtkToggleButton *)widget);
    if (state)
        g_print("Radio Button 1 is active.\n");
}

static void rbutton2(GtkWidget *widget, gpointer data)
{
    gboolean state ;
    state = gtk_toggle_button_get_active((GtkToggleButton *)widget);
    if (state)
        g_print("Radio Button 2 is active.\n");
}

static void rbutton3(GtkWidget *widget, gpointer data)
{
    gboolean state ;
    state = gtk_toggle_button_get_active((GtkToggleButton *)widget);
    if (state)
        g_print("Radio Button 3 is active.\n");
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    GtkWidget *radio1, *radio2, *radio3;
    GtkWidget *box;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    box = gtk_vbox_new(TRUE, 10);

    radio1 = gtk_radio_button_new_with_mnemonic(
        NULL, "Radio Button _One");
    radio2 = gtk_radio_button_new_with_mnemonic_from_widget(
        GTK_RADIO_BUTTON(radio1), "Radio Button _Two");
    radio3 = gtk_radio_button_new_with_mnemonic_from_widget (
        GTK_RADIO_BUTTON(radio1), "Radio Button T_hree");

    g_signal_connect(radio1, "toggled", G_CALLBACK(rbutton1), NULL);
    g_signal_connect(radio2, "toggled", G_CALLBACK(rbutton2), NULL);
    g_signal_connect(radio3, "toggled", G_CALLBACK(rbutton3), NULL);
    gtk_box_pack_start(GTK_BOX(box), radio1, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(box), radio2, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(box), radio3, TRUE, TRUE, 5);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
