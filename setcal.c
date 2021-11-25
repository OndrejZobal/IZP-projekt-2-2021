/**
 * 2. IZP projekt 2021
 * @author Ondřej Zobal <xzobal01@stud.fit.vutbr.cz>
 * @author Petr Kolouch <xkolou05@stud.fit.vutbr.cz>
 * @author Vladimír Hucovič <xhucov00@stud.fit.vutbr.cz>
 */

 // TODO: limit the input length

#include <stdlib.h>
#include <string.h>
#include "./structs.h"
#include "./growstr.c"
#include "./growsubj.c"

// TODO UPDATE: Obsah univerza si budeme pamatovat a seznam položek budme používat jako slovník id, abychom si ušetřili porovnavani stringu.

/**
 * Functions fills given array with string split by a space delimiter
 * @param string string to split by a delimiter.
 * @param array array to fill the split string with.
*/
void splitStringintoArray(char* string, char** array, SubjectType type)
{
    int i = 0;
    char* strtoken = strtok(string, " ");
    while (strtoken != NULL)
    {
        if (type == SetType) {
            array[i++] = (int)strtoken;
        }
        else {
            array[i++] = strtoken;
        }
        strtoken = strtok(NULL, " ");
    }
}


/**
 * Function creates a set object with specified params
 * @param id id corresponding to the textfile row
 * @param size size of the content array
 * @param contentString string to parse and fill the content array with
*/
Set* setCreate(int id, int size, char* contentString)
{

    int content[size];
    splitStringintoArray(contentString, content, SetType);

    Set* set = malloc(sizeof(Set));

    set->id = id;
    set->size = size;
    set->content = content;

    for (int i = 0; i < size; i++) {
        printf("set content at index %d = %d\n", i, set->content[i]);
    }

    return set;
}

Universe* universeCreate(int id, int size, char* contentString)
{

    char* content[size];
    splitStringintoArray(contentString, content, UniverseType);

    Universe* universe = malloc(sizeof(Universe));

    universe->id = id;
    universe->size = size;
    universe->content = content;

    for (int i = 0; i < size; i++) {
        printf("universe content at index %d = %s\n", i, universe->content[i]);
    }

    return universe;
}

Subject* parseLine(int id, int size, char* contentString, SubjectType type)
{
    Relation* relation;
    Set* set;
    Universe* universe;

    if (type == RelationType)
    {
        //relation = relationCreate();
    }
    else if (type == SetType)
    {
        set = setCreate(id, size, contentString);
    }
    else if (type == UniverseType)
    {
        universe = universeCreate(id, size, contentString);
    }

    Subject* subjekt = malloc(sizeof(Subject));
    subjekt->id = id;
    subjekt->relation_p = relation;
    subjekt->set_p = set;
    subjekt->universe_p = universe;
    subjekt->subjectType = type;

    // Calls a lot of helper fucntions

    // The result is encapsulated in Subject.

    //return malloc(sizeof(Subject));
    printf("id: %d subject type: %d\n", subjekt->id, subjekt->subjectType);
    return subjekt;
}

SubjectType setType(char character)
{
    if (character == 'S')
    {
        return SetType;
    }
    else if (character == 'R')
    {
        return RelationType;
    }
    else if (character == 'U')
    {
        return UniverseType;
    }
    return -1;
}

/**
 * Parses the intire file into subjects. Calls many helper functions
 * @param filepath path to file that will be parsed.
 * @param subjc The count of subjects in subjv
 * @param subjv Empty pointer for returning the subjects.
 */
void parseFile(char* filePath, int* subjc, Subject* subjv)
{

    FILE* file = fopen(filePath, "r");
    // current character returned from getc
    char character;
    // count of spaces = count of strings = size of relation/set array
    int count = 0;
    int id = 0;
    // string to return growStrComvertToStr to
    char* string;

    SubjectType type = -1;
    subjv = malloc(sizeof(Subject) * 1000); // Before we have generic grow type...
                                            // For every line:
                                            //  Read line char by char and store it in growstr.
    GrowStr* gs = growStrCreate();
    printf("Grow string created!\n");
    int isFirstChar = 1;

    // read current charatcter while not at the end of the file
    while ((character = getc(file)) != EOF)
    {
        // only set SubjectType using fist character of the line
        if (isFirstChar)
        {
            type = setType(character);
            if (type == -1)
            {
                break;
            }
            isFirstChar = 0;
            continue;
        }
        // if endline is reached
        // store the whole string into the string variable
        // call the parsline function with it
        // free the old references and create new growStr

        else if (character == '\n')
        {
            printf("FINAL: %s count: %d type: %d\n", gs->content, count, type);
            string = growStrConvertToStr(gs);
            printf("string from growstrconvert: %s\n", string);
            parseLine(id, count, string, type);
            gs = growStrCreate();
            count = 0;
            type = -1;
            id++;
            isFirstChar = 1;
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
char* readFilePath(int argc, char** argv)
{
    if (argc < 1)
    {
        return NULL;
    }

    // We can add more checks here lol.
    return argv[1];
}

int main(int argc, char** argv)
{
    // Getting the path to the file.
    char* filePath = readFilePath(argc, argv);
    if (filePath == NULL)
    {
        return 1;
    }

    Subject subjekt;
    int count = 5;
    int* count_p;
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
