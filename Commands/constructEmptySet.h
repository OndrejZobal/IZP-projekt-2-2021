//
// Created by vladimir on 11/26/21.
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
#include <stdlib.h>

// makes a set full of '-1'
Set *constructEmptySet(int size){
    int *list = malloc(size * sizeof(int));
    for(int i = 0; i < size; i++){
        list[i] = -1;
    }
    Set *set;
    set = malloc(sizeof(Set));
    set->id= 0;
    set->size = size;
    set->content = list;
    return set;
}
