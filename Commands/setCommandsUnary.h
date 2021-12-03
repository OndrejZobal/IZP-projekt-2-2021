//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
// Created by vladimir on 11/25/21.
//

#ifndef setcal
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../structs.h"
#include "isInSet.h"
#include "areSetsEqual.h"
#endif


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
int card(Set *set){
    return set->size;
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


