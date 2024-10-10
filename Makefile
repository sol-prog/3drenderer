build: 
	gcc -std=c17 -Wall -Wextra -pedantic -O2 $(shell pkg-config --cflags sdl2) src/*.c $(shell pkg-config --libs sdl2) -lm -o renderer

build_debug:
	gcc -std=c17 -Wall -Wextra -pedantic -g -fsanitize=address -O2 $(shell pkg-config --cflags sdl2) src/*.c $(shell pkg-config --libs sdl2) -lm -o renderer

run:
	./renderer

clean:
	rm renderer
