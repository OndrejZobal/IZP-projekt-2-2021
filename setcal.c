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

// input constraints
#define MAX_INPUT_FILE_ROWS 999
#define MAX_ROW_ELEMENT_SIZE 30

// Set commands
#define CMD_EMPTY "empty"
#define CMD_CARD "card"
#define CMD_COMPLEMENT "complement"
#define CMD_UNION "union"
#define CMD_INTERSECT "intersect"
#define CMD_MINUS "minus"
#define CMD_SUBSETEQ "subseteq"
#define CMD_SUBSET "subset"
#define CMD_EQUALS "equals"

// GROWSTR constants
#define GROWSTR_DEFAULT_SIZE 10
#define GROWSTR_SIZE_MULTIPLIER 10
#define GROWSTR_OK 0
#define GROWSTR_ERR 1

// Relation commands
#define CMD_REFLEXIVE "reflexive"
#define CMD_SYMMETRIC "symmetric"
#define CMD_ANTISYMMETRIC "antisymmetric"
#define CMD_TRANSITIVE "transitive"
#define CMD_FUNCTION "function"
#define CMD_DOMAIN "domain"
#define CMD_CODOMAIN "codomain"
#define CMD_INJECTIVE "injective"
#define CMD_SURJECTIVE "surjective"
#define CMD_BIJECTIVE "bijective"

// Relations Bonus
#define CMD_CLOSURE_REF "closure_ref"
#define CMD_CLOSURE_SYM "closure_sym"
#define CMD_CLOSURE_TRANS "closure_trans"
#define CMD_SELECT "select"

typedef struct
{
    int id;
    int size;
    char** content;
} Universe;

typedef enum
{
    SetType,
    RelationType,
    UniverseType,
    CommandType,
} SubjectType;

typedef struct
{
    int x;
    int y;
} Pair;

typedef struct
{
    int id;
    int size;
    Pair* pairs;
} Relation;

typedef struct
{
    int id;
    int size;
    int* content;
} Set;

typedef struct
{
    int id;
    Set* set_p;
    Relation* relation_p;
    Universe* universe_p;
    SubjectType subjectType;

} Subject;

typedef struct growSubj {
    // Current length of the string.
    int length;
    // Size of allocated memroy for the string.
    int size;
    // Subject storing the content.
    Subject* content;
} GrowSubj;


typedef struct growStr
{
    // Current length of the string.
    int length;
    // Size of allocated memroy for the string.
    int size;
    // String storing the content.
    char* content;
} GrowStr;


int isInSet(int element, Set *set);
bool subseteq(Set *s1, Set *s2);
int subset(Set *s1, Set *s2);
int areSetsEqual(Set *s1, Set *s2);
Set* constructEmptySet(int size);
void memoryCrash();
Pair createPair(int x, int y);
void destroyPair(Pair* pair);
void destroyUniverse(Universe* universe);
void printPair(Universe universe, Pair pair);
Set *getComplement(Set *set, int universeSize);
Relation* CreateRelation(int id, int size, Pair* content);
int areSetsEqual(Set *s1, Set *s2);
void destroyRelation(Relation* relation);
Set createSet(int id, int size, int* content);
void destroySet(Set* set);
int getItemIndex(Universe* universe, char* word);
char* getItemName(Universe universe, int index);
void printUniverse(Universe universe);
Subject createSubjectFromSet(Set set);
Subject createSubjectFromSetPtr(Set* set);
Subject createSubjectFromRelationPtr(Relation* rel);
Subject createEmptySubject(int id);
void destroySubject(Subject* subject);
void printSet(Universe universe, Set set);
void printRelation(Universe universe, Relation rel);
void printSubject(Universe universe, Subject subject);
GrowStr* growStrCreate();
int growStrAdd(GrowStr* growstr, char ch);
char* growStrConvertToStr(GrowStr* growstr);
GrowSubj* growSubjCreate();
void growSubjAdd(GrowSubj* growstr, Subject subj);
void destroyGrowSubj(GrowSubj* growsubj);
Subject* growSubjConvertToArray(GrowSubj* growstr);
void ioCrash(char *path);
void syntaxCrash();
void argCrash(int index);
void nanCrash(int line, char* nan);
void invalidCommandCrash(int index, char* command);
void printBool(int boolean);
void freeString(char** strings, int size);
int isEmpty(Set *set);
int card(Set *set);
Set *setUnion(Set *s1, Set *s2);
Set *minus(Set *s1, Set *s2);
Set *intersect(Set *s1, Set *s2);
Relation* constructEmptyRelation(int size);
void reallocRelationToFit(Relation* relation, int newSize);
void reallocSetToFit(Set* set, int newSize);
void cloneRelation(Relation* from, Relation* to);
bool isInRelation(Pair pair, Relation *relation);
int isReflexive(Relation *relation, int universeSize);
bool isSymmetric(Relation *relation);
bool isAntisymmetric(Relation *relation);
int isTransitive(Relation *relation);
bool isFunction(Relation *relation);
Set* domain(Relation *relation);
Set* codomain(Relation *relation);
Relation* reflexiveClosure(Relation* relation, int universeSize);
Relation* symmetricClosure(Relation* relation);
Relation* transitiveClosure(Relation* relation);
bool isInjective(Relation* relation, Set* s1, Set* s2);
bool isSurjective(Relation* relation, Set* s1, Set* s2);
bool isBijective(Relation* relation, Set* s1, Set* s2);
int selectSet(Set* set);
Pair selectRelation(Relation* relation);
void splitStringintoArray(char* string, char** array, int size, char* delimiter);
void removeChar(char* str, char charToRemove);
bool hasSymbols(char** content, int size);
bool hasNumbers(char** content, int size);
bool hasCommandName(char** content, int size);
bool checkValidContent(char** content, int size);
void splitStringIntoPairs(char* string, int size, char** array);
bool hasMoreThanMaxSize(char* string);
bool hasRepeatingPairs(Pair* pairs, int size);
Relation* relationCreate(int id, int size, char* contentString, Universe* universe);
bool hasRepeatingElement(int* intContent, int size);
Set* setCreate(int id, int size, char* contentString, Universe* universe);
Universe* universeCreate(int id, int size, char* contentString);
int parseInt(char* str, bool* err);
Subject processRelationCommand(int id, char* cmdWord, int  arg1, int arg2, int arg3, Subject* subjects);
Subject processSetCommand(int id, char* cmdWord, int  arg1, int arg2, Subject* subjects);
Subject processCommand(int id, int size, char* contentString, GrowSubj* gsubj);
Subject parseLine(int id, int size, char* contentString, SubjectType type, Universe* universe, GrowSubj* gsubj);
SubjectType setType(char character);
void parseFile(char* filePath);
char* readFilePath(int argc, char** argv);
void parseFileEndCheck(int growSubjLength, GrowSubj* gsubj, bool wasCommandSet, bool wasRelationSet, bool wasSetSet);
void parseFileElseCheck(char character, bool* seenSpace, bool* afterFirstChar, int* count);
void endLineCharacterCheck(SubjectType type, bool* wasUniverseSet, bool* wasCommandSet, bool* wasRelationSet, bool* wasSetSet, Universe* universe, char* string);
void firstCharCheck(int id, SubjectType type, bool* isFirstChar, bool* seenSpace, bool* afterFirstChar);


/**
 * returns true if s1 is a subset of s2 (unless they are equal)
 * @param s1 set1
 * @param s2 set2
 * @return true or false
 */

int subset(Set *s1, Set *s2){
    if(areSetsEqual(s1, s2)){
        return 0;
    }
    else{
        return subseteq(s1, s2);
    }
}

/**
 * returns true if element is in set
 * @param element the element we are looking for
 * @param set the set we are searching
 * @return
 */

int isInSet(int element, Set *set){
    for (int i = 0; i < set->size; ++i) {
        if(element == set->content[i]){
            return 1;
        }
    }
    return 0;
}

/**
 * A constructor for the a Set that is empty.
 * All values will be set to -1 and id to 0.
 * @param size The size of the content.
 * @return A brand new set
 */
Set* constructEmptySet(int size) {
    Set* set;
    set = malloc(sizeof(Set));
    set->id = 0;
    set->size = size;
    if(size == 0){
        set->content = NULL;
        return set;
    }
    int* list = malloc(size * sizeof(int));
    if(size != 0){
        for (int i = 0; i < size; i++) {
            list[i] = -1;
        }
    }
    set->content = list;
    return set;
}

/**
 * returns true if s1 is a subset of s2
 * @param s1 set1
 * @param s2 set2
 * @return true or false
 */
bool subseteq(Set *s1, Set *s2){
    if(s1->size == 0){
        return true;
    }
    for (int i = 0; i < s1->size; ++i) {
        if(!isInSet(s1->content[i], s2)){
            return false;
        }
    }
    return true;
}

/**
 * exits the program if there is an issue with memory allocation
 */
void memoryCrash(){
    fprintf(stderr, "Failed to allocate memory on the machine. The program cannot continue!\n");
    exit(1);
}

/**
 * A constructor for the Pair type.
 * @param x The first part of the pair.
 * @param y The second part of the pair.
 * @return Brand new pair.
 */
Pair createPair(int x, int y) {
    Pair pair;
    pair.x = x;
    pair.y = y;
    return pair;
}

/**
 * A destructor for the Pair type.
 * @param pair The pair to be destroied.
 */
void destroyPair(Pair* pair) {
    free(pair);
}


/**
 * A destructor for the Universe type.
 * @param universe The universe that will be destroied.
 */
void destroyUniverse(Universe* universe) {
    for (int i = 0; i < universe->size; i++) {
        free(universe->content[i]);
    }
    free(universe->content);
    free(universe);
}


/**
 * Printing the Pair according to the specification.
 * @param universe Universe in wich the pair exists.
 * @param pair The pair you want to print.
 */
void printPair(Universe universe, Pair pair) {
    printf("(%s %s)", universe.content[pair.x], universe.content[pair.y]);
}

/**
 * returns the complement of set, compared to universe
 * @param set the we want the complement of
 * @param universeSize how many elements are in the universe
 * @return Set that is a complement of set
 */
Set *getComplement(Set *set, int universeSize) {
    int complementCurrentLength = 0; // how many elements in complement already have a value
    Set *complement = constructEmptySet(universeSize - set->size);

    for (int i = 0; i < universeSize; i++) {
        if(!isInSet(i, set)){
            complement->content[complementCurrentLength] = i;
            complementCurrentLength++;
        }
    }
    return complement;
}

/**
 * Printing the Pair according to the specification.
 * @param universe Universe in wich the pair exists.
 * @param pair The pair you want to print.
 */
Relation* CreateRelation(int id, int size, Pair* content) {
    if (content == NULL && size != 0) {
        content = malloc(sizeof(Pair) * size);
    }
    Relation* relation = malloc(sizeof(Relation));

    if (content == NULL || relation == NULL) {
        memoryCrash();
    }

    relation->id = id;
    relation->size = size;
    relation->pairs = content;
    return relation;
}

/**
 * returns true if sets are equal
 * @param s1 set1
 * @param s2 set2
 * @return true or false
 */
int areSetsEqual(Set *s1, Set *s2){
    if(s1->size != s2->size){
        return 0;
    }

    for (int i = 0; i < s1->size; ++i) {
        if(!isInSet(s1->content[i], s2)){
            return 0;
        }
    }
    return 1;
}

/**
 * A destructor for the Relation type.
 * @param relation The that will be destroyed.
 */
void destroyRelation(Relation* relation) {
    free(relation->pairs);
    free(relation);
}

/**
 * A constructor for the Set type.
 * @param id The id of the set.
 * @param size The amount of numbers in the content.
 * @param content The list of the numbers in the set.
 * @return A brand new set
 */
Set createSet(int id, int size, int* content) {
    Set set = { .id = id, .size = size, .content = content };

    return set;
}


/**
 * A destructor for the Set type.
 * @param set The set that will be destroied.
 */
void destroySet(Set* set) {
    free(set->content);
    free(set);
}

/**
 * This functin translates words into their numeric
 * representation.
 * @param universe Universe to translate from
 * @param the string to be translated.
 * @return Numeric representation of the word.
 */
int getItemIndex(Universe* universe, char* word) {
    for (int i = 0; i < universe->size; i++) {
        if (!strcmp(word, universe->content[i])) {
            return i;
        }
    }
    return -1;
}

/**
 * Translates numeric values back to strings using
 *the universe.
 * @param universe The univers used to translate the number.
 * @param index The numeric value that will be translated.
 * @return A string representation of "index".
 */
char* getItemName(Universe universe, int index) {
    return universe.content[index];
}

/**
 * Prints the universe according to the specification.
 * @param universe The universe you want to print.
 */
void printUniverse(Universe universe) {
    printf("U");
    for (int i = 0; i < universe.size; i++) {
        printf(" %s", universe.content[i]);
    }
    printf("\n");
}
/**
 * Encapsulate set in a subject
 * @param set The set you would like to encapsulate.
 * @return The subject with the set in it.
 */
Subject createSubjectFromSet(Set set) {
    // Copy the set to heap.
    Set* set_p = malloc(sizeof(Set));
    *set_p = set;

    Subject subj = { .id = set.id, .set_p = set_p, .subjectType = SetType };
    return subj;
}

/**
 * Encapsulate set in a subject using a pointer.
 * @param set The set pointer you would like to encapsulate.
 * @return The subject with the set in it.
 */
Subject createSubjectFromSetPtr(Set* set) {
    // Copy the set to heap.
    Subject subj = { .id = set->id, .set_p = set, .subjectType = SetType };
    return subj;
}

/**
 * Encapsulate relation in a subject using a pointer.
 * @param set The set pointer you would like to encapsulate.
 * @return The subject with the set in it.
 */
Subject createSubjectFromRelationPtr(Relation* rel) {
    // Copy the relation to heap.
    Subject subj = { .id = rel->id, .relation_p = rel, .subjectType = RelationType };
    return subj;
}


/**
 * Create a subject with nothing in it.
 * @param id id of the subject.
 * @return a new subject instance.
 */
Subject createEmptySubject(int id) {
    Subject subj = { .id = id, .subjectType = CommandType };
    return subj;
}

/**
 * A destructor for the Subject type.
 * @param subject The that will be destroied.
 */
void destroySubject(Subject* subject) {
    switch (subject->subjectType) {
        case SetType:
            destroySet(subject->set_p);
            break;
        case RelationType:
            destroyRelation(subject->relation_p);
            break;
        case UniverseType:
            destroyUniverse(subject->universe_p);
            destroySet(subject->set_p);
            break;
        case CommandType:
            if (subject->set_p != NULL){
                destroySet(subject->set_p);
            }
            if (subject->relation_p != NULL){
                destroyRelation(subject->relation_p);
            }

        default:
            break;
    }
}

/**
 * Prints the set according to the specification.
 * @param universe The universe you want to print.
 * @param set The set that will be printed out
 */
void printSet(Universe universe, Set set) {
    printf("S");
    for (int i = 0; i < set.size; i++) {
        if (set.content[i] == -1) {
            continue;
        }
        printf(" %s", universe.content[set.content[i]]);
    }
    printf("\n");
}

/**
 * Prints the relation according to the specification.
 * @param universe The universe you want to print.
 * @param rel The set that will be printed out
 */
void printRelation(Universe universe, Relation rel) {
    printf("R");
    for (int i = 0; i < rel.size; i++) {
        printf(" ");
        printPair(universe, rel.pairs[i]);
    }
    printf("\n");
}

/**
 * Prints the subject according to the specification.
 * @param universe The universe you want to print.
 * @param subject The set that will be printed out
 */
void printSubject(Universe universe, Subject subject) {
    switch (subject.subjectType) {
        case SetType:
            printSet(universe, *subject.set_p);
            break;
        case RelationType:
            printRelation(universe, *subject.relation_p);
            break;
        case UniverseType:
            printUniverse(universe);
            break;
        default:
            break;
    }
}

/**
 * This function creates a new instance of GrowString
 * @return An empty GrowStr
 */
GrowStr* growStrCreate()
{
    // Allocating the string array
    char* content = malloc(sizeof(char) * GROWSTR_DEFAULT_SIZE);
    GrowStr* gs = malloc(sizeof(GrowStr));

    if (content == NULL || gs == NULL)
    {
        return NULL;
    }

    // Cleaning the String.
    content[0] = '\0';

    // Assigning the values of the new GrowStr instance.
    gs->length = 0;
    gs->size = GROWSTR_DEFAULT_SIZE;
    gs->content = content;

    return gs;
}

/**
 * Adds a new character into an existing GrowStr instance.
 * @return GROWSTR_OK if successful and GROWSTR_ERR if the character could not
 *be added.
 * @param growstr GrowStr to be added into
 * @param ch Character that will be added into the growstring
 * @return GROWSTR_ERR on if the appending was unsuccessful, otherwise
 *GROWSTR_OK.
 */
int growStrAdd(GrowStr* growstr, char ch)
{
    // Checking if the string is large enough for another char to be added to it
    // (accounts for terminator).
    if (growstr->length + 1 > growstr->size - 1)
    {
        // Reallocating the array.
        char* buffer = NULL;
        // To make the need for reallocation less frequent the new string size will
        // be multiplied by a constant.
        int newSize = growstr->size * GROWSTR_SIZE_MULTIPLIER;
        buffer = (char*)realloc(growstr->content, newSize * sizeof(char));
        if (buffer == NULL)
        {
            return GROWSTR_ERR;
        }
        growstr->content = buffer;
        growstr->size = newSize;
    }

    // Adding the new char.
    growstr->content[growstr->length++] = ch;
    growstr->content[growstr->length] = '\0';
    return GROWSTR_OK;
}

/**
 * This function destroys the growstring and returns you an optimized string.
 * The Growstr is no longer valid after calling this.
 * @param growstr GrowStr that will be converted to string
 * @return content of growstr
 */
char* growStrConvertToStr(GrowStr* growstr)
{
    char* str = malloc(sizeof(char) * growstr->length+1);
    if (str == NULL)
    {
        printf("SUSUS hella susu :flushed:");
        exit(1);
    }
    for (int i = 0; i < growstr->length+1; i++)
    {
        str[i] = growstr->content[i];
    }

    free(growstr->content);
    free(growstr);
    return str;
}


/**
 * This function creates a new instance of GrowSubj
 * @return An empty GrowSubj
 */
GrowSubj* growSubjCreate() {
    // Allocating the string array
    Subject* content = malloc(sizeof(Subject) * GROWSTR_DEFAULT_SIZE);
    GrowSubj* gs = malloc(sizeof(GrowSubj));

    if (content == NULL || gs == NULL) {
        return NULL;
    }

    // Assigning the values of the new GrowSubj instance.
    gs->length = 0;
    gs->size = GROWSTR_DEFAULT_SIZE;
    gs->content = content;

    return gs;
}

/**
 * Adds a new Subjectacter into an exsiting GrowSubj instance.
 * @return GROWSTR_OK if successfull and GROWSTR_ERR if the Subjectacter could not
 *be added.
 * @param growstr GrowSubj to be added into
 * @param subj Subjectacter that will be added into the growstring
 *GROWSTR_OK.
 */
void growSubjAdd(GrowSubj* growstr, Subject subj) {
    // Checking if the string is large enough for another Subject to be added to it
    // (accounts for terminator).
    if (growstr->length + 1 > growstr->size) {
        // Reallocating the array.
        Subject* buffer = NULL;
        // To make the need for reallocation less frewquent the new string size will
        // be multiplied by a constant.
        int newSize = growstr->size * GROWSTR_SIZE_MULTIPLIER;
        buffer = realloc(growstr->content, newSize * sizeof(Subject));
        if (buffer == NULL) {
            memoryCrash();
        }

        growstr->content = buffer;
        growstr->size = newSize;
    }

    // Adding the new Subject.
    growstr->content[growstr->length++] = subj;
}

/**
 * frees the growsubject
 * @param growsubj the growsubject to be freed
 */
void destroyGrowSubj(GrowSubj* growsubj) {
    for (int i = 0; i < growsubj->length; i++) {
        destroySubject(&growsubj->content[i]);
    }
    free(growsubj->content);
    free(growsubj);
}

/**
 * This function destroys the growstring and returns you an optimized string.
 * The Growstr is no longer valid after calling this.
 * @param growstr GrowSubj that will be converted to string
 * @return content of growstr
 */
Subject* growSubjConvertToArray(GrowSubj* growstr) {
    Subject* str = malloc(sizeof(Subject) * growstr->length);
    if (str == NULL) {
        memoryCrash();
    }

    for (int i = 0; i < growstr->length; i++) {
        str[i] = growstr->content[i];
    }

    destroyGrowSubj(growstr);
    return str;
}

/**
 * exits the program if it fails to read from the input file
 * @param path the path to the file
 */
void ioCrash(char *path) {
    if (path == NULL){
        fprintf(stderr, "Failed to manipulate with file!\n");
        exit(1);
    }

    fprintf(stderr, "Failed to manipulate with file: \"%s\"!\n", path);
    exit(1);
}

/**
 * exists the program if input file contains invalid instructions
 */
void syntaxCrash() {
    fprintf(stderr, "Invalid syntax in instruction file. The program cannot continue!\n");
    exit(1);
}

/**
 * exits the program if the line contains invalid parameters
 * @param index the index of the line which contains invalid parameters
 */
void argCrash(int index) {
    fprintf(stderr, "Line %d has invalid parameters!", index + 1);
    syntaxCrash();
}

/**
 * exits the program if command argument is not a number
 * @param line the line which contains the invalid argument
 * @param nan the char which was supposed to be a number
 */
void nanCrash(int line, char* nan) {
    fprintf(stderr, "On line %d there was supposed to be a line number, instead got \"%s\"!\n", line, nan);
    syntaxCrash();
}

/**
 * exits the program if the operation is called with invalid inputs
 * @param index the index of the operation
 * @param command the command name
 */
void invalidCommandCrash(int index, char* command) {
    fprintf(stderr, "\"%s\" is not a valid operation for given inputs! Line %d!\n", command, index + 1);
    exit(1);
}

/**
 * prints the boolean value as a word
 * @param boolean A boolean value to be printed
 */
void printBool(int boolean){
    if (boolean != 0 && boolean != 1){
        fprintf(stderr, "Boolean operation resulted in nonbinary output: \"%d\"!\n", boolean);
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


/**
 * returns true if set size = 0
 * @param set the set we are checking
 * @return true or false
 */
int isEmpty(Set *set) {
    return !set->size;
}

/**
 * returns the number of elements in set
 * @param set the set we want to know the size of
 * @return the size of set
 */
int card(Set *set) {
    return set->size;
}


/**
 * returns the union of sets s1 and s2
 * @param s1 Set
 * @param s2 Set
 * @return union of s1 and s2
 */
Set *setUnion(Set *s1, Set *s2) {
    int unionSetSize = s1->size + s2->size;
    Set *unionSet = constructEmptySet(unionSetSize);

    int currentIndex = 0;
    for (int i = 0; i < s1->size; ++i) {
        unionSet->content[currentIndex] = s1->content[i];
        currentIndex++;
    }
    for (int i = 0; i < s2->size; ++i) {
        if(!isInSet(s2->content[i], unionSet)){
            unionSet->content[currentIndex] = s2->content[i];
            currentIndex++;
        }
    }
    return unionSet;
}

/**
 * returns the difference between s1 and s2
 * @param s1 set1
 * @param s2 the set that we are subtracting from set1
 * @return
 */

Set *minus(Set *s1, Set *s2) {
    Set *difference = constructEmptySet(s1->size);
    int differenceCurrentLength = 0;
    for (int i = 0; i < s1->size; i++) {
        if(!isInSet(s1->content[i], s2)){
            difference->content[differenceCurrentLength] = s1->content[i];
            differenceCurrentLength++;
        }
    }
    return difference;
}




/**
 * returns the intersect Set of s1 and s2
 * @param s1 set1
 * @param s2 set2
 * @return Set intersect of s1 and s2
 */
Set *intersect(Set *s1, Set *s2) {
    int currentIntersectSetLength = 0;
    Set *intersectSet;

    intersectSet = constructEmptySet(s1->size);

    for (int i = 0; i < s1->size; ++i) {
        if(isInSet(s1->content[i], s2)){
            intersectSet->content[currentIntersectSetLength] = s1->content[i];
            currentIntersectSetLength++;
        }
    }
    return intersectSet;
}



/**
 *
 * @param size size that should be allocated for the relation
 * @return relation full of '-1'
 */
Relation* constructEmptyRelation(int size) {
    Relation* relation = malloc(sizeof(Relation));
    relation->id = 0;
    relation->size = size;
    if(relation->size == 0){
        relation->pairs = NULL;
        return relation;
    }
    relation->pairs = malloc(size * sizeof(Pair));
    for (int i = 0; i < relation->size; ++i) {
        relation->pairs[i].x = -1;
        relation->pairs[i].y = -1;
    }
    return relation;
}

/**
 * reallocates the relation so that it doesnt contain any "empty" pairs
 * @param relation the relation to be reallocated
 * @param newSize size of relation after reallocating
 */
void reallocRelationToFit(Relation* relation, int newSize) {
    Pair* newPairs;
    newPairs = realloc(relation->pairs, newSize*sizeof(Pair));
    if(newPairs != NULL){
        relation->size = newSize;
        relation->pairs = newPairs;
    }
    else{
        memoryCrash();
    }
}

/**
 * reallocs the set so that it doesnt contain any empty pairs
 * @param set set to be reallocated
 * @param newSize size of the reallocated set
 */

// TODO utility, it belongs to a completely different file

void reallocSetToFit(Set* set, int newSize) {
    int* newContent;
    newContent = realloc(set->content, newSize * sizeof(int));
    if(newContent != NULL){
        set->size = newSize;
        set->content = newContent;
    }
    else{
        memoryCrash();
    }
}

/**
 * copies relation content
 * @param from the relation to copy from
 * @param to the relation to copy to
 */

void cloneRelation(Relation* from, Relation* to) {
    for (int i = 0; i < from->size; ++i) {
        to->pairs[i] = from->pairs[i];
    }
}

/**
 * returns true if pair is in relation
 * @param pair the pair we are looking for in the relation
 * @param relation the relation we are searching
 * @return
 */
bool isInRelation(Pair pair, Relation *relation) {
    for (int i = 0; i < relation->size; ++i) {
        if(pair.x == relation->pairs[i].x && pair.y == relation->pairs[i].y){
            return true;
        }
    }
    return false;
}

/**
 * returns true if the relation is reflexive on set Universe
 * @param relation the relation we are checking
 * @param universeSize how many elemnts does universe have
 * @return true or false
 */
int isReflexive(Relation *relation, int universeSize) {
    Pair reflexivePair;
    for (int i = 0; i < universeSize; ++i) {
        reflexivePair.x = i;
        reflexivePair.y = i;
        if(!isInRelation(reflexivePair, relation)){
            return false;
        }
    }
    return true;
}

/**
 * returns true if relation is symmetric
 * @param relation the relation we are checking
 * @return true or false
 */
bool isSymmetric(Relation *relation) {
    Pair flippedPair;
    for (int i = 0; i < relation->size; ++i) {
        if(relation->pairs[i].x == relation->pairs[i].y){
            continue;
        }
        flippedPair.x = relation->pairs[i].y;
        flippedPair.y = relation->pairs[i].x;
        if(!isInRelation(flippedPair, relation)){
            return false;
        }
    }
    return true;
}

/**
 * returns true if relation is antisymmetric
 * @param relation the relation we are checking
 * @return true or false
 */
bool isAntisymmetric(Relation *relation) {
    Pair flippedPair;
    for (int i = 0; i < relation->size; ++i) {
        if(relation->pairs[i].x == relation->pairs[i].y){
            continue;
        }
        flippedPair.x = relation->pairs[i].y;
        flippedPair.y = relation->pairs[i].x;
        if(isInRelation(flippedPair, relation)){
            return false;
        }
    }
    return true;
}


/**
 * returns true if relation is transitive
 * @param relation the relation we are checking
 * @return true or false
 */
int isTransitive(Relation *relation) {
    Pair gluedPair;
    int glue;
    for (int i = 0; i < relation->size; ++i) {
        if(relation->pairs[i].x == relation->pairs[i].y){
            continue;
        }
        glue = relation->pairs[i].y;
        for (int j = 0; j < relation->size; ++j) {
            if(relation->pairs[j].x == glue){
                gluedPair.x = relation->pairs[i].x;
                gluedPair.y = relation->pairs[j].y;
                if(!isInRelation(gluedPair, relation)){
                    return 0;
                }
            }
        }
    }
    return 1;
}

/**
 * returns true if relation is a function
 * @param relation the relation we are checking
 * @return true or false
 */
bool isFunction(Relation *relation) {
    int xValue;
    int yValue;
    for (int i = 0; i < relation->size; ++i) {
        xValue = relation->pairs[i].x;
        yValue = relation->pairs[i].y;
        for (int j = 0; j < relation->size; ++j) {
            if(relation->pairs[j].x == xValue){
                if(relation->pairs[j].y != yValue){
                    return false;
                }
            }
        }
    }
    return true;
}

/**
 * returns the domain of relation
 * @param relation the relation we want the domain of
 * @return Set which contains domain elements of relation
 */
Set* domain(Relation *relation) {
    int domainCurrentLength = 0;
    Set *domainSet = constructEmptySet(relation->size);
    if(domainSet->size == 0){
        return domainSet;
    }
    for (int i = 0; i < relation->size; ++i) {
        if(!isInSet(relation->pairs[i].x, domainSet)){
            domainSet->content[domainCurrentLength] = relation->pairs[i].x;
            domainCurrentLength++;
        }
    }
    reallocSetToFit(domainSet, domainCurrentLength);
    return domainSet;
}

/**
 * returns the codomain of relation
 * @param relation the relation we want the codomain of
 * @return Set which contains codomain elements of relation
 */
Set* codomain(Relation *relation) {
    int codomainCurrentLength = 0;
    Set *codomainSet = constructEmptySet(relation->size);
    if(codomainSet->size == 0){
        return codomainSet;
    }
    for (int i = 0; i < relation->size; ++i) {
        if(!isInSet(relation->pairs[i].y, codomainSet)){
            codomainSet->content[codomainCurrentLength] = relation->pairs[i].y;
            codomainCurrentLength++;
        }
    }
    reallocSetToFit(codomainSet, codomainCurrentLength);
    return codomainSet;
}


/**
 * returns the reflexive closure of relation on universe set
 * @param relation the relation we want the closure of
 * @param universeSize how many elements are in universe
 * @return the reflexive closure of relation
 */

Relation* reflexiveClosure(Relation* relation, int universeSize) {
    Pair reflexivePair;
    int refRelCurrentLength = relation->size;
    Relation* reflexiveClosureRelation = constructEmptyRelation(relation->size + universeSize);
    cloneRelation(relation, reflexiveClosureRelation);

    for (int i = 0; i < universeSize; ++i) {
        reflexivePair.x = i;
        reflexivePair.y = i;
        if(!isInRelation(reflexivePair, reflexiveClosureRelation)){
            reflexiveClosureRelation->pairs[refRelCurrentLength] = reflexivePair;
            refRelCurrentLength++;
        }
    }
    reallocRelationToFit(reflexiveClosureRelation, refRelCurrentLength);
    return reflexiveClosureRelation;
}

/**
 * returns the symmetric closure of relation
 * @param relation the relation we want the closure of
 * @return the symmetric closure of relation
 */
Relation* symmetricClosure(Relation* relation) {
    Pair symmetricPair;
    int symRelCurrentLength = relation->size;
    Relation* symmetricClosureRelation = constructEmptyRelation(relation->size * 2);
    cloneRelation(relation, symmetricClosureRelation);

    for (int i = 0; i < relation->size; ++i) {
        symmetricPair.x = symmetricClosureRelation->pairs[i].y;
        symmetricPair.y = symmetricClosureRelation->pairs[i].x;
        if(!isInRelation(symmetricPair, symmetricClosureRelation)){
            symmetricClosureRelation->pairs[symRelCurrentLength] = symmetricPair;
            symRelCurrentLength++;
        }
    }
    reallocRelationToFit(symmetricClosureRelation, symRelCurrentLength);
    return symmetricClosureRelation;
}

/**
 * returns the transitive closure of relation
 * @param relation the relation we want the closure of
 * @return the transitive closure of relation
 */
Relation* transitiveClosure(Relation* relation) {
    Pair gluedPair;
    int glue;
    int transRelCurrentLength = relation->size;
    Relation* transClosureRelation = constructEmptyRelation(relation->size * relation->size);
    cloneRelation(relation, transClosureRelation);

    for (int i = 0; i < transClosureRelation->size; ++i) {
        if(transClosureRelation->pairs[i].x == transClosureRelation->pairs[i].y){
            continue;
        }
        glue = transClosureRelation->pairs[i].y;
        for (int j = 0; j < transClosureRelation->size; ++j) {
            if(transClosureRelation->pairs[j].x == glue){
                gluedPair.x = transClosureRelation->pairs[i].x;
                gluedPair.y = transClosureRelation->pairs[j].y;
                if(!isInRelation(gluedPair, transClosureRelation)){
                    transClosureRelation->pairs[transRelCurrentLength] = gluedPair;
                    transRelCurrentLength++;
                }
            }
        }
    }
    reallocRelationToFit(transClosureRelation, transRelCurrentLength);
    return transClosureRelation;
}

/**
 * returns true if relation is an injective function on sets s1 and s2
 * @param relation the relation we are checking
 * @param s1 x values of the function
 * @param s2 y values of the function
 * @return true or false
 */

bool isInjective(Relation* relation, Set* s1, Set* s2) {
    if(s1->size > s2->size){
        return false;
    }
    if(!isFunction(relation)){
        return false;
    }
    Set* domainSet = domain(relation);
    if (!areSetsEqual(domainSet, s1)) {
        destroySet(domainSet);
        return false;
    }
    destroySet(domainSet);
    for (int i = 0; i < relation->size; ++i) {
        if (!isInSet(relation->pairs[i].y, s2)) {
            return false;
        }
        for (int j = i+1; j < relation->size; ++j) {
            if (relation->pairs[i].x == relation->pairs[j].x) {
                return false;
            }
            if(relation->pairs[i].y == relation->pairs[j].y){
                return false;
            }
        }
    }
    return true;
}

/**
 * returns true if relation is a surjective function on sets s1 and s2
 * @param relation the relation we are checking
 * @param s1 the x values of the function
 * @param s2 the y values of the function
 * @return true or false
 */
bool isSurjective(Relation* relation, Set* s1, Set* s2){
    if(!isFunction(relation)){
        return false;
    }
    Set *codomainSet = codomain(relation);
    if(!areSetsEqual(codomainSet, s2)){
        destroySet(codomainSet);
        return false;
    }
    destroySet(codomainSet);
    for (int i = 0; i < relation->size; ++i) {
        if(!isInSet(relation->pairs[i].x, s1)){
            return false;
        }
    }
    return true;
}

/**
 * returns true if relation is a bijective function on sets s1 and s2
 * @param relation the relation we are checking
 * @param s1 the x values of the function
 * @param s2 the y values of the function
 * @return true or false
 */
bool isBijective(Relation* relation, Set* s1, Set* s2) {
    if(!isFunction(relation)){
        return false;
    }
    if(isSurjective(relation, s1, s2) && isInjective(relation, s1, s2)){
        return true;
    }
    return false;
}

/**
 * returns a random element from set
 * @param set the Set we want the random element from
 * @return random set element
 */

int selectSet(Set* set) {
    if(set->size == 0){
        return -1;
    }
    int randomIndex = rand() % set->size;
    return set->content[randomIndex];
}

/**
 * returns a random Pair from relation
 * @param relation the Relation we want the random Pair from
 * @return random relation Pair
 */

Pair selectRelation(Relation* relation) {
    Pair dummyPair = {.x = -1, .y = -1};
    if(relation->size == 0){
        return dummyPair;
    }
    int randomIndex = rand() % relation->size;
    return relation->pairs[randomIndex];
}


 // TODO UPDATE: Obsah univerza si budeme pamatovat a seznam položek budme používat jako slovník id, abychom si ušetřili porovnavani stringu.

/**
 * this function splits string into an array by a delimimter
 * @param string string to be splitted
 * @param array array to be filled with
 * @param delimiter string that tells which character should split the string
 * @return void
 */

void splitStringintoArray(char* string, char** array, int size, char* delimiter)
{
    int i = 0;
    char* tempstr = malloc((strlen(string) + 1) * sizeof(char));
    strcpy(tempstr, string);
    char* strtoken = strtok(tempstr, delimiter);
    while (strtoken != NULL)
    {
        array[i++] = strtoken;

        strtoken = strtok(NULL, delimiter);
    }

    //char** jesuschrist = malloc(sizeof(char*) * size);
    for (int j = 0; j < size; j++) {
        int len = strlen(array[j]) + 1;
        char* godhavemercy = malloc(len * sizeof(char));
        strcpy(godhavemercy, array[j]);
        array[j] = godhavemercy;
    }

    free(tempstr);
    free(strtoken);
}

/**
 * this function removes a specific char from a string
 * @param string string to remove the chars from
 * @param charToRemove char to be removed
 * @return void
 */

void removeChar(char* str, char charToRemove) {
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == charToRemove)
        {
            for (int j = i; j < len; j++)
            {
                str[j] = str[j + 1];
            }
        }
    }
}

/**
 * this function checks if values, that should be use to create U/S/R contain symbols
 * @param content string array containing all elements
 * @param size size of content array
 * @return true if content doesnt contain symbols
 */

bool hasSymbols(char** content, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; (size_t)j < strlen(content[i]); j++) {
            if ((content[i][j] > 'z' || content[i][j] < 'a') && (content[i][j] > 'Z' || content[i][j] < 'A') && content[i][j] != ' ') {
                return true;
            }
        }
    }
    return false;

}

/**
 * this function checks if values, that should be use to create U/S/R contain numbers
 * @param content string array containing all elements
 * @param size size of content array
 * @return true if content doesnt contain number
 */

bool hasNumbers(char** content, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; (size_t)j < strlen(content[i]); j++) {
            if ((content[i][j] > '0' && content[i][j] < '9') && content[i][j] != ' ') {
                return true;
            }
        }
    }
    return false;
}

/**
 * this function checks if values, that should be use to create U/S/R contain command names
 * @param content string array containing all elements
 * @param size size of content array
 * @return true if content doesnt contain any of forbidden values
 */

bool hasCommandName(char** content, int size) {
    const int commandNameArraySize = 21;
    const char* commandNameArray[] = { "empty", "card", "complement", "union", "intersect", "minus",
    "subseteq", "subset", "equals", "reflexive", "symetric", "antisymmetric", "transitive",
     "function", "domain", "codomain", "injective", "surjective", "bijective", "true", "false" };


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < commandNameArraySize; j++) {
            if (!strcmp(content[i], commandNameArray[j])) {
                return true;
            }
        }
    }
    return false;
}

/**
 * this function checks if values, that should be use to create U/S/R contain forbidden characters
 * @param content string array containing all elements
 * @param size size of content array
 * @return return true if contend is valid
 */

bool checkValidContent(char** content, int size) {
    if (!hasSymbols(content, size) && !hasNumbers(content, size) && !hasCommandName(content, size)) {
        return true;
    }
    return false;
}

/**
 * splits string into array, which will then make pairs
 * @param string string to be split into pairs
 * @param array to which the string will be splitted
 * @return void
 */

void splitStringIntoPairs(char* string, int size, char** array) {
    removeChar(string, '(');
    splitStringintoArray(string, array, size, ")");

    if (!checkValidContent(array, size)) {
        fprintf(stderr, "given values contain forbidden characters!\n");
        exit(1);
    }
}


/**
 * this function tells, if universe contains longer element than it should
 * @param string string to check
 * @return return true if string is longer than max value
 */

bool hasMoreThanMaxSize(char* string) {
    if (strlen(string) > MAX_ROW_ELEMENT_SIZE) {
        return true;
    }
    return false;
}

/**
 * this function tells, whether there is
 * @param pairs int array of pairs
 * @param size size of intContent array
 * @return return true if relation contains duplicit pair
 */

bool hasRepeatingPairs(Pair* pairs, int size) {
    for (int i = 0; i < size; i++) {
        Pair helpPair = pairs[i];
        int numberOfRepeats = 0;

        for (int j = 0; j < size; j++) {
            if (pairs[j].x == helpPair.x && pairs[j].y == helpPair.y) {
                numberOfRepeats++;
            }
            if (numberOfRepeats > 1) {
                return true;
            }
        }
    }
    return false;
}

/**
 * this function creates a relation with specified values
 * @param id the number of the row from the file
 * @param size size = how many columns does the line have == values
 * @param contentString string with content, that will be parsed to values
 * @param universe universe the values are related to
 * @return created set with specified values
 */

Relation* relationCreate(int id, int size, char* contentString, Universe* universe) {
    char** content = malloc(sizeof(char*) * size);
    Pair* pairs = malloc(sizeof(Pair) * size);
    splitStringIntoPairs(contentString, size, content);

    for (int i = 0; i < size; i++) {
        char* helpArray[2];
        splitStringintoArray(content[i], helpArray, 2, " ");


        int x = getItemIndex(universe, helpArray[0]);
        int y = getItemIndex(universe, helpArray[1]);
        if (x == -1 || y == -1) {
            fprintf(stderr, "Attempted to create a relation with an element outside of the universe: (%s %s)\n", helpArray[0], helpArray[1]);
            exit(1);
        }
        Pair pair = createPair(x, y);
        pairs[i] = pair;

        for (int i = 0; i < 2; i++) {
            free(helpArray[i]);
        }
    }


    if (hasRepeatingPairs(pairs, size)) {
        fprintf(stderr, "given values contain identic pairs at line %d!\n", id + 1);
        exit(1);
    }

    Relation* relation = malloc(sizeof(Relation));
    relation->id = id;
    relation->size = size;
    relation->pairs = pairs;

    for (int i = 0; i < size; i++) {
        free(content[i]);
    }
    free(content);
    return relation;
}

/**
 * this function tells, whether there is duplicitt element in set
 * @param intContent int array of int elements
 * @param size size of intContent array
 * @return return true if relation contains duplicit pair
 */

bool hasRepeatingElement(int* intContent, int size) {
    for (int i = 0; i < size; i++) {
        int helpIntContent = intContent[i];
        int numberOfRepeats = 0;
        for (int j = 0; j < size; j++) {
            if (intContent[j] == helpIntContent) {
                numberOfRepeats++;
            }
            if (numberOfRepeats > 1) {
                return true;
            }
        }
    }
    return false;
}

/**
 * this function creates a set with specified values
 * @param id the number of the row from the file
 * @param size size = how many columns does the line have == values
 * @param contentString string with content, that will be parsed to values
 * @param universe universe the values are related to
 * @return created set with specified values
 */

Set* setCreate(int id, int size, char* contentString, Universe* universe) {
    // TODO: Need to check for duplicates in the set.
    int* intContent = malloc(sizeof(int) * size);
    char** content = malloc(sizeof(char*) * size);

    splitStringintoArray(contentString, content, size, " ");
    if (!checkValidContent(content, size)) {
        fprintf(stderr, "given values contain forbidden characters!\n");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        int index = getItemIndex(universe, content[i]);
        if (index == -1) {
            fprintf(stderr, "Attempted to create a set with an element outside of the universe: %s.\n", content[i]);
            exit(1);
        }
        intContent[i] = index;
    }

    if (hasRepeatingElement(intContent, size)) {
        fprintf(stderr, "given values contain repeating elements at line %d!\n", id + 1);
        exit(1);
    }


    Set* set = malloc(sizeof(Set));


    set->id = id;
    set->size = size;
    set->content = intContent;

    for (int i = 0; i < size; i++) {
        free(content[i]);
    }
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

Universe* universeCreate(int id, int size, char* contentString) {
    char** content = malloc(sizeof(char*) * size);

    splitStringintoArray(contentString, content, size, " ");

    if (!checkValidContent(content, size)) {
        fprintf(stderr, "given values contain forbidden characters!\n");
        exit(1);
    }

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

/**
 * A fucntion for carring out operations on relations
 * @param id ID of the line.
 * @param cmdWord the string representing the command alias
 * @param arg1 The line first supplied line number parsed as int.
 * @param arg2 The line first supplied line number parsed as int.
 * @param arg3 The line first supplied line number parsed as int.
 * @param subjects The list of all subjects processed so far
 * @return A processed subject
 */
Subject processRelationCommand(int id, char* cmdWord, int  arg1, int arg2, int arg3, Subject* subjects) {
    if (!strcmp(cmdWord, CMD_SELECT) && arg2 != -1 &&  arg3 == -1) {
        Pair pair = selectRelation(subjects[arg1].relation_p);
        printf("(%s %s)\n", getItemName(*subjects[0].universe_p, pair.x), getItemName(*subjects[0].universe_p, pair.y));
        return createEmptySubject(id);
    }

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
            return createSubjectFromRelationPtr(reflexiveClosure(subjects[arg1].relation_p, subjects[0].universe_p->size));
        }
        if (!strcmp(cmdWord, CMD_CLOSURE_SYM)) {
            return createSubjectFromRelationPtr(symmetricClosure(subjects[arg1].relation_p));
        }
        if (!strcmp(cmdWord, CMD_CLOSURE_TRANS)) {
            return createSubjectFromRelationPtr(transitiveClosure(subjects[arg1].relation_p));
        }
    }

    // Functions requiring sets as args
    /// In the version we submitted the following condition could never be true
    /// This is a fixed version.
    if (subjects[arg2].subjectType == SetType
        && subjects[arg3].subjectType == SetType) {
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

/**
 * A function for carrying out operations on Sets
 * @param id ID of the line.
 * @param cmdWord the string representing the command alias
 * @param arg1 The line first supplied line number parsed as int.
 * @param arg2 The line first supplied line number parsed as int.
 * @param subjects The list of all subjects processed so far
 * @return A processed subject
 */
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
    if (!strcmp(cmdWord, CMD_SELECT) && arg2 != -1) {
        printf("%s\n", getItemName(*subjects[0].universe_p, selectSet(subjects[arg1].set_p)));
        return createEmptySubject(id);
    }
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

/**
 * A fucntion for carring out operations. Either processSetCommand or processRelationCommand
 * @param id ID of the line.
 * @param size Count of the words in contentString
 * @param contentString Argumenty v podobě stryngu.
 * @param subjects The list of all subjects processed so far
 * @return A processed subject
 */
Subject processCommand(int id, int size, char* contentString, GrowSubj* gsubj) {
    if (size < 2 || size > 4) {
        argCrash(id);
    }

    char* content[size];
    Subject* subjects = gsubj->content;
    splitStringintoArray(contentString, content, size, " ");
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
        Subject newsubj = processSetCommand(id, cmdWord, arg1, arg2, subjects);
        freeString(content, size);
        return newsubj;
    }
    if (gsubj->content[arg1].subjectType == RelationType) {
        Subject newsubj = processRelationCommand(id, cmdWord, arg1, arg2, arg3, subjects);
        freeString(content, size);
        return newsubj;
    }

    freeString(content, size);
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

Subject parseLine(int id, int size, char* contentString, SubjectType type, Universe* universe, GrowSubj* gsubj) {
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

SubjectType setType(char character) {
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
 * this function checks if entered file during the firstChar condition is valid
 * @param id id corresponding to the file row
 * @param type type of the character being checked
 * @param isFirstChar tells if its the first char of the row
 * @param seenSpace tells if space has been seen
 * @param afterFirstChar tells if if there has been at least one character after a space
 * @return void
 */

void firstCharCheck(int id, SubjectType type, bool* isFirstChar, bool* seenSpace, bool* afterFirstChar) {
    if (id == 0 && type != UniverseType) {
        fprintf(stderr, "The first character should specify a universe type!\n");
        exit(1);
    }

    *isFirstChar = false;
    *seenSpace = false;
    *afterFirstChar = true;
}

/**
 * this function checks if entered file during the endLine condition
 * @param type type of the character being checked
 * @param wasUniverseSet tells if universe was already set
 * @param wasCommandSet tells if command was already set
 * @param wasRelationSet tells if relation was already set
 * @param wasSetSet tells if set was already set
 * @param universe universe from the file
 * @param string string to convert the growstring from input to
 * @return void
 */

void endLineCharacterCheck(SubjectType type, bool* wasUniverseSet, bool* wasCommandSet, bool* wasRelationSet, bool* wasSetSet, Universe* universe, char* string) {
    if (type == UniverseType) {
        if (*wasUniverseSet) {
            destroyUniverse(universe);
            free(string);
            fprintf(stderr, "Universe was already specified!\n");
            exit(1);
        }
        *wasUniverseSet = true;
    }
    if (type == SetType) {
        if (!(*wasUniverseSet) || *wasCommandSet) {
            fprintf(stderr, "non valid argument order!\n");
            exit(1);
        }
        *wasSetSet = true;
    }

    if (type == RelationType) {
        if (!(*wasUniverseSet) || *wasCommandSet) {
            fprintf(stderr, "non valid argument order!\n");
            exit(1);
        }
        *wasRelationSet = true;
    }

    if (type == CommandType) {
        *wasCommandSet = true;
    }
}

/**
 * this function checks if entered file during the else condition
 * @param character character that tells what type is being specified
 * @param seenSpace tells if space has been seen
 * @param afterFirstChar tells if if there has been at least one character after a space
 * @param count tells how long the input string is
 * @return void
 */

void parseFileElseCheck(char character, bool* seenSpace, bool* afterFirstChar, int* count) {
    if (character == ' ')
    {
        *seenSpace = true;
        *afterFirstChar = false;
    }
    else if (*seenSpace) {
        (*count)++;
        *seenSpace = false;
    }

    if (*afterFirstChar) {
        syntaxCrash();
    }
}

/**
 * this function checks if entered file during the end of the function
 * @param growSubjLength the length of the grow subject
 * @param gsubj pointer to the growSubject variable
 * @param wasCommandSet tells if command has been set
 * @param wasRelationSet tells if relation has been set
 * @param wasSetSet tells if set has been set
 * @return void
 */

void parseFileEndCheck(int growSubjLength, GrowSubj* gsubj, bool wasCommandSet, bool wasRelationSet, bool wasSetSet) {
    if (growSubjLength == 1 && gsubj[0].content->universe_p != NULL) {
        fprintf(stderr, "Only universe has been specified!\n");
        exit(1);
    }

    if (!wasCommandSet) {
        fprintf(stderr, "no command specified!\n");
        exit(1);
    }

    if (!wasRelationSet && !wasSetSet) {
        fprintf(stderr, "no set or relation!\n");
        exit(1);
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

    bool wasUniverseSet = false;
    bool wasSetSet = false;
    bool wasRelationSet = false;
    bool wasCommandSet = false;


    FILE* file = fopen(filePath, "r");

    if (file == NULL) {
        fprintf(stderr, "no file given!\n");
        exit(1);
    }
    // read current charatcter while not at the end of the file
    while ((character = getc(file)) != EOF)
    {
        if (id > MAX_INPUT_FILE_ROWS) {
            fprintf(stderr, "The file has to contain maximum of 1000 lines!\n");
        }
        // only set SubjectType using fist character of the line
        if (isFirstChar)
        {
            gstr = growStrCreate();
            type = setType(character);

            firstCharCheck(id, type, &isFirstChar, &seenSpace, &afterFirstChar);
            continue;
        }

        else if (character == '\n')
        {
            string = growStrConvertToStr(gstr);

            endLineCharacterCheck(type, &wasUniverseSet, &wasCommandSet, &wasRelationSet, &wasSetSet, universe, string);

            growSubjAdd(gsubj, parseLine(id, count, string, type, universe, gsubj));
            growSubjLength++;
            printSubject(*universe, gsubj->content[gsubj->length - 1]);

            free(string);
            count = 0;
            id++;
            isFirstChar = true;
        }
        else
        {
            parseFileElseCheck(character, &seenSpace, &afterFirstChar, &count);
            growStrAdd(gstr, character);
        }
    }

    parseFileEndCheck(growSubjLength, gsubj, wasCommandSet, wasRelationSet, wasSetSet);

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
char* readFilePath(int argc, char** argv) {
    if (argc != 2)
    {
        return NULL;
    }

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
    return 0;

}
