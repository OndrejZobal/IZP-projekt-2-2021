build: setcal.c
	gcc -std=c99 -Wall -Wextra setcal.c -o setcal -g

release: setcal.c
	gcc -std=c99 -Wall -Wextra setcal.c -o setcal -static
	strip setcal

run: build
	./setcal dummy.txt
