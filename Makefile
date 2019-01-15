CC=clang
CPPCHECK=C:\Program Files\Cppcheck\cppcheck.exe
CFLAGS=-Wall -Iinclude -Wno-pragma-pack
LDFLAGS=-L. -lSDL2
BINARY=gfx
BINARY_TESTS=gfx_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

gfx: main.o aiv_math.o rasterizer.o	parser.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

tests.o: tests.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

aiv_math.o: aiv_math.c aiv_math.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

parser.o: parser.c parser.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

rasterizer.o: rasterizer.c aiv_math.h rasterizer.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^