//
// Created by vladimir on 11/27/21.
//
#ifndef setcal
#include "../structs.h"
#include "isInSet.h"
#include "areSetsEqual.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "isInSet.h"
#include "../utility.h"
#include "isInSet.h"
#include "stdbool.h"
#include "areSetsEqual.h"
#include "isInSet.h"
#include "areSetsEqual.h"
#include <stdbool.h>
#endif


// constructs relation full of empty pairs ('-1') // TODO utility
Relation* constructEmptyRelation(int size){
    Relation* relation = malloc(sizeof(Relation));
    relation->id = 0;
    relation->size = size;
    relation->pairs = malloc(size * sizeof(Pair));
    for (int i = 0; i < relation->size; ++i) {
        relation->pairs[i].x = -1;
        relation->pairs[i].y = -1;
    }
    return relation;
}

// reallocs the relation so that it doesnt contain any empty pairs // TODO utility
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

// reallocs the set so that it doesnt contain any empty pairs // TODO utility, it belongs to a completely different file
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

// copies relation "from" to relation "to" // TODO utility
void cloneRelation(Relation* from, Relation* to){
    for (int i = 0; i < from->size; ++i) {
        to->pairs[i] = from->pairs[i];
    }
}

// returns 1 if pair is in relation // TODO utility
int isInRelation(Pair pair, Relation *relation){
    for (int i = 0; i < relation->size; ++i) {
        if(pair.x == relation->pairs[i].x && pair.y == relation->pairs[i].y){
            return 1;
        }
    }
    return 0;
}

// returns 1 if relation is reflexive on set Universe
int isReflexive(Relation *relation, int universeSize){
    Pair reflexivePair;
    for (int i = 0; i < universeSize; ++i) {
        reflexivePair.x = i;
        reflexivePair.y = i;
        if(!isInRelation(reflexivePair, relation)){
            return false;
        }
    }
    return 1;
}

// returns 1 if relation is symmetric
int isSymmetric(Relation *relation){
    Pair flippedPair;
    for (int i = 0; i < relation->size; ++i) {
        if(relation->pairs[i].x == relation->pairs[i].y){
            continue;
        }
        flippedPair.x = relation->pairs[i].y;
        flippedPair.y = relation->pairs[i].x;
        if(!isInRelation(flippedPair, relation)){
            return 0;
        }
    }
    return 1;
}


// returns 1 if relation is antisymmetric
int isAntisymmetric(Relation *relation){
    Pair flippedPair;
    for (int i = 0; i < relation->size; ++i) {
        if(relation->pairs[i].x == relation->pairs[i].y){
            continue;
        }
        flippedPair.x = relation->pairs[i].y;
        flippedPair.y = relation->pairs[i].x;
        if(isInRelation(flippedPair, relation)){
            return 0;
        }
    }
    return 1;
}


// returns 1 if relation is transitive
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

// returns 1 if relation is function
int isFunction(Relation *relation){
    int xValue;
    int yValue;
    for (int i = 0; i < relation->size; ++i) {
        xValue = relation->pairs[i].x;
        yValue = relation->pairs[i].y;
        for (int j = 0; j < relation->size; ++j) {
            if(relation->pairs[j].x == xValue){
                if(relation->pairs[j].y != yValue){
                    return 0;
                }
            }
        }
    }
    return 1;
}

// returns domain set of relation (x values)
Set* domain(Relation *relation){
    int domainCurrentLength = 0;
    Set *domainSet = constructEmptySet(relation->size);
    for (int i = 0; i < relation->size; ++i) {
        if(!isInSet(relation->pairs[i].x, domainSet)){
            domainSet->content[domainCurrentLength] = relation->pairs[i].x;
            domainCurrentLength++;
        }
    }
    reallocSetToFit(domainSet, domainCurrentLength);
    return domainSet;
}

// returns codomain set of relation (y values)
Set* codomain(Relation *relation){
    int codomainCurrentLength = 0;
    Set *codomainSet = constructEmptySet(relation->size);
    for (int i = 0; i < relation->size; ++i) {
        if(!isInSet(relation->pairs[i].y, codomainSet)){
            codomainSet->content[codomainCurrentLength] = relation->pairs[i].y;
            codomainCurrentLength++;
        }
    }
    reallocSetToFit(codomainSet, codomainCurrentLength);
    return codomainSet;
}



//returns the reflexive closure of relation on universe set
Relation* reflexiveClosure(Relation* relation, int universeSize){
    if(isReflexive(relation, universeSize)){
        return relation;
    }

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

// returns the symmetric closure of relation
Relation* symmetricClosure(Relation* relation){
    if(isSymmetric(relation)){
        return relation;
    }

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

// returns the transitive closure of relation
Relation* transitiveClosure(Relation* relation){
    if(isTransitive(relation)){
        return relation;
    }

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

// TODO bijective/surjective/injective need more testing

// returns true if relation R is an injective function on sets s1 and s2
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

// returns true if relation R is a surjective function on sets s1 and s2
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

// returns true if relation R is a bijective function on sets s1 and s2
bool isBijective(Relation* relation, Set* s1, Set* s2){
    if(!isFunction(relation)){
        return false;
    }
    if(isSurjective(relation, s1, s2) && isInjective(relation, s1, s2)){
        return true;
    }
    return false;
}
