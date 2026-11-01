# Tu Mundo Pet — GTK 4 + WebKitGTK 6. Desarrollado por Javiera Navarrete.
PKGS := gtk4 webkitgtk-6.0
CFLAGS := -O2 -Wall -Wextra -std=c11 $(shell pkg-config --cflags $(PKGS)) $(EXTRA_CFLAGS)
LIBS := $(shell pkg-config --libs $(PKGS))
tumundopet: tumundopet.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
clean:
	rm -f tumundopet
