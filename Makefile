cc = gcc
cflags = -Wall -Wextra

all:
	$(cc) main.c system.c -o cfetch $(cflags)

run:
	./cfetch

clean:
	rm -f cfetch