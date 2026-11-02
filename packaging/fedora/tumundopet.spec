Name:           tumundopet
Version:        1.1.0
Release:        1%{?dist}
Summary:        Tienda Tu Mundo Pet: acuarismo y productos premium de mascotas
License:        GPL-3.0-or-later
URL:            https://github.com/navarretenoir/tumundopet
Source0:        https://github.com/navarretenoir/tumundopet/archive/refs/tags/v%{version}.tar.gz#/%{name}-%{version}.tar.gz
BuildRequires:  gcc make pkgconfig(gtk4) pkgconfig(webkitgtk-6.0)
BuildRequires:  desktop-file-utils
BuildRequires:  libappstream-glib

%description
The Tu Mundo Pet online store (Chile) in its own window: catalogue, cart and checkout with Chilean
payment gateways. Cart and session are kept; WhatsApp and social links open in the browser.
Interface in Spanish.

%prep
%autosetup -n tumundopet-%{version}

%build
make -C desktop EXTRA_CFLAGS="%{optflags} %{build_ldflags}"

%install
D=%{buildroot}
install -Dm755 desktop/tumundopet "%{buildroot}%{_prefix}/bin/tumundopet"
install -Dm644 linux/io.github.navarretenoir.TuMundoPet.desktop "%{buildroot}%{_prefix}/share/applications/io.github.navarretenoir.TuMundoPet.desktop"
install -Dm644 linux/io.github.navarretenoir.TuMundoPet.metainfo.xml "%{buildroot}%{_prefix}/share/metainfo/io.github.navarretenoir.TuMundoPet.metainfo.xml"
install -Dm644 linux/io.github.navarretenoir.TuMundoPet.svg "%{buildroot}%{_prefix}/share/icons/hicolor/scalable/apps/io.github.navarretenoir.TuMundoPet.svg"

%check
desktop-file-validate %{buildroot}%{_datadir}/applications/io.github.navarretenoir.TuMundoPet.desktop
appstream-util validate-relax --nonet %{buildroot}%{_datadir}/metainfo/io.github.navarretenoir.TuMundoPet.metainfo.xml || :

%files
%license LICENSE
%doc README.md
%{_bindir}/*

%{_datadir}/applications/io.github.navarretenoir.TuMundoPet.desktop
%{_datadir}/metainfo/io.github.navarretenoir.TuMundoPet.metainfo.xml
%{_datadir}/icons/hicolor/scalable/apps/io.github.navarretenoir.TuMundoPet.svg


%changelog
* Mon Nov 02 2026 Javiera Navarrete <navarrete.noir@gmail.com> - 1.1.0-1
- Botón flotante «TMP Calculadora» con ventana adaptativa (dosis según los litros del acuario)

* Sun Nov 01 2026 Javiera Navarrete <navarrete.noir@gmail.com> - 1.0.2-1
- Paquete inicial desde el código fuente.
