CC = gcc
CFLAGS = -std=c99 -O2 -fexceptions

OBJS = build/tgi.o build/gdi.o
TARGET = build/libtgi.a 

build/%.o: src/%.c
	$(CC) $< -c $(CFLAGS) -o $@
$(TARGET): $(OBJS)
	ar rcsv $(TARGET) $(OBJS)

all: $(TARGET)
	

.PHONY: clean
clean:
	rm build/*

.PHONY: test
test: all
	gcc test.c -o test -Lbuild -ltgi -std=c99 -lgdi32 -lwinmm -lgdiplus -static -s && ./test