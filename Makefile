CC = gcc
CFLAGS = -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
TARGET_APP = plotgui
SRC_FILES = main.c gplot.c

all: $(TARGET_APP)

$(TARGET_APP): $(SRC_FILES)
	$(CC) -o $@ $? $(CFLAGS)

.PHONY: clean
clean:
	rm $(TARGET_APP)
