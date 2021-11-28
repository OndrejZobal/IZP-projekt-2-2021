//
// Created by vladimir on 11/26/21.
//

#ifndef setcal
#include "../structs.h"
#include "isInSet.h"
#endif

// returns 1 if sets are equal
int areSetsEqual(Set *s1, Set *s2){
    if(s1->size != s2->size){
        return 0;
    }

    for (int i = 0; i < s1->size; ++i) {
        if(!isInSet(s1->content[i], s2)){
            return 0;
        }
    }
    return 1;
}
