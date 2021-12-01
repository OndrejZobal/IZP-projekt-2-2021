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
#include "utility.h"
#include "structs.h"
#include "growstr.c"
#include "growsubj.c"
#include "Commands/isInSet.h"
#include "Commands/areSetsEqual.h"
#include "Commands/setCommandsUnary.h"
#include "Commands/setCommandsBinary.h"
#include "Commands/commandWords.h"
#include "Commands/relationCommandsUnary.h"

 // TODO UPDATE: Obsah univerza si budeme pamatovat a seznam položek budme používat jako slovník id, abychom si ušetřili porovnavani stringu.

 /**
  * Functions fills given array with string split by a space delimiter
  * @param string string to split by a delimiter.
  * @param array array to fill the split string with.
 */
void splitStringintoArray(char* string, char** array, char* delimiter)
{
    int i = 0;
    char* tempstr = calloc(strlen(string) + 1, sizeof(char));
    strcpy(tempstr, string);
    char* strtoken = strtok(tempstr, delimiter);
    while (strtoken != NULL)
    {
        array[i++] = strtoken;

        strtoken = strtok(NULL, delimiter);
    }
    free(strtoken);
}

void removeChar(char* str, char charToRemove) {
    int i, j;
    int len = strlen(str);
    for (i = 0; i < len; i++)
    {
        if (str[i] == charToRemove)
        {
            for (j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }
            len--;
            i--;
        }
    }
    //printf("string after remove: %s\n", str);
}

void splitStringIntoPairs(char* string, char** array) {
    removeChar(string, '(');
    splitStringintoArray(string, array, ")");
}

Relation* relationCreate(int id, int size, char* contentString, Universe* universe) {
    char** content = malloc(sizeof(char*) * size);
    Pair* pairs = malloc(sizeof(Pair) * size);
    splitStringIntoPairs(contentString, content);

    for (int i = 0; i < size; i++) {
        char** helpArray = malloc(sizeof(char*) * 2);
        splitStringintoArray(content[i], helpArray, " ");
        int x = getItemIndex(universe, helpArray[0]);
        int y = getItemIndex(universe, helpArray[1]);
        if (x == -1 || y == -1) {
            fprintf(stderr, "Attempted to create a relation with an element outside of the universe: (%s %s)\n", helpArray[0], helpArray[1]);
            exit(1);
        }
        Pair pair = createPair(x, y);
        //printf("pair x: %d pair y: %d\n", pair.x, pair.y);
        pairs[i] = pair;
        free(helpArray); // FIXME Is this ok?? :flushed: Because I think so -O
    }

    Relation* relation = malloc(sizeof(Relation));
    relation->id = id;
    relation->size = size;
    relation->pairs = pairs;

    free(content);
    return relation;
}

/**
 * Function creates a set object with specified params
 * @param id id corresponding to the textfile row
 * @param size size of the content array
 * @param contentString string to parse and fill the content array with
*/
Set* setCreate(int id, int size, char* contentString, Universe* universe)
{
    // TODO: Need to check for duplicates in the set.
    int* intContent = malloc(sizeof(int) * size);
    char** content = malloc(sizeof(char*) * size);

    splitStringintoArray(contentString, content, " ");
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
    free(content);
    return set;
}

Universe* universeCreate(int id, int size, char* contentString)
{
    char** content = malloc(sizeof(char*) * size);

    splitStringintoArray(contentString, content, " ");

    Universe* universe = malloc(sizeof(Universe));


    universe->id = id;
    universe->size = size;
    universe->content = content;

    for (int i = 0; i < size; i++) {
        //printf("universe content at index %d = %s\n", i, universe->content[i]);
    }

    return universe;
}

int parseInt(char* str, bool* err) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] > '9' || str[i] < '0') {
            *err = true;
            return 0;
        }
    }
    err = false;
    return atoi(str);
}

// FIXME: pokud chybi parametr, funkce se dojebe
Subject processRelationCommand(int id, char* cmdWord, int  arg1, int arg2, Subject* subjects) {
    if (!strcmp(cmdWord, CMD_REFLEXIVE)) {
        printBool(isReflexive(subjects[arg1].relation_p, subjects[0].universe_p->size));
        return createEmptySubject(id);
    }
    if (!strcmp(cmdWord, CMD_SYMMETRIC)) {
        printBool(isSymmetric(subjects[arg1].relation_p));
        return createEmptySubject(id);
    }
    if (!strcmp(cmdWord, CMD_ANTISYMMETRIC)) {
        printBool(isAntisymmetric(subjects[arg1].relation_p));
        return createEmptySubject(id);
    }
    if (!strcmp(cmdWord, CMD_TRANSITIVE)) {
        printBool(isTransitive(subjects[arg1].relation_p));
        return createEmptySubject(id);
    }
    if (!strcmp(cmdWord, CMD_FUNCTION)) {
        printBool(isFunction(subjects[arg1].relation_p));
        return createEmptySubject(id);
    }

    if (!strcmp(cmdWord, CMD_DOMAIN)) {
        return createSubjectFromSetPtr(domain(subjects[arg1].relation_p));
    }
    if (!strcmp(cmdWord, CMD_CODOMAIN)) {
        return createSubjectFromSetPtr(codomain(subjects[arg1].relation_p));
    }
    // TODO
}

Subject processSetCommand(int id, char* cmdWord, int  arg1, int arg2, Subject* subjects) {
    if (!strcmp(cmdWord, CMD_EMPTY)) {
        printBool(isEmpty(subjects[arg1].set_p));
        return createEmptySubject(id);
    }
    if (!strcmp(cmdWord, CMD_CARD)) {
        return createEmptySubject(id);
    }
    if (!strcmp(cmdWord, CMD_COMPLEMENT)) {
        return createSubjectFromSetPtr(getComplement(subjects[arg1].set_p, subjects[0].universe_p->size));
    }

    // Processing commands with two inputs
    if (arg2 == -1 || (subjects[arg2].subjectType != SetType && subjects[arg2].subjectType != UniverseType)) {
        argCrash(id);
    }

    if (!strcmp(cmdWord, CMD_UNION)) {
        return createSubjectFromSetPtr(setUnion(subjects[arg1].set_p, subjects[arg2].set_p));
    }
    if (!strcmp(cmdWord, CMD_INTERSECT)) {
        return createSubjectFromSetPtr(intersect(subjects[arg1].set_p, subjects[arg2].set_p));
    }
    if (!strcmp(cmdWord, CMD_MINUS)) {
        return createSubjectFromSetPtr(minus(subjects[arg1].set_p, subjects[arg2].set_p));
    }
    if (!strcmp(cmdWord, CMD_SUBSETEQ)) {
        printBool(subseteq(subjects[arg1].set_p, subjects[arg2].set_p));
        return createEmptySubject(id);
    }
    if (!strcmp(cmdWord, CMD_SUBSET)) {
        printBool(subset(subjects[arg1].set_p, subjects[arg2].set_p));
        return createEmptySubject(id);
    }
    if (!strcmp(cmdWord, CMD_EQUALS)) {
        printBool(areSetsEqual(subjects[arg1].set_p, subjects[arg2].set_p));
        return createEmptySubject(id);
    }
}

Subject processCommand(int id, int size, char* contentString, GrowSubj* gsubj) {
    if (size < 2) {
        argCrash(id);
    }

    char* content[size];
    Subject* subjects = gsubj->content;
    splitStringintoArray(contentString, content, " ");
    char* cmdWord = content[0];
    bool conversionErr = false;
    int arg1 = parseInt(content[1], &conversionErr) - 1;
    if (conversionErr) {
        nanCrash(id, content[1]);
    }

    int arg2 = -1;
    if (size == 3) {
        arg2 = parseInt(content[2], &conversionErr) - 1;
        if (conversionErr) {
            nanCrash(id, content[2]);
        }
    }

    if (gsubj->content[arg1].subjectType == SetType || gsubj->content[arg1].subjectType == UniverseType) {
        return processSetCommand(id, cmdWord, arg1, arg2, subjects);
    }
    if (gsubj->content[arg1].subjectType == RelationType) {
        return processRelationCommand(id, cmdWord, arg1, arg2, subjects);
    }
    free(content);
}

Subject parseLine(int id, int size, char* contentString, SubjectType type, Universe* universe, GrowSubj* gsubj)
{
    Relation* relation = NULL;
    Set* set = NULL;
    Universe* newUniverse = NULL;
    Subject subj;

    switch (type) {
    case RelationType:
        relation = relationCreate(id, size / 2, contentString, universe);
        break;
    case SetType:
        set = setCreate(id, size, contentString, universe);
        break;
    case UniverseType:
        newUniverse = universeCreate(id, size, contentString);
        *universe = *newUniverse;
        set = setCreate(id, size, contentString, universe);
        // Only free the universe and keep the content.
        free(newUniverse);
        break;
    case CommandType:
        subj = processCommand(id, size, contentString, gsubj);
        return subj;
    }

    Subject subject = { .id = id, .relation_p = relation, .set_p = set, .universe_p = universe, .subjectType = type };

    return subject;
}

SubjectType setType(char character)
{
    switch (character) {
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
    bool seenSpace = false;

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
            seenSpace = false;
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
            printSubject(*universe, gsubj->content[gsubj->length - 1]);

            count = 0;
            id++;
            isFirstChar = true;
        }
        else
        {
            if (character == ' ')
            {
                seenSpace = true;
            }
            else if (seenSpace) {
                count++;
                seenSpace = false;
            }
            growStrAdd(gstr, character);
            //printf("Element %c added\n", character);
            //printf("%s\n", gstr->content);
        }
    }
    //  Convert Growstr into an array.

    //  Send the line into a processing fucntion. (Returns Subject)
    // parseLine();

    free(gsubj[0].content->set_p);
    destroyUniverse(universe);
    destroyGrowSubj(gsubj);

    if (fclose(file))
    {
        ioCrash(filePath);
    }
    return universe;
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
//parseFile(filePath); // TODO: Dunno co to bude vracet to vymyslíme později
    return 0;
}
