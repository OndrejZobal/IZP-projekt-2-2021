//
// Created by vladimir on 11/25/21.
//

#ifndef tests
#include "../structs.h"
#include "isInSet.h"
#include "areSetsEqual.h"
#include "constructEmptySet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif


// TODO maybe do some realloc magic so that only the bare minimum amount of memory is used
// TODO also check naming practice later

// returns the union of s1 and s2
Set *setUnion(Set *s1, Set *s2){
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

// returns the difference set of s1 and s2 (s1 \ s2)
Set *minus(Set *s1, Set *s2){
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

// returns true if s1 is a subset of s2 (they can be equal)
int subseteq(Set *s1, Set *s2){
    for (int i = 0; i < s1->size; ++i) {
        if(!isInSet(s1->content[i], s2)){
            return 0;
        }
    }
    return 1;
}


// returns true if s1 is a subset of s2 (they cannot be equal)
int subset(Set *s1, Set *s2){
    if(areSetsEqual(s1, s2)){
        return 0;
    }
    else{
        return subseteq(s1, s2);
    }
}

// returns the intersect of s1 and s2
Set *intersect(Set *s1, Set *s2){
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