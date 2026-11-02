// Tu Mundo Pet para Android (Kotone · desarrollado por Javiera Navarrete). Sin dependencias externas.
plugins { id("com.android.application") version "9.4.1" }
android {
    namespace = "cl.kotone.tumundopet"
    compileSdk { version = release(36) { minorApiLevel = 1 } }
    defaultConfig {
        applicationId = "cl.kotone.tumundopet"
        minSdk = 21          // Android 5.0
        targetSdk = 36
        versionCode = 2
        versionName = "1.1.0"
    }
    sourceSets["main"].apply { manifest.srcFile("AndroidManifest.xml"); java.srcDirs("src"); res.srcDirs("res"); assets.srcDirs("assets") }
    buildTypes { release { isMinifyEnabled = false } }
    compileOptions { sourceCompatibility = JavaVersion.VERSION_17; targetCompatibility = JavaVersion.VERSION_17 }
    lint { abortOnError = false; checkOnly += setOf("NewApi", "InlinedApi"); xmlReport = true }
}
