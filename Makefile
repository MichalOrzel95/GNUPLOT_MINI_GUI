plotgui: main.c gplot.c
	gcc -o plotgui main.c gplot.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

install: plotgui
	install -m 0755 plotgui /usr/local/bin
