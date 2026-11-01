/* Tu Mundo Pet — la tienda (tiendatumundopet.cl, Shopify) en una ventana propia: GTK 4 + WebKitGTK 6.
 * Carrito y sesión persisten (almacenamiento propio); la compra y las pasarelas de pago (Webpay, Mercado Pago, Flow,
 * 3-D Secure de cada banco) quedan dentro; WhatsApp, redes y mapas se abren en el navegador del sistema.
 * Desarrollado por Javiera Navarrete. */
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <string.h>

#define INICIO "https://www.tiendatumundopet.cl/"
static const char *FUERA[] = {"wa.me", "whatsapp.com", "instagram.com", "facebook.com", "fb.me", "m.me", "tiktok.com",
    "youtube.com", "youtu.be", "twitter.com", "x.com/", "maps.google.", "google.com/maps", "goo.gl/maps", "maps.app.goo.gl",
    "waze.com", "play.google.com", NULL};

static gboolean es_fuera (const char *uri) {
    if (!uri) return FALSE;
    if (g_str_has_prefix (uri, "mailto:") || g_str_has_prefix (uri, "tel:") || g_str_has_prefix (uri, "whatsapp:")) return TRUE;
    if (!g_str_has_prefix (uri, "http")) return FALSE;
    for (int i = 0; FUERA[i]; i++) if (strstr (uri, FUERA[i])) return TRUE;
    return FALSE;
}

static gboolean on_decidir (WebKitWebView *v, WebKitPolicyDecision *d, WebKitPolicyDecisionType t, gpointer u) {
    (void) u;
    if (t != WEBKIT_POLICY_DECISION_TYPE_NAVIGATION_ACTION && t != WEBKIT_POLICY_DECISION_TYPE_NEW_WINDOW_ACTION) return FALSE;
    WebKitNavigationAction *a = webkit_navigation_policy_decision_get_navigation_action (WEBKIT_NAVIGATION_POLICY_DECISION (d));
    const char *uri = webkit_uri_request_get_uri (webkit_navigation_action_get_request (a));
    if (es_fuera (uri)) {
        GtkUriLauncher *l = gtk_uri_launcher_new (uri);
        gtk_uri_launcher_launch (l, GTK_WINDOW (gtk_widget_get_root (GTK_WIDGET (v))), NULL, NULL, NULL);
        g_object_unref (l);
        webkit_policy_decision_ignore (d);
        return TRUE;
    }
    if (t == WEBKIT_POLICY_DECISION_TYPE_NEW_WINDOW_ACTION) {   /* ventanas emergentes de pasarelas → misma vista */
        webkit_web_view_load_uri (v, uri);
        webkit_policy_decision_ignore (d);
        return TRUE;
    }
    return FALSE;
}

static gboolean on_fallo (WebKitWebView *v, WebKitLoadEvent e, const char *uri, GError *err, gpointer u) {
    (void) e; (void) u;
    if (g_error_matches (err, WEBKIT_NETWORK_ERROR, WEBKIT_NETWORK_ERROR_CANCELLED)) return FALSE;
    gchar *html = g_strdup_printf ("<html><body style='font-family:sans-serif;text-align:center;padding-top:20vh;color:#046059'>"
        "<h2>Sin conexión</h2><p>No se pudo abrir la tienda.</p><p><a href='%s' style='color:#046059'>Reintentar</a></p>"
        "</body></html>", uri ? uri : INICIO);
    webkit_web_view_load_alternate_html (v, html, uri, NULL);
    g_free (html);
    return TRUE;
}

static gboolean on_tecla (GtkEventControllerKey *k, guint kv, guint kc, GdkModifierType m, gpointer v) {
    (void) k; (void) kc;
    if (kv == GDK_KEY_F5 || ((m & GDK_CONTROL_MASK) && kv == GDK_KEY_r)) { webkit_web_view_reload (v); return TRUE; }
    if ((m & GDK_ALT_MASK) && kv == GDK_KEY_Left) { webkit_web_view_go_back (v); return TRUE; }
    if ((m & GDK_ALT_MASK) && kv == GDK_KEY_Home) { webkit_web_view_load_uri (v, INICIO); return TRUE; }
    return FALSE;
}

static void activar (GtkApplication *app, gpointer u) {
    (void) u;
    GtkWidget *win = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (win), "Tu Mundo Pet");
    gtk_window_set_default_size (GTK_WINDOW (win), 480, 860);
    /* sesión propia y persistente (carrito, inicio de sesión) en ~/.local/share/tumundopet */
    gchar *datos = g_build_filename (g_get_user_data_dir (), "tumundopet", NULL);
    gchar *cache = g_build_filename (g_get_user_cache_dir (), "tumundopet", NULL);
    WebKitNetworkSession *s = webkit_network_session_new (datos, cache);
    webkit_cookie_manager_set_persistent_storage (webkit_network_session_get_cookie_manager (s),
        g_build_filename (datos, "cookies.sqlite", NULL), WEBKIT_COOKIE_PERSISTENT_STORAGE_SQLITE);
    webkit_cookie_manager_set_accept_policy (webkit_network_session_get_cookie_manager (s), WEBKIT_COOKIE_POLICY_ACCEPT_ALWAYS);
    WebKitWebView *v = WEBKIT_WEB_VIEW (g_object_new (WEBKIT_TYPE_WEB_VIEW, "network-session", s, NULL));
    WebKitSettings *st = webkit_web_view_get_settings (v);
    webkit_settings_set_user_agent_with_application_details (st, "TuMundoPetApp", "1.0");
    webkit_settings_set_hardware_acceleration_policy (st, WEBKIT_HARDWARE_ACCELERATION_POLICY_NEVER);
    g_signal_connect (v, "decide-policy", G_CALLBACK (on_decidir), NULL);
    g_signal_connect (v, "load-failed", G_CALLBACK (on_fallo), NULL);
    GtkEventController *k = gtk_event_controller_key_new ();
    g_signal_connect (k, "key-pressed", G_CALLBACK (on_tecla), v);
    gtk_widget_add_controller (win, k);
    gtk_window_set_child (GTK_WINDOW (win), GTK_WIDGET (v));
    webkit_web_view_load_uri (v, INICIO);
    gtk_window_present (GTK_WINDOW (win));
    g_free (datos); g_free (cache);
}

int main (int argc, char **argv) {
    GtkApplication *app = gtk_application_new ("io.github.navarretenoir.TuMundoPet", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activar), NULL);
    int r = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return r;
}
