CC=gcc
NAME=minify

build: scan.l main.c
	flex -l scan.l
	$(CC) -Wall -o $(NAME) -lfl lex.yy.c

clean:
	rm lex.yy.c minify