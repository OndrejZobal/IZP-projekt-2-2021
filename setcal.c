/**
 * 2. IZP projekt 2021
 * @author Ondřej Zobal <xzobal01@stud.fit.vutbr.cz>
 * @author Petr Kolouch <xkolou05@stud.fit.vutbr.cz>
 * @author Vladimír Hucovič <xhucov00@stud.fit.vutbr.cz>
 */

#include <stdlib.h>
#include <string.h>
#include "./structs.h"
#include "./growstr.c"
#include "./growsubj.h"

// TODO UPDATE: Obsah univerza si budeme pamatovat a seznam položek budme používat jako slovník id, abychom si ušetřili porovnavani stringu.

Subject *parseLine(char *line) {
    // Calls a lot of helper fucntions

    // The result is encapsulated in Subject.

    return malloc(sizeof(Subject));
}

/**
 * Parses the intire file into subjects. Calls many helper functions
 * @param filepath path to file that will be parsed.
 * @param subjc The count of subjects in subjv
 * @param subjv Empty pointer for returning the subjects.
 */
void parseFile(char* filePath, int *subjc, Subject *subjv) {
    FILE *file = fopen(filePath, "r");

    subjv = malloc(sizeof(Subject)*1000); // Before we have generic grow type...
    // For every line:
    //  Read line char by char and store it in growstr.

    //  Convert Growstr into an array.

    //  Send the line into a processing fucntion. (Returns Subject)
    // parseLine();



    if (fclose(file) != 0) {
        printf("Sussy bakka cummy fucca!");
    }
}

/**
 * Functions returns the file from args.
 * @param argc count of arguments.
 * @param argv values of argumets.
 * @return Path to file from arg or NULL if no path was given
*/
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
    //parseFile(filePath); // TODO Dunno co to bude vracet to vymyslíme později
    return 0;
}

