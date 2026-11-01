# Tu Mundo Pet

App de **[Tienda Tu Mundo Pet](https://www.tiendatumundopet.cl)**, tienda de acuarismo y productos premium de mascotas.
Abre la tienda en su propia ventana, con el catálogo, el carrito y la compra con los medios de pago chilenos
(tarjeta, Mercado Pago, Flow y transferencia). El carrito y la sesión se conservan entre usos; WhatsApp,
redes sociales, mapas, teléfono y correo se abren en la app correspondiente del sistema.

Sin publicidad ni rastreadores propios de la app.

**Desarrollado por Javiera Navarrete para tienda Tu Mundo Pet** · Código bajo licencia [GPL-3.0-or-later](LICENSE).
El nombre, el logo y el contenido de la tienda pertenecen a Tienda Tu Mundo Pet y no están cubiertos por la licencia del código.

## Plataformas

| Carpeta | Plataforma | Cómo se compila |
|---|---|---|
| `android/` | Android 5.0 → 16 | Android Studio o `./gradlew assembleRelease` (sin dependencias externas) |
| `desktop/` + `linux/` | Linux (GTK 4 + WebKitGTK 6) | `make -C desktop`; paquetes RPM/DEB/AppImage/Flatpak/Snap con `herramientas/linux-pkg/empaquetar.sh . todo` |
| `windows/` | Windows 10/11 (y 7/8.1 con WebView2) | `herramientas/winhost/construir.sh windows` (MinGW-w64 + SDK de WebView2 + NSIS); proyecto de Visual Studio en `visualstudio/` |
| `apple/` | macOS (Intel y Apple Silicon) e iOS/iPadOS | `xcodegen generate` dentro de `apple/` (también lo compila el flujo de GitHub Actions) |

Las piezas de terceros de los kits se bajan aparte: ver `herramientas/LEEME.md`.


---

## English

The app of **[Tienda Tu Mundo Pet](https://www.tiendatumundopet.cl)**, an aquarium and premium pet products store in Chile. It opens
the store in its own window, with catalog, cart and checkout using Chilean payment methods (card, Mercado Pago, Flow and bank
transfer). Cart and session persist between uses; WhatsApp, social networks, maps, phone and e-mail open in the corresponding system
app. No ads or trackers of its own.

Platforms: Android 5.0+, Linux (RPM, DEB, AppImage, Flatpak, Snap), Windows 10/11 (and 7/8.1 with WebView2), macOS (Intel and Apple
Silicon) and iOS/iPadOS. The interface is in Spanish (Chile).

**Developed by Javiera Navarrete for Tienda Tu Mundo Pet** · Code under [GPL-3.0-or-later](LICENSE). The store's name, logo and
content belong to Tienda Tu Mundo Pet and are not covered by the code license.
