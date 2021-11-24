build: setcal.c
	gcc -std=c99 -Wall -Wextra setcal.c -o setcal -g

growstr: growstr.c
	gcc -std=c99 -Wall -Wextra growstr.c -o growstr_test -g
	./growstr_test

run: build
	./setcal dummy.txt
