/**
 * 2. IZP projekt 2021
 * @author Ondřej Zobal <xzobal01@stud.fit.vutbr.cz>
 * @author Petr Kolouch <xkolou05@stud.fit.vutbr.cz>
 * @author Vladimír Hucovič <xhucov00@stud.fit.vutbr.cz>
 */

#define setcal 1
#define tests 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./structs.h"
#include "./growstr.c"
#include "./growsubj.c"
#include "./utility.h"
#include "Commands/setCommandsUnary.h"
#include "Commands/isInSet.h"
#include "Commands/setCommandsBinary.h"
#include "Commands/areSetsEqual.h"
#include "Commands/commandWords.h"

// TODO UPDATE: Obsah univerza si budeme pamatovat a seznam položek budme používat jako slovník id, abychom si ušetřili porovnavani stringu.

/**
 * Functions fills given array with string split by a space delimiter
 * @param string string to split by a delimiter.
 * @param array array to fill the split string with.
*/
void splitStringintoArray(char* string, char** array)
{
    int i = 0;
    char* tempstr = calloc(strlen(string) + 1, sizeof(char));
    strcpy(tempstr, string);
    char* strtoken = strtok(tempstr, " ");
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
Set* setCreate(int id, int size, char* contentString, Universe* universe)
{
    int *intContent = malloc(sizeof(int) * size);
    char** content = malloc(sizeof(char*) * size);
    splitStringintoArray(contentString, content);
    for (int i = 0; i < universe->size; i++) {
    }
    for (int i = 0; i < size; i++) {
        int index = getItemIndex(universe, content[i]);
        if (index == -1) {
            fprintf(stderr, "Attempted to create a set with an element outside of the universe: %s.\n", content[i]);
            exit(1);
        }
        intContent[i] = index;
    }


    Set* set = malloc(sizeof(Set));

    set->id = id;
    set->size = size;
    set->content = intContent;

    /*
    for (int i = 0; i < size; i++) {
        printf("set content at index %d = %d\n", i, set->content[i]);
    }
    printf("*******\n");
    */
    return set;
}

Universe* universeCreate(int id, int size, char* contentString)
{
    char** content = malloc(sizeof(char*) * size);
    splitStringintoArray(contentString, content);

    Universe* universe = malloc(sizeof(Universe));

    universe->id = id;
    universe->size = size;
    universe->content = content;

    for (int i = 0; i < size; i++) {
        //printf("universe content at index %d = %s\n", i, universe->content[i]);
    }

    return universe;
}

int parseInt(char* str){
    return atoi(str);
}

Subject processCommand(int id, int size, char* contentString, Set* setResutl, Relation* relResult, GrowSubj* gsubj) {
    if (size < 2){
        argCrash(id);
    }
    char* content[size];
    Subject* subjects = gsubj->content;
    splitStringintoArray(contentString, content);

    if (!strcmp(content[0], CMD_EMPTY)){
        printBool(isEmpty(subjects[parseInt(content[1])-1].set_p));
        return createEmptySubject(id);
    }
    if (!strcmp(content[0], CMD_CARD)){
        printf("%d\n", card(subjects[parseInt(content[1])-1].set_p));
        return createEmptySubject(id);
    }
    if (!strcmp(content[0], CMD_COMPLEMENT)){
        return createSubjectFromSetPtr(getComplement(subjects[parseInt(content[1])-1].set_p, gsubj->content[0].universe_p->size));
    }

    if (size < 3){
        argCrash(id);
    }

    if (!strcmp(content[0], CMD_UNION)){
         return createSubjectFromSetPtr(setUnion(subjects[parseInt(content[1])-1].set_p, subjects[parseInt(content[2])-1].set_p));
    }
    if (!strcmp(content[0], CMD_INTERSECT)){
         return createSubjectFromSetPtr(intersect(subjects[parseInt(content[1])-1].set_p, subjects[parseInt(content[2])-1].set_p));
    }
    if (!strcmp(content[0], CMD_MINUS)){
         return createSubjectFromSetPtr(minus(subjects[parseInt(content[1])-1].set_p, subjects[parseInt(content[2])-1].set_p));
    }
    if (!strcmp(content[0], CMD_SUBSETEQ)){
        printBool(subseteq(subjects[parseInt(content[1])-1].set_p, subjects[parseInt(content[2])-1].set_p));
        return createEmptySubject(id);
    }
    if (!strcmp(content[0], CMD_SUBSET)){
        printBool(subset(subjects[parseInt(content[1])-1].set_p, subjects[parseInt(content[2])-1].set_p));
        return createEmptySubject(id);
    }
    if (!strcmp(content[0], CMD_EQUALS)){
        printBool(areSetsEqual(subjects[parseInt(content[1])-1].set_p, subjects[parseInt(content[2])-1].set_p));
        return createEmptySubject(id);
    }
}

Subject parseLine(int id, int size, char* contentString, SubjectType type, Universe* universe, GrowSubj* gsubj)
{
    Relation* relation = NULL;
    Set* set = NULL;
    Universe* newUniverse = NULL;
    Subject subj;

    switch(type){
        case RelationType:
            break;
        case SetType:
            set = setCreate(id, size, contentString, universe);
            break;
        case UniverseType:
            newUniverse = universeCreate(id, size, contentString);
            *universe = *newUniverse;
            // Only free the universe and keep the content.
            free(newUniverse);
            break;
        case CommandType:
            subj = processCommand(id, size, contentString, set, relation, gsubj);
                return subj;
    }

    Subject subject = {.id = id, .relation_p = relation, .set_p = set, .universe_p = universe, .subjectType = type};

    return subject;
}

SubjectType setType(char character)
{
    switch (character){
        case 'S':
            return SetType;
        case 'R':
            return RelationType;
        case 'U':
            return UniverseType;
        case 'C':
            return CommandType;
        default:
            fprintf(stderr, "\"%c\" is not a valid identifier!\n", character);
            syntaxCrash();
    }
}

/**
 * Parses the intire file into subjects. Calls many helper functions
 * @param filepath path to file that will be parsed.
 * @param subjc The count of subjects in subjv
 * @param subjv Empty pointer for returning the subjects.
 */
void parseFile(char* filePath)
{
    Universe* universe = malloc(sizeof(Universe));
    // current character returned from getc
    char character;
    // count of spaces = count of string = size of relation/set array
    int count = 0;
    int id = 0;
    // string to return growStrComvertToStr to
    char* string;

    SubjectType type;

    GrowStr* gstr;
    GrowSubj* gsubj = growSubjCreate();

    bool isFirstChar = true;

    FILE* file = fopen(filePath, "r");
    // read current charatcter while not at the end of the file
    while ((character = getc(file)) != EOF)
    {
        // only set SubjectType using fist character of the line
        if (isFirstChar)
        {
            gstr = growStrCreate();
            type = setType(character);
            isFirstChar = false;
            continue;
        }
        // if endline is reached
        // store the whole string into the string variable
        // call the parsline function with it
        // free the old references and create new growStr

        else if (character == '\n')
        {
            string = growStrConvertToStr(gstr);
            growSubjAdd(gsubj, parseLine(id, count, string, type, universe, gsubj));
            printSubject(*universe, gsubj->content[gsubj->length-1]);

            count = 0;
            id++;
            isFirstChar = true;
        }
        else
        {
            if (character == ' ')
            {
                count++;
            }
            growStrAdd(gstr, character);
            //printf("Element %c added\n", character);
            //printf("%s\n", gstr->content);
        }
    }
    //  Convert Growstr into an array.

    //  Send the line into a processing fucntion. (Returns Subject)
    // parseLine();

    if (fclose(file))
    {
        ioCrash(filePath);
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
        fprintf(stderr, "No path to file was provided!\n");
        return 1;
    }

    parseFile(filePath);
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
