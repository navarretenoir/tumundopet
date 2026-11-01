package cl.kotone.tumundopet;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowInsets;
import android.webkit.CookieManager;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceError;
import android.webkit.WebResourceRequest;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.FrameLayout;
import android.widget.ProgressBar;

/**
 * Tu Mundo Pet (Kotone 2026-10-31): la tienda real en su versión móvil dentro de un envoltorio nativo.
 * Carrito y sesión persisten (cookies + almacenamiento web); la compra (Jumpseller + pasarelas chilenas) queda dentro de
 * la app; WhatsApp, teléfono, correo y redes se abren en sus apps; sin conexión muestra una página propia.
 */
public class MainActivity extends Activity {
    static final String INICIO = "https://www.tiendatumundopet.cl/";
    /** Tienda en Shopify: checkout en el mismo dominio (/checkouts/…) + Shopify PCI; pagos con tarjeta, Mercado Pago, Flow
     *  (→ Webpay/Khipu/banco) y depósito. Las pasarelas terminan en páginas 3-D Secure de CADA banco, imposibles de listar:
     *  por eso TODA navegación web queda dentro de la app y sólo salen estas apps externas. */
    static final String[] FUERA = {"wa.me", "whatsapp.com", "instagram.com", "facebook.com", "fb.me", "m.me", "tiktok.com",
            "youtube.com", "youtu.be", "twitter.com", "x.com", "maps.google.", "google.com/maps", "goo.gl/maps", "maps.app.goo.gl",
            "waze.com", "play.google.com"};

    private WebView web;
    private ProgressBar barra;
    private boolean errorCarga = false;

    @SuppressLint("SetJavaScriptEnabled")
    @Override protected void onCreate(Bundle b) {
        super.onCreate(b);
        FrameLayout raiz = new FrameLayout(this);
        raiz.setBackgroundColor(Color.WHITE);
        web = new WebView(this);
        barra = new ProgressBar(this, null, android.R.attr.progressBarStyleHorizontal);
        barra.setMax(100);
        barra.setProgressTintList(android.content.res.ColorStateList.valueOf(0xFF046059));
        raiz.addView(web, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        raiz.addView(barra, new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, 8, Gravity.TOP));
        setContentView(raiz);

        // Android 15+ dibuja de borde a borde: se respeta el área de la barra de estado y de navegación.
        if (android.os.Build.VERSION.SDK_INT >= 30) {
            raiz.setOnApplyWindowInsetsListener((v, ins) -> {
                android.graphics.Insets i = ins.getInsets(WindowInsets.Type.systemBars() | WindowInsets.Type.displayCutout());
                v.setPadding(i.left, i.top, i.right, i.bottom);
                return WindowInsets.CONSUMED;
            });
        } else raiz.setFitsSystemWindows(true);               // Android 5–10: el sistema reserva las barras

        WebSettings s = web.getSettings();
        s.setJavaScriptEnabled(true);
        s.setDomStorageEnabled(true);
        s.setDatabaseEnabled(true);
        s.setLoadWithOverviewMode(true);
        s.setUseWideViewPort(true);
        s.setSupportZoom(false);
        s.setSupportMultipleWindows(false);                    // ventanas emergentes de pasarelas → misma vista
        s.setJavaScriptCanOpenWindowsAutomatically(true);
        s.setMediaPlaybackRequiresUserGesture(true);
        s.setUserAgentString(s.getUserAgentString() + " TuMundoPetApp/1.0");
        CookieManager.getInstance().setAcceptCookie(true);
        CookieManager.getInstance().setAcceptThirdPartyCookies(web, true);   // checkout y pasarelas

        web.setWebChromeClient(new WebChromeClient() {
            @Override public void onProgressChanged(WebView v, int p) {
                barra.setProgress(p);
                barra.setVisibility(p >= 100 ? View.GONE : View.VISIBLE);
            }
        });
        web.setWebViewClient(new WebViewClient() {
            @Override public boolean shouldOverrideUrlLoading(WebView v, WebResourceRequest r) {
                return abrirFuera(r.getUrl());
            }
            @Override public void onPageStarted(WebView v, String url, Bitmap f) { errorCarga = false; }
            @Override public void onReceivedError(WebView v, WebResourceRequest r, WebResourceError e) {
                if (r.isForMainFrame() && !errorCarga) {
                    errorCarga = true;
                    v.loadUrl("file:///android_asset/sin-conexion.html");
                }
            }
            @Override public void onPageFinished(WebView v, String url) {
                CookieManager.getInstance().flush();          // el carrito sobrevive a cerrar la app
            }
        });

        Uri entrada = getIntent() != null ? getIntent().getData() : null;
        if (b != null) web.restoreState(b);
        else web.loadUrl(entrada != null ? entrada.toString() : INICIO);
    }

    /** true = se abre fuera (otra app); false = se navega dentro. */
    private boolean abrirFuera(Uri u) {
        String esq = u.getScheme() == null ? "" : u.getScheme();
        if (esq.equals("file")) return false;
        if (esq.equals("reintentar")) { web.loadUrl(INICIO); return true; }
        if (esq.equals("http") || esq.equals("https")) {
            String url = u.toString();
            boolean fuera = false;
            for (String d : FUERA) if (url.contains(d)) { fuera = true; break; }
            if (!fuera) return false;                          // tienda, checkout, pasarelas y bancos: dentro
        }
        try {
            Intent i = esq.equals("intent") ? Intent.parseUri(u.toString(), Intent.URI_INTENT_SCHEME) : new Intent(Intent.ACTION_VIEW, u);
            i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivity(i);
        } catch (ActivityNotFoundException | java.net.URISyntaxException e) {
            if (esq.equals("intent")) {                            // sin la app destino: usar el enlace web de respaldo
                String alt = Uri.parse(u.toString()).getQueryParameter("browser_fallback_url");
                if (alt != null) web.loadUrl(alt);
            }
        }
        return true;
    }

    @Override protected void onNewIntent(Intent i) {
        super.onNewIntent(i);
        if (i.getData() != null) web.loadUrl(i.getData().toString());
    }

    @Override public void onBackPressed() {
        if (web.canGoBack() && !errorCarga) web.goBack();
        else super.onBackPressed();
    }

    @Override protected void onSaveInstanceState(Bundle b) { super.onSaveInstanceState(b); web.saveState(b); }
    @Override protected void onPause() { super.onPause(); CookieManager.getInstance().flush(); web.onPause(); }
    @Override protected void onResume() { super.onResume(); web.onResume(); }
}
