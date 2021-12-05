#ifndef setcal
#include <stdio.h>
#include <stdlib.h>
#endif

void memoryCrash(){
    fprintf(stderr, "Failed to allocate memory on the machine. The program cannot continue!\n");
    exit(1);
}

void ioCrash(char *path){
    if (path == NULL){
        fprintf(stderr, "Failed to manipulate with file!\n");
        exit(1);
    }

    fprintf(stderr, "Failed to manipulate with file: \"%s\"!\n", path);
    exit(1);
}

void syntaxCrash(){
    fprintf(stderr, "Invalid syntax in instruction file. The program cannot continue!\n");
    exit(1);
}

void argCrash(int index){
    fprintf(stderr, "Line %d has invalid parameters!", index + 1);
    syntaxCrash();
}

void nanCrash(int line, char* nan){
    fprintf(stderr, "On line %d there was supposted to be a line number, instead got \"%s\"!\n", line, nan);
    syntaxCrash();
}

void invalidCommandCrash(int index, char* command){
    fprintf(stderr, "\"%s\" is not a valid oparation operation for given inputs! Line %d!", command, index + 1);
    exit(1);
}

/**
 * Prints a boolean value as a word
 * @param boolean A boolean value to be printed */
void printBool(int boolean){
    if (boolean != 0 && boolean != 1){
        fprintf(stderr, "Boolean oparation resulted in nonbinary output: \"%d\"!\n", boolean);
        exit(1);
    }
    printf("%s\n", (boolean == 1) ? "true" : "false");
}

/**
 * Frees an array of strings
 * @param strings an array of strings
 * @param size the number of strings in the array.
 */
void freeString(char** strings, int size){
    for (int i = 0; i < size; i++){
        free(strings[i]);
    }
}
