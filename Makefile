CC = gcc
CFLAGS = -std=c99 -O2 -fexceptions

OBJS = build/tgi.o build/gdi.o
TARGET = build/libtgi.a 

build/%.o: src/%.c
	$(CC) $< -c $(CFLAGS) -o $@
$(TARGET): $(OBJS)
	ar rcsv $(TARGET) $(OBJS)

all: $(TARGET)
	
.PHONY: build
build: all
	zip -q -r -j build/libtgi-x86_64.zip src/tgi.h src/tgihelper.h src/tgi.hpp build/libtgi.a
	zip -q -r -j build/libtgi-x86_64-devcpp-c-example.zip src/tgi.h src/tgihelper.h src/tgi.hpp build/libtgi.a projects/devcpp-c/HelloWorld.dev projects/devcpp-c/main.cpp
	zip -q -r -j build/libtgi-x86_64-devcpp-cpp-example.zip src/tgi.h src/tgihelper.h src/tgi.hpp build/libtgi.a projects/devcpp-cpp/HelloWorld.dev projects/devcpp-cpp/main.cpp

.PHONY: clean
clean:
	rm build/*

.PHONY: test
test: all
	gcc src/*.c test.c -o test -std=c99 -lgdi32 -lwinmm -lgdiplus -static -g && ./test