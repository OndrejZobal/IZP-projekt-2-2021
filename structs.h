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

void destroyUniverse(Universe* universe) {
    for (int i = 0; i < universe->size; i++) {
        free(universe->content[i]);
    }
    free(universe->content);
    free(universe);
}

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

Pair createPair(int x, int y) {
    Pair pair;
    pair.x = x;
    pair.y = y;
    return pair;
}

void destroyPair(Pair* pair) {
    free(pair);
}

void printPair(Universe universe, Pair pair) {
    printf("(%s %s)", universe.content[pair.x], universe.content[pair.y]);
}

typedef struct
{
    int id;
    int size;
    Pair* pairs;
} Relation;

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

void destroyRelation(Relation* relation) {
    free(relation->pairs);
    free(relation);
}

typedef struct
{
    int id;
    int size;
    int* content;
} Set;

Set createSet(int id, int size, int* content) {
    Set set = { .id = id, .size = size, .content = content };

    return set;
}

// makes a set full of '-1'
Set* constructEmptySet(int size) {
    int* list = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        list[i] = -1;
    }
    Set* set;
    set = malloc(sizeof(Set));
    set->id = 0;
    set->size = size;
    set->content = list;
    return set;
}

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

char* getItemName(Universe universe, int index) {
    return universe.content[index];
}

void printUniverse(Universe universe) {
    printf("U");
    for (int i = 0; i < universe.size; i++) {
        printf(" %s", universe.content[i]);
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

Subject createSubjectFromSet(Set set) {
    // Copy the set to heap.
    Set* set_p = malloc(sizeof(Set));
    *set_p = set;

    Subject subj = { .id = set.id, .set_p = set_p, .subjectType = SetType };
    return subj;
}

Subject createSubjectFromSetPtr(Set* set) {
    // Copy the set to heap.
    Subject subj = { .id = set->id, .set_p = set, .subjectType = SetType };
    return subj;
}

Subject createSubjectFromRelationPtr(Relation* rel) {
    // Copy the set to heap.
    Subject subj = { .id = rel->id, .relation_p = rel, .subjectType = SetType };
    return subj;
}

Subject createEmptySubject(int id) {
    Subject subj = { .id = id, .subjectType = CommandType };
    return subj;
}

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

void printRelation(Universe universe, Relation rel) {
    printf("R");
    for (int i = 0; i < rel.size; i++) {
        printf(" ");
        printPair(universe, rel.pairs[i]);
    }
    printf("\n");
}

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
