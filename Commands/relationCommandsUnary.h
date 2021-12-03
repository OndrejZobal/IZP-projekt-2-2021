#ifndef setcal
#include "../structs.h"
#include "areSetsEqual.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../utility.h"
#include "isInSet.h"
#include "stdbool.h"
#include "areSetsEqual.h"
#include "isInSet.h"
#include "areSetsEqual.h"
#include <stdbool.h>
#include <time.h>
#endif




/**
 *
 * @param size size that should be allocated for the relation
 * @return relation full of '-1'
 */
Relation* constructEmptyRelation(int size){

    Relation* relation = malloc(sizeof(Relation));
    relation->id = 0;
    relation->size = size;
    relation->pairs = malloc(size * sizeof(Pair));
    if(relation->size == 0){
        relation->pairs = NULL;
        return relation;
    }
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
void reallocRelationToFit(Relation* relation, int newSize){
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

void reallocSetToFit(Set* set, int newSize){
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

void cloneRelation(Relation* from, Relation* to){
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
bool isInRelation(Pair pair, Relation *relation){
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
int isReflexive(Relation *relation, int universeSize){
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
bool isSymmetric(Relation *relation){
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
bool isAntisymmetric(Relation *relation){
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
int isTransitive(Relation *relation){
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
bool isFunction(Relation *relation){
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
Set* domain(Relation *relation){
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
Set* codomain(Relation *relation){
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

Relation* reflexiveClosure(Relation* relation, int universeSize){
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
// returns the symmetric closure of relation
Relation* symmetricClosure(Relation* relation){
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
Relation* transitiveClosure(Relation* relation){
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
bool isBijective(Relation* relation, Set* s1, Set* s2){
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

int selectSet(Set* set){
    if(set->size == 0){
        return -1;
    }
    int randomIndex = rand() % set->size;
    printf("%d\n", randomIndex);
    return set->content[randomIndex];
}

/**
 * returns a random Pair from relation
 * @param relation the Relation we want the random Pair from
 * @return random relation Pair
 */

Pair selectRelation(Relation* relation){
    Pair dummyPair = {.x = -1, .y = -1};
    if(relation->size == 0){
        return dummyPair;
    }
    int randomIndex = rand() % relation->size;
    return relation->pairs[randomIndex];
}

