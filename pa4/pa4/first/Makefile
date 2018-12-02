all: first

first: first.c first.h
	gcc -Wall -Werror -fsanitize=address -lm first.c first.h -o first

clean:
	rm -rf first
