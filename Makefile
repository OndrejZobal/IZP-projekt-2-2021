build: setcal.c
	gcc -std=c99 -Wall -Werror setcal.c -o setcal

run: build
	./setcal dummy.txt
