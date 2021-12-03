#ifndef setcal
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structs.h"
#include "isInSet.h"
#include "areSetsEqual.h"
#include "constructEmptySet.h"
#endif

/**
 * returns the union of sets s1 and s2
 * @param s1 Set
 * @param s2 Set
 * @return union of s1 and s2
 */
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

/**
 * returns the difference between s1 and s2
 * @param s1 set1
 * @param s2 the set that we are subtracting from set1
 * @return
 */

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
 * returns the intersect Set of s1 and s2
 * @param s1 set1
 * @param s2 set2
 * @return Set intersect of s1 and s2
 */
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
