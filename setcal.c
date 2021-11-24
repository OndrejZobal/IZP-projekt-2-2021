/**
 * 2. IZP projekt 2021
 * @author Ondřej Zobal <xzobal01@stud.fit.vutbr.cz>
 * @author Petr Kolouch <xkolou05@stud.fit.vutbr.cz>
 * @author Vladimiír Hucovič <xhucov00@stud.fit.vutbr.cz>
 */

#include <stdlib.h>
#include <string.h>
#include "./structs.h"
#include "./growstr.c"

// TODO UPDATE: Obsah univerza si budeme pamatovat a seznam položek budme používat jako slovník id, abychom si ušetřili porovnavani stringu.
/*
Subject parseLine(char *line)
{
    Subject subjekt = 
    // Calls a lot of helper fucntions

    // The result is encapsulated in Subject.

    //return malloc(sizeof(Subject));
}
*/

/**
 * Parses the intire file into subjects. Calls many helper functions
 * @param filepath path to file that will be parsed.
 * @param subjc The count of subjects in subjv
 * @param subjv Empty pointer for returning the subjects.
 */
void parseFile(char *filePath, int *subjc, Subject *subjv)
{

    FILE *file = fopen(filePath, "r");
    // current character returned from getc
    char character;
    // string to return growStrComvertToStr to
    char *string;
    subjv = malloc(sizeof(Subject) * 1000); // Before we have generic grow type...
                                            // For every line:
                                            //  Read line char by char and store it in growstr.
    GrowStr *gs = growStrCreate();
    printf("Grow string created!\n");

    // read current charatcter while not at the end of the file
    while ((character = getc(file)) != EOF)
    {
        // if endline is reached
        // store the whole string into the string variable
        // call the parsline function with it
        // free the old references and create new growStr
        if (character == '\n')
        {
            printf("FINAL: %s\n", gs->content);
            string = growStrConvertToStr(gs);
            parseLine(string);
            gs = growStrCreate();
        }
        else
        {
            growStrAdd(gs, character);
            //printf("Element %c added\n", character);
            //printf("%s\n", gs->content);
        }
    }
    //  Convert Growstr into an array.

    //  Send the line into a processing fucntion. (Returns Subject)
    // parseLine();

    if (fclose(file) != 0)
    {
        printf("Sussy bakka cummy fucca!");
    }
}

/**
 * Functions returns the file from args.
 * @param argc count of arguments.
 * @param argv values of argumets.
 * @return Path to file from arg or NULL if no path was given
*/
char *readFilePath(int argc, char **argv)
{
    if (argc < 1)
    {
        return NULL;
    }

    // We can add more checks here lol.
    return argv[1];
}

int main(int argc, char **argv)
{
    // Getting the path to the file.
    char *filePath = readFilePath(argc, argv);
    if (filePath == NULL)
    {
        return 1;
    }

    Subject subjekt;
    int count = 5;
    int *count_p;
    count_p = &count;

    parseFile(filePath, count_p, &subjekt);

    // Parsing the content into structs.
    //parseFile(filePath); // TODO Dunno co to bude vracet to vymyslíme později
    return 0;
}
