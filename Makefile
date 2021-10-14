run: main
	./main

main: main.c parser.c parser.h type.c type.h
	gcc -Wall main.c parser.c type.c -o ./main

clean:
	rm -f ./main
