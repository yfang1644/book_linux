#include <gtk/gtk.h>    /* gtk+ 组件头文件 */

/* 回调函数. 第二个参数指针 data 用于参数传递 */
static void hello(GtkWidget *widget,
                  gpointer   data)
{
    g_print("Hello World.\n");
}

static gboolean delete_event(GtkWidget *widget,
                             GdkEvent  *event,
                             gpointer   data )
{
    g_print ("delete event occurred.\n");

    /* "delete_event" 信号句柄返回 FALSE 时发出 "destroy" 信号,
     * 返回 TRUE 时不销毁窗口. */

    return FALSE;
}

/* 另一个回调函数. */
static void destroy(GtkWidget *widget,
                    gpointer   data)
{
    gtk_main_quit();
}

int main(int argc, char *argv[])
{
    /* 所有组件指针结构都是 GtkWidget. */
    GtkWidget *window;
    GtkWidget *button;

    /* 解析命令行参数. 所有 gtk 应用程序开始都要调用 gtk_init() */
    gtk_init (&argc, &argv);

    /* 创建顶层窗口. */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /* "window" 收到 "delete-event" 信号 (该信号由窗口管理器发出，
     * 通常是标题栏菜单的一个选项), 将该信号与 delete_event() 函数
     * 连接, 参数指针 NULL 被回调函数忽略. */
    g_signal_connect(window, "delete-event",
                     G_CALLBACK (delete_event), NULL);

    /* 将事件 "destroy" 连接到信号句柄.
     * 当调用函数 gtk_widget_destroy() 时或者在delete_event() 
     * 返回 FALSE 时触发"destroy" 事件. */
    g_signal_connect (window, "destroy",
                      G_CALLBACK (destroy), NULL);

    /* 设置窗口边界宽度 (像素点单位). */
    gtk_container_set_border_width(GTK_CONTAINER (window), 10);

    /* 创建按钮组件，标签"Hello World". */
    button = gtk_button_new_with_label("Hello World");

    /* 组件 "button" 的 "clicked" 信号与回调函数 hello() 连接，
     * 参数指针 NULL. */
    g_signal_connect(button, "clicked",
                     G_CALLBACK (hello), NULL);

    /* 组件"button" 的另一个回调函数, 调用 gtk_widget_destroy(window)
     * 销毁组件 "window". */
    g_signal_connect_swapped(button, "clicked",
                             G_CALLBACK(gtk_widget_destroy),
                             window);

    /* 将组件 "window" 作为容器，在容器里添加组件 "button". */ 
    gtk_container_add (GTK_CONTAINER (window), button);

    /* 显示组件. */
    gtk_widget_show(button);
    gtk_widget_show(window);

    /* 另一个显示组件的函数是 gtk_widget_show_all(window),
     * 将容器 "window" 内的所有组件一次性显示出来. */

    /* 组件创建完毕，所有 gtk 应用程序都会在最后调用 gtk_main(),
     * 进入事件响应和消息循环. */
    gtk_main();

    return 0;
}
