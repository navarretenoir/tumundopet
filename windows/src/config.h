/* Tu Mundo Pet para Windows — configuración del anfitrión WebView2 (webhost.c). Desarrollado por Javiera Navarrete. */
#define APP_NOMBRE          L"Tu Mundo Pet"
#define APP_CLASE           L"TuMundoPetJavieraNavarrete"
#define APP_AGENTE          "TuMundoPet-Windows/1.0 (Javiera Navarrete)"
#define APP_INICIO          L"https://www.tiendatumundopet.cl/"
#define APP_CARPETA_DATOS   L"TuMundoPet"
#define APP_PUENTE          0
#define APP_VENTANAS_DENTRO 1      /* pasarelas de pago (Webpay, Mercado Pago, Flow, 3-D Secure) en la misma ventana */
#define APP_MENU_CONTEXTUAL TRUE
#define APP_ANCHO           520
#define APP_ALTO            900
#define APP_COLOR_FONDO     RGB(0xFF, 0xFF, 0xFF)
#define APP_ACERCA          L"Tu Mundo Pet 1.0 para Windows\n\nDesarrollado por Javiera Navarrete.\n\n" \
                            L"La tienda tiendatumundopet.cl en su propia ventana: el carrito y la sesión se conservan.\n" \
                            L"WhatsApp, redes sociales y mapas se abren en tu navegador. F5 recarga."
static const WCHAR *APP_FUERA[] = {L"wa.me", L"whatsapp.com", L"instagram.com", L"facebook.com", L"fb.me", L"m.me", L"tiktok.com",
    L"youtube.com", L"youtu.be", L"twitter.com", L"x.com/", L"maps.google.", L"google.com/maps", L"goo.gl/maps", L"maps.app.goo.gl",
    L"waze.com", L"play.google.com", NULL};
