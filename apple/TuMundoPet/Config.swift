// Tu Mundo Pet para macOS e iOS — configuración del anfitrión. Desarrollado por Javiera Navarrete.
import Foundation
extension ConfigApp {
    static let actual = ConfigApp(
        nombre: "Tu Mundo Pet",
        inicio: .remoto(URL(string: "https://www.tiendatumundopet.cl/")!),
        puente: .ninguno,
        permitidos: [],
        fuera: ["wa.me", "whatsapp.com", "instagram.com", "facebook.com", "fb.me", "m.me", "tiktok.com", "youtube.com", "youtu.be",
                "twitter.com", "x.com/", "maps.google.", "google.com/maps", "goo.gl/maps", "maps.app.goo.gl", "waze.com", "maps.apple.com"],
        ventanasDentro: true,                 // pasarelas de pago y 3-D Secure en la misma vista
        activos: [])
}
