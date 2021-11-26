//
// Created by vladimir on 11/26/21.
//

#ifndef IZP_PROJEKT_2_2021_ARESETSEQUAL_H
#define IZP_PROJEKT_2_2021_ARESETSEQUAL_H

#endif //IZP_PROJEKT_2_2021_ARESETSEQUAL_H

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