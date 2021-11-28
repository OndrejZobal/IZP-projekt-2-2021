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

void syntaxCrash(){
    fprintf(stderr, "Invalid syntax in instruction file. The program cannot continue!");
    exit(1);
}

void argCrash(int line){
    fprintf(stderr, "Command missing arguments on line %d", line + 1);
    syntaxCrash();
}

void printBool(int boolean){
    if (boolean != 0 && boolean != 1){
        fprintf(stderr, "Boolean oparation resulted in nonbinary output: \"%d\"!\n", boolean);
        exit(1);
    }
    printf("%s\n", (boolean == 1) ? "true" : "false");
}
