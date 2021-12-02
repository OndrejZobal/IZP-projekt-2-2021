#ifndef setcal
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./utility.h"
#include "./structs.h"
#endif

#define GROWSTR_DEFAULT_SIZE 10
#define GROWSTR_SIZE_MULTIPLIER 10
#define GROWSTR_OK 0
#define GROWSTR_ERR 1

typedef struct growSubj {
    // Current length of the string.
    int length;
    // Size of allocated memroy for the string.
    int size;
    // Subject storing the content.
    Subject* content;
} GrowSubj;

/**
 * This function creates a new instance of GrowSubj
 * @return An empty GrowSubj
 */
GrowSubj* growSubjCreate() {
    // Allocating the string array
    Subject* content = malloc(sizeof(Subject) * GROWSTR_DEFAULT_SIZE);
    GrowSubj* gs = malloc(sizeof(GrowSubj));

    if (content == NULL || gs == NULL) {
        return NULL;
    }

    // Assigning the values of the new GrowSubj instance.
    gs->length = 0;
    gs->size = GROWSTR_DEFAULT_SIZE;
    gs->content = content;

    return gs;
}

/**
 * Adds a new Subjectacter into an exsiting GrowSubj instance.
 * @return GROWSTR_OK if successfull and GROWSTR_ERR if the Subjectacter could not
 *be added.
 * @param growstr GrowSubj to be added into
 * @param subj Subjectacter that will be added into the growstring
 *GROWSTR_OK.
 */
void growSubjAdd(GrowSubj* growstr, Subject subj) {
    // Checking if the string is large enough for another Subject to be added to it
    // (accounts for terminator).
    if (growstr->length + 1 > growstr->size) {
        // Reallocating the array.
        Subject* buffer = NULL;
        // To make the need for reallocation less frewquent the new string size will
        // be multiplied by a constant.
        int newSize = growstr->size * GROWSTR_SIZE_MULTIPLIER;
        buffer = realloc(growstr->content, newSize * sizeof(Subject));
        if (buffer == NULL) {
            memoryCrash();
        }

        growstr->content = buffer;
        growstr->size = newSize;
    }

    // Adding the new Subject.
    growstr->content[growstr->length++] = subj;
}

void destroyGrowSubj(GrowSubj* growsubj) {
    for (int i = 0; i < growsubj->length; i++) {
        destroySubject(&growsubj->content[i]);
    }
    free(growsubj->content);
    free(growsubj);
}

/**
 * This function destroys the growstring and returns you an optimized string.
 * The Growstr is no longer valid after calling this.
 * @param growstr GrowSubj that will be converted to string
 * @return content of growstr
 */
Subject* growSubjConvertToArray(GrowSubj* growstr) {
    Subject* str = malloc(sizeof(Subject) * growstr->length);
    if (str == NULL) {
        memoryCrash();
    }

    for (int i = 0; i < growstr->length; i++) {
        str[i] = growstr->content[i];
    }

    destroyGrowSubj(growstr);
    return str;
}

//
//// Test function do not call
//int main() {
//    Subject *test = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopa"
//                 "sdfghjklzxcvbnm"
//                 "123456789012345678901234567890";
//    GrowSubj *gs = growStrCreate();
//    printf("Grow string created!\n");
//    for (int i = 0; test[i] != '\0'; i++) {
//        growStrAdd(gs, test[i]);
//        printf("Element %d added\n", i);
//        printf("%s\n", gs->content);
//    }
//    printf("FINAL: %s\n", gs->content);
//}
