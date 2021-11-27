#ifndef setcal
#include <stdio.h>
#include <stdlib.h>
#endif

void memoryCrash(){
    fprintf(stderr, "Failed to allocate memory on the machine. The program cannot continue!");
    exit(1);
}

void ioCrash(char *path){
    if (path == NULL){
        fprintf(stderr, "Failed to manipulate with file!\n");
    }

    fprintf(stderr, "Failed to manipulate with file: \"%s\"!\n", path);
    exit(1);
}
