#ifndef setcal
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"
#endif

typedef struct testType
{
    int test;
} TestType;


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
 * A destructor for the Relatin type.
 * @param relation The that will be destroied.
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
    // Copy the set to heap.
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
    //free(subject);
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
