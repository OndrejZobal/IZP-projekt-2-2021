//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
// Created by vladimir on 11/25/21.
//

#ifndef setcal
#include "../structs.h"
#include "isInSet.h"
#include "areSetsEqual.h"
#include "constructEmptySet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

// TODO remove unnecessary includes everywhere
// TODO check naming practice bullshit
// TODO FIX THE MEMORY LEAK WTFFFFFFF

Set *constructSet(int id, int size, int *content){ // TODO this is just for testing, remove later
    Set *set;
    set = constructEmptySet(size);
    set->id = id;
    set->size = size;
    free(set->content);
    set->content = content;
    return set;
}

// returns 0 if size > 0, returns 1 if size = 0
int isEmpty(Set *set) {
    return !set->size;
}

// returns the number of elements in set
int card(Set *set){
    return set->size;
}

// returns the complement of set
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


