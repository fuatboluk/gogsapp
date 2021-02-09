// Author: Fuat Bölük <mektup@fuatboluk.com.tr>


#include <gtk/gtk.h>
#include <webkit2/webkit2.h>


#define WIDTH  1024
#define HEIGHT 768


gint button_press(GtkWidget * widget, GdkEventButton * event, gpointer user_data)
{
    if (event->type == GDK_BUTTON_PRESS && event->button == 3)
    {
        return TRUE;
    } else {
        return FALSE;
    }
}


int main(int argc, char *argv[])
{
    GtkWidget * window, * scrolled, * event;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_window_maximize(GTK_WINDOW(window));
    gtk_window_set_title(GTK_WINDOW(window), "GogsApp");
    gtk_window_set_icon_from_file(GTK_WINDOW(window), "gogs-logo.png", NULL);

    scrolled = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_overlay_scrolling(GTK_SCROLLED_WINDOW(scrolled), 10);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled), WIDTH);
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled), HEIGHT);

    WebKitWebView * webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
    WebKitSettings * settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webView));

    WebKitWebContext * context = webkit_web_context_get_default();
    WebKitCookieManager * manager = webkit_web_context_get_cookie_manager(context);
    webkit_cookie_manager_set_accept_policy(manager, WEBKIT_COOKIE_POLICY_ACCEPT_ALWAYS);
    webkit_cookie_manager_set_persistent_storage(manager, "cookies.sqlite", WEBKIT_COOKIE_PERSISTENT_STORAGE_SQLITE);

    gtk_widget_set_events(GTK_WIDGET(webView), GDK_BUTTON_PRESS_MASK);
    webkit_settings_set_user_agent(settings, "Mozilla/5.0 (X11; Future OS; Linux x86_64; rv:66.0) Gecko/20100101 Firefox/66.0");

    WebKitWebsiteDataManager * data = webkit_website_data_manager_new("web_data");
    webkit_website_data_manager_get_cookie_manager(data);

    webkit_web_view_load_uri(webView, "http://localhost:3000/");

    gtk_container_add(GTK_CONTAINER(scrolled), GTK_WIDGET(webView));
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(scrolled));

    g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(webView), "button-press-event", G_CALLBACK(button_press), NULL);

    gtk_widget_grab_focus(GTK_WIDGET(webView));
    gtk_widget_set_size_request(window, WIDTH, HEIGHT);
    gtk_widget_show_all(window);

    gtk_main();
}


// End
