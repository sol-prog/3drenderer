build:
	gcc -std=c17 -Wall -Wextra -pedantic -O2 $(shell pkg-config --cflags sdl2) src/*.c $(shell pkg-config --libs sdl2) -lm -o renderer

run:
	./renderer

clean:
	rm renderer

