#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./structs.h"
#include "./growstr.c"


// TODO Az bude struktura hotova, tak to bude vracet array ty struktury
void parseFile(char* filePath) {
    FILE *file = fopen(filePath, "r");


    if (fclose(file) != 0) {
        printf("Sussy bakka cummy fucca!");
}

char* readFilePath(int argc, char **argv) {
    if (argc < 1) {
        return NULL;
    }

    // We can add more checks here lol.
    return argv[1];
}

int main(int argc, char **argv) {
    // Getting the path to the file.
    char* filePath = readFilePath(argc, argv);
    if (filePath == NULL) {
        return 1;
    }

    // Parsing the content into structs.
    parseFile(filePath); // TODO Dunno co to bude vracet to vymyslíme později
    return 0;
}
