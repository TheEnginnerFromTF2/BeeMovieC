CC = gcc
CFLAGS = -lm
DIST_DIR = dist
TARGET = $(DIST_DIR)/beemovie.exe

all: $(TARGET)

$(TARGET): main.c resources.rc
	mkdir -p $(DIST_DIR)
	windres resources.rc -o resources.o
	$(CC) main.c resources.o -o $(TARGET) $(CFLAGS)

clean:
	rm -f resources.o
	rm -rf $(DIST_DIR)
