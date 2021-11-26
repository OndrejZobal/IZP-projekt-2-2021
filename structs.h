#ifndef main
#include <string.h>
#include <stdio.h>
#endif

typedef struct testType
{
    int test;
} TestType;

typedef enum
{
    SetType,
    RelationType,
    UniverseType
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
    Pair pairs[];
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
    int size;
    char** content;
} Universe;

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

char *getItemName(Universe* universe, int index) {
    return universe->content[index];
}

void printUniverse(Universe *universe){
    printf("U");
    for(int i = 0; i < universe->size; i++) {
        printf(" %s", universe->content[i]);
    }
    printf("\n");
}

typedef struct
{
    int id;
    Set* set_p;
    Relation* relation_p;
    Universe* universe_p;
    SubjectType subjectType;

} Subject;

void printSet(Universe *universe, Set *set){
    printf("S");
    for(int i = 0; i < set->size; i++){
        if (set->content[i] == -1){
            printf(" OwQ");
        }
        printf(" %s", getItemName(universe, set->content[i]));
    }
    printf("\n");
}

void printRelation(Universe *universe, Relation *rel){
    printf("R");
    for(int i = 0; i < rel->size; i++){
        printf(" (%s %s)", universe->content[rel->pairs[i].x], universe->content[rel->pairs[i].x]);
    }
    printf("\n");
}

void printSubject(Universe *universe, Subject *subject){
    switch(subject->subjectType){
        case SetType:
            printSet(universe, subject->set_p);
            break;
        case RelationType:
            printRelation(universe, subject->relation_p);
            break;
        case UniverseType:
            printUniverse(universe);
    }
}
