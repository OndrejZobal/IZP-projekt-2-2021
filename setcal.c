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

/**
 * Functions fills given array with string split by a space delimiter
 * @param string string to split by a delimiter.
 * @param array array to fill the split string with.
*/
void splitStringintoArray(char *string, char **array)
{
    int i = 0;
    char *strtoken = strtok(string, " ");
    while (strtoken != NULL)
    {
        array[i++] = strtoken;
        strtoken = strtok(NULL, " ");
    }
}

/**
 * Function creates a set object with specified params
 * @param id id corresponding to the textfile row
 * @param size size of the content array
 * @param contentString string to parse and fill the content array with 
*/
Set *setCreate(int id, int size, char *contentString)
{

    char *content[size];
    splitStringintoArray(contentString, content);

    Set *set = malloc(sizeof(Set));

    set->id = id;
    set->size = size;
    set->content = content;

    return set;
}

Subject parseLine(char *line, SubjectType type)
{
    Relation relation;
    Set set;

    Subject subjekt;

    if (line[0] == 'R')
    {
    }
    else if (line[0] == 'S')
    {
    }
    // Calls a lot of helper fucntions

    // The result is encapsulated in Subject.

    //return malloc(sizeof(Subject));
    return subjekt;
}

int setType(char character)
{
    if (character == 'S')
    {
        return SetType;
    }
    else if (character == 'R')
    {
        return RelationType;
    }
    else
    {
        return -1;
    }
}

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
    // count of spaces = count of strings = size of relation/set array
    int count = 0;
    // string to return growStrComvertToStr to
    char *string;

    SubjectType type = -1;
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
        if (character == 'S')
        {
            type = SetType;
        }
        else if (character == 'R')
        {
            type = RelationType;
        }
        else if (character == 'U' || character == 'C')
        {
            continue;
        }

        else if (character == '\n')
        {
            printf("FINAL: %s count: %d type: %d\n", gs->content, count, type);
            string = growStrConvertToStr(gs);
            printf("string from growstrconvert: %s\n", string);
            //parseLine(string, count);
            gs = growStrCreate();
            count = 0;
            type = -1;
        }
        else
        {
            if (character == ' ')
            {
                count++;
            }
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

    /*
    char contentString[] = "S a b c x";

    Set *testSet = setCreate(1, 5, contentString);
    printf("set id: %d set size: %d\n", testSet->id, testSet->size);
    for (int i = 0; i < 5; i++)
    {
        printf("set content string at index %d = %s\n", i, testSet->content[i]);
    }
*/
    // Parsing the content into structs.
    //parseFile(filePath); // TODO Dunno co to bude vracet to vymyslíme později
    return 0;
}
