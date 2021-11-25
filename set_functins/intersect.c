
// This enables this file to be compiled standalone.
#ifndef main
#include "../structs.h"
#include <stdlib.h>
#endif



Set setIntersect(Subject *subjects, int a, int b){
    int *intersects = malloc(sizeof(int) * subjects[a].set_p->size);
    if (intersects == NULL){
        exit(1);
    }
    int counter = 0;
    for (int i = 0; subjects[a].set_p->size; i++){
        for (int j = 0; subjects[b].set_p->size; j++){
            if (subjects[a].set_p->content[i] == subjects[b].set_p->content[j]){
                // TODO Lookup jmena prvku v univerzu.
                intersects[counter++] = subjects[a].set_p->content[i];
            }
        }
    }

    // TODO Create set

    // TODO Return set
}
