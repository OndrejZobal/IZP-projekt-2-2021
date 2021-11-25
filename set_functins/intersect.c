#ifndef main
#include "../structs.h"
#endif

void set_intersect(Subject *subjects, int a, int b){
    for (int i = 0; subjects[a].set_p->size; i++){
        for (int j = 0; subjects[b].set_p->size; j++){
            if (subjects[a].set_p->obsah[i] == subjects[b].set_p->obsah[j]){
                // TODO Lookup jmena prvku v univerzu.
                //printf("")
            }
        }
    }
}
