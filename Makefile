CC=clang
CPPCHECK=C:\Program Files\Cppcheck\cppcheck.exe
CFLAGS=-Wall -Werror -Iinclude -Wno-pragma-pack
LDFLAGS=-L. -lSDL2
BINARY=gfx
BINARY_TESTS=gfx_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

gfx: main.o math.o rasterizer.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

tests.o: tests.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

math.o: math.c math.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

rasterizer.o: rasterizer.c math.h rasterizer.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^