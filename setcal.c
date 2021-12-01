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
#include <time.h>
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
 * this function splits string into an array by a delimimter
 * @param string string to be splitted
 * @param array array to be filled with
 * @param delimiter string that tells which character should split the string
 * @return void
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

/**
 * this function removes a specific char from a string
 * @param string string to remove the chars from
 * @param charToRemove char to be removed
 * @return void
 */

void removeChar(char* str, char charToRemove) {
    int i;
    int j;
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
}

/**
 * splits string into array, which will then make pairs
 * @param string string to be split into pairs
 * @param array to which the string will be splitted
 * @return created set with specified values
 */

void splitStringIntoPairs(char* string, char** array) {
    removeChar(string, '(');
    splitStringintoArray(string, array, ")");
}

/**
 * this function creates a relation with specified values
 * @param id the number of the row from the file
 * @param size size = how many columns does the line have == values
 * @param contentString string with content, that will be parsed to values
 * @param universe universe the values are related to
 * @return created set with specified values
 */

int hasMoreThanMaxSize(char* string) {
    //FIXME: add max const
    if (strlen(string) > 30) {
        return 1;
    }
    return 0;
}

Relation* relationCreate(int id, int size, char* contentString, Universe* universe) {
    char** content = malloc(sizeof(char*) * size);
    Pair* pairs = malloc(sizeof(Pair) * size);
    splitStringIntoPairs(contentString, content);

    for (int i = 0; i < size; i++) {
        if (hasMoreThanMaxSize(content[i])) {
            fprintf(stderr, "value exceeds the max allowed value!\n");
            exit(1);
        }
    }

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

    for (int i = 0; i < size; i++) {
        Pair helpPair = pairs[i];
        int numberOfRepeats = 0;

        for (int j = 0; j < size; j++) {
            if (pairs[j].x == helpPair.x && pairs[j].y == helpPair.y) {
                numberOfRepeats++;
            }
            if (numberOfRepeats > 1) {
                fprintf(stderr, "pair (%d %d) appears more than once in the relation!\n", helpPair.x, helpPair.y);
                exit(1);
            }
        }
    }

    Relation* relation = malloc(sizeof(Relation));
    relation->id = id;
    relation->size = size;
    relation->pairs = pairs;

    free(content);
    return relation;
}

/**
 * this function creates a set with specified values
 * @param id the number of the row from the file
 * @param size size = how many columns does the line have == values
 * @param contentString string with content, that will be parsed to values
 * @param universe universe the values are related to
 * @return created set with specified values
 */

Set* setCreate(int id, int size, char* contentString, Universe* universe)
{
    // TODO: Need to check for duplicates in the set.
    int* intContent = malloc(sizeof(int) * size);
    char** content = malloc(sizeof(char*) * size);

    splitStringintoArray(contentString, content, " ");

    for (int i = 0; i < size; i++) {
        if (hasMoreThanMaxSize(content[i])) {
            fprintf(stderr, "value exceeds the max allowed value!\n");
            exit(1);
        }
    }

    for (int i = 0; i < size; i++) {
        int index = getItemIndex(universe, content[i]);
        if (index == -1) {
            fprintf(stderr, "Attempted to create a set with an element outside of the universe: %s.\n", content[i]);
            exit(1);
        }
        intContent[i] = index;
    }

    for (int i = 0; i < size; i++) {
        int helpIntContent = intContent[i];
        int numberOfRepeats = 0;
        for (int j = 0; j < size; j++) {
            if (intContent[j] == helpIntContent) {
                numberOfRepeats++;
            }
            if (numberOfRepeats > 1) {
                fprintf(stderr, "%d appears more than once in the set!\n", helpIntContent);
                exit(1);
            }
        }
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

/**
 * this function creates a universe with specified values
 * @param id the number of the row from the file
 * @param size size = how many columns does the line have == values
 * @param contentString string with content, that will be parsed to values
 * @return created universe with specified values
 */

Universe* universeCreate(int id, int size, char* contentString)
{
    char** content = malloc(sizeof(char*) * size);

    splitStringintoArray(contentString, content, " ");

    for (int i = 0; i < size; i++) {
        if (hasMoreThanMaxSize(content[i])) {
            fprintf(stderr, "value exceeds the max allowed value!\n");
            exit(1);
        }
    }

    Universe* universe = malloc(sizeof(Universe));


    universe->id = id;
    universe->size = size;
    universe->content = content;

    for (int i = 0; i < size; i++) {
        //printf("universe content at index %d = %s\n", i, universe->content[i]);
    }

    return universe;
}



/**
 * parses string into number if possible
 * @param str string to be parsed
 * @param err variable to set the error to
 * @return parsed string to number
 */

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

Subject processRelationCommand(int id, char* cmdWord, int  arg1, int arg2, int arg3, Subject* subjects) {

    if (arg2 == -1 && arg3 == -1) {
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

        if (!strcmp(cmdWord, CMD_CLOSURE_REF)) {
            return createSubjectFromRelationPtr(transitiveClosure(subjects[arg1].relation_p));
        }
        if (!strcmp(cmdWord, CMD_CLOSURE_SYM)) {
            return createSubjectFromRelationPtr(symmetricClosure(subjects[arg1].relation_p));
        }
        if (!strcmp(cmdWord, CMD_CLOSURE_TRANS)) {
            return createSubjectFromRelationPtr(transitiveClosure(subjects[arg1].relation_p));
        }
    }

    // Functions requiering stes as args
    if (subjects[arg2].subjectType == SetType
        && subjects[arg3].subjectType == SetType
        && arg2 == -1 && arg3 == -1) {
        if (!strcmp(cmdWord, CMD_INJECTIVE)) {
            printBool(isInjective(subjects[arg1].relation_p, subjects[arg2].set_p, subjects[arg3].set_p));
            return createEmptySubject(id);
        }
        if (!strcmp(cmdWord, CMD_SURJECTIVE)) {
            printBool(isSurjective(subjects[arg1].relation_p, subjects[arg2].set_p, subjects[arg3].set_p));
            return createEmptySubject(id);
        }
        if (!strcmp(cmdWord, CMD_BIJECTIVE)) {
            printBool(isBijective(subjects[arg1].relation_p, subjects[arg2].set_p, subjects[arg3].set_p));
            return createEmptySubject(id);
        }
    }


    invalidCommandCrash(id, cmdWord);
    // This does nothing but we got a warning without it.
    return createEmptySubject(0);
}

Subject processSetCommand(int id, char* cmdWord, int  arg1, int arg2, Subject* subjects) {
    if (arg2 == -1) {
        if (!strcmp(cmdWord, CMD_EMPTY)) {
            printBool(isEmpty(subjects[arg1].set_p));
            return createEmptySubject(id);
        }
        if (!strcmp(cmdWord, CMD_CARD)) {
            printf("%d\n", card(subjects[arg1].set_p));
            return createEmptySubject(id);
        }
        if (!strcmp(cmdWord, CMD_COMPLEMENT)) {
            return createSubjectFromSetPtr(getComplement(subjects[arg1].set_p, subjects[0].universe_p->size));
        }
    }

    // Processing commands with two inputs
    if (arg2 != -1 && (subjects[arg2].subjectType == SetType || subjects[arg2].subjectType == UniverseType)) {
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

    invalidCommandCrash(id, cmdWord);
    // This does nothing but we got a warning without it.
    return createEmptySubject(0);
}

Subject processCommand(int id, int size, char* contentString, GrowSubj* gsubj) {
    if (size < 2 || size > 4) {
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
    if (size >= 3) {
        arg2 = parseInt(content[2], &conversionErr) - 1;
        if (conversionErr) {
            nanCrash(id, content[2]);
        }
    }

    int arg3 = -1;
    if (size == 4) {
        arg3 = parseInt(content[3], &conversionErr) - 1;
        if (conversionErr) {
            nanCrash(id, content[3]);
        }
    }

    if (gsubj->content[arg1].subjectType == SetType || gsubj->content[arg1].subjectType == UniverseType) {
        if (arg3 != -1) {
            argCrash(id);
        }
        return processSetCommand(id, cmdWord, arg1, arg2, subjects);
    }
    if (gsubj->content[arg1].subjectType == RelationType) {
        return processRelationCommand(id, cmdWord, arg1, arg2, arg3, subjects);
    }

    argCrash(id);
    //
    // This does nothing but we got a warning without it.
    return createEmptySubject(0);
}

/**
 * this function creates a subject with specified values
 * @param id the number of the row from the file
 * @param size size = how many columns does the line have
 * @param contentString string with content, that will be parsed
 * @param type SubjectType that tells, how to handle specific line
 * @param universe Universe to Relate to when creating a subject based on the line
 * @param gsubj dynamic array of subjects, which is being filled with subjects from this function
 * @return created subject with specified values
 */

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
/**
 * this function tells what type to set to a variable based on the input char
 * @param character character that specifies which SubjectType to return
 * @return returns SetType related to the character
 */
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
        // Getting rid of a warning.
        return SetType;
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
    int growSubjLength = 0;

    SubjectType type;

    GrowStr* gstr;
    GrowSubj* gsubj = growSubjCreate();

    // If current iterration is going over the first char of the line.
    bool isFirstChar = true;
    // Counts words accourately.
    bool seenSpace = false;
    // Makes sure there is a space after the first char.
    bool afterFirstChar = false;

    bool isFirstCharOfFile = true;

    bool  wasUniverseSet = false;
    bool  wasSetSet = false;
    bool  wasRelationSet = false;
    bool wasCommandSet = false;


    FILE* file = fopen(filePath, "r");
    // read current charatcter while not at the end of the file
    while ((character = getc(file)) != EOF)
    {
        // only set SubjectType using fist character of the line
        if (isFirstChar)
        {
            gstr = growStrCreate();
            type = setType(character);

            if (isFirstCharOfFile && type != UniverseType) {
                fprintf(stderr, "The first character should specify a universe type!\n");
                exit(1);
            }
            isFirstCharOfFile = false;
            isFirstChar = false;
            seenSpace = false;
            afterFirstChar = true;
            continue;
        }
        // if endline is reached
        // store the whole string into the string variable
        // call the parsline function with it
        // free the old references and create new growStr

        else if (character == '\n')
        {
            string = growStrConvertToStr(gstr);

            if (type == UniverseType) {
                wasUniverseSet = true;
            }
            if (type == setType) {
                if (!wasUniverseSet) {
                    fprintf(stderr, "non valid argument order!\n");
                    exit(1);
                }
                wasSetSet = true;
            }

            if (type == RelationType) {
                if (!wasUniverseSet) {
                    fprintf(stderr, "non valid argument order!\n");
                    exit(1);
                }
                wasRelationSet = true;
            }

            if (type == CommandType) {
                wasCommandSet = true;
            }

            growSubjAdd(gsubj, parseLine(id, count, string, type, universe, gsubj));
            growSubjLength++;
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
                afterFirstChar = false;
            }
            else if (seenSpace) {
                count++;
                seenSpace = false;
            }

            if (afterFirstChar) {
                syntaxCrash();
            }

            growStrAdd(gstr, character);
            //printf("Element %c added\n", character);
            //printf("%s\n", gstr->content);
        }
    }
    //  Convert Growstr into an array.

    //  Send the line into a processing fucntion. (Returns Subject)
    // parseLine();
    if (growSubjLength == 1 && gsubj[0].content->universe_p != NULL) {
        fprintf(stderr, "Only universe has been specified!\n");
        exit(1);
    }

    if (!wasCommandSet) {
        fprintf(stderr, "no command specified!\n");
        exit(1);
    }
    /*
    FIXME: somehow does not fokin work
        if (!wasRelationSet && !wasSetSet) {
            fprintf(stderr, "no set or relation!\n");
            exit(1);
        }
    */
    free(gsubj[0].content->set_p);
    destroyUniverse(universe);
    destroyGrowSubj(gsubj);

    if (fclose(file))
    {
        ioCrash(filePath);
    }
}

/**
 * Functions returns the file from args.
 * @param argc counErrort of arguments.
 * @param argv values of argumets.
 * @return Path to file from arg or NULL if no path was given
*/
char* readFilePath(int argc, char** argv)
{
    if (argc != 2)
    {
        return NULL;
    }

    // We can add more checks here lol.
    return argv[1];
}

int main(int argc, char** argv)
{
    // has to be here so that rand() actually returns a random number
    srand(time(NULL));
    // Getting the path to the file.
    char* filePath = readFilePath(argc, argv);
    if (filePath == NULL)
    {
        fprintf(stderr, "Bad command line arguments! "
            "Provide a path to the instruction file.\n");
        return 1;
    }

    parseFile(filePath);
    /*
    char contentString[] = "S a b c x";

    Set *testSet = setCreate(1, 5, contentString);
    printf("set id: %d set size: %d\n", testSet->id, testSet->size);
    for (int i =Error 0; i < 5; i++)
    {
        printf("set content string at index %d = %s\n", i, testSet->content[i]);
    }
*/
// Parsing the content into structs.
//parseFile(filePath); // TODO: Dunno co to bude vracet to vymyslíme později
    return 0;

    //U S R C
}
