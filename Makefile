build: setcal.c
	gcc -std=c99 -Wall -Wextra setcal.c -o setcal -g

run: build
	./setcal dummy.txt
