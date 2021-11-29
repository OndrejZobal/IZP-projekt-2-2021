//
// Created by vladimir on 11/27/21.
//

#ifndef IZP_PROJEKT_2_2021_RELATIONCOMMANDSUNARY_H
#define IZP_PROJEKT_2_2021_RELATIONCOMMANDSUNARY_H

#endif //IZP_PROJEKT_2_2021_RELATIONCOMMANDSUNARY_H

#ifndef setcal
#include "../structs.h"
#include "isInSet.h"
#include "areSetsEqual.h"
#include "constructEmptySet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
#include "constructEmptySet.h"
#include "isInSet.h"

// returns 1 if pair is in relation
// TODO move this to utility commands later?
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
    int reflexivePairsCount = 0;
    for (int i = 0; i < universeSize; ++i) {
        if(relation->pairs[i].x == relation->pairs[i].y){
            reflexivePairsCount++;
        }
    }
    if(reflexivePairsCount >= universeSize){
        return 1;
    }
    return 0;
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
Set *domain(Relation *relation){
    Set *domainSet = constructEmptySet(relation->size);
    if(!isFunction(relation)){
        return NULL;
    }
    for (int i = 0; i < relation->size; ++i) {
        if(!isInSet(relation->pairs[i].x, domainSet)){
            domainSet->content[i] = relation->pairs[i].x;
        }
    }
    return domainSet;
}

// returns codomain set of relation (y values)
Set *codomain(Relation *relation){
    Set *codomainSet = constructEmptySet(relation->size);
    if(!isFunction(relation)){
        return NULL;
    }
    for (int i = 0; i < relation->size; ++i) {
        if(!isInSet(relation->pairs[i].y, codomainSet)){
            codomainSet->content[i] = relation->pairs[i].y;
        }
    }
    return codomainSet;
}

// TODO t/s/r closures
