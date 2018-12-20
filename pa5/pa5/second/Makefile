all: second

second: second.c second.h
	gcc -Wall -Werror -fsanitize=address second.c second.h -lm -o second

clean:
	rm -rf second
