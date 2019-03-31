CC=gcc
NAME=minify

dart: dart.l main.c
	flex -l dart.l
	$(CC) -Wall -o $(NAME) -lfl lex.yy.c

song: 
	flex -l song.l
	$(CC) -Wall -o min_song -lfl lex.yy.c


clean:
	rm lex.yy.c minify