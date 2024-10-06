build:
	# gcc -std=c17 -Wall -Wextra -pedantic -g $(shell pkg-config --cflags sdl2) src/*.c $(shell pkg-config --libs sdl2) -lm -o renderer
	gcc -std=c17 -Wall -Wextra -pedantic $(shell pkg-config --cflags sdl2) src/*.c $(shell pkg-config --libs sdl2) -lm -o renderer

run:
	./renderer

clean:
	rm renderer

