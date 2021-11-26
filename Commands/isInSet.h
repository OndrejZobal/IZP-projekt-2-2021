//
// Created by vladimir on 11/26/21.
//

#ifndef tests
#include "../structs.h"
#endif
// returns 1 if element is in set
int isInSet(int element, Set *set){
    for (int i = 0; i < set->size; ++i) {
        if(element == set->content[i]){
            return 1;
        }
    }
    return 0;
}