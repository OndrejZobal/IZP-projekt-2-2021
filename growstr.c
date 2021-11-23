#include <stdlib.h>
#include <stdio.h>

#define GROWSTR_DEFAULT_LENGTH 10
#define GROWSTR_OK 0
#define GROWSTR_ERR 1

// GrowStr, home.
// TODO I havent tested if this works.

typedef struct growStr {
    int length;
    int size;
    char *content;
} GrowStr;

GrowStr *growStrCreate() {
    // Allocating the array
    char *content = malloc(sizeof(char) * GROWSTR_DEFAULT_LENGTH);

    if (content == NULL){
        return NULL;
    }

    // Emptying the string
    content[0] = '\0';

    GrowStr *gs = malloc(sizeof(GrowStr));
    gs->length = 0;
    gs->size = GROWSTR_DEFAULT_LENGTH;
    gs->content = content;
    return gs;
}

int growStrAdd(GrowStr *growstr, char ch) {
    if (growstr->length + 1 > growstr->size - 1) {
        // TODO call realloc
        char *buffer = NULL;
        int newSize = growstr->size * 2;
        if (buffer = realloc(growstr->content, newSize * sizeof(char)) != NULL) {
            growstr->content = buffer;
            growstr->size = newSize;
        }
        else {
            printf("sussy baka\n");
        }
    }

    // Adding the new char.
    growstr->content[growstr->length++] = ch;
    growstr->content[growstr->length] = '\0';
    return GROWSTR_OK;
}

// Returns malloced string.
char *growStrConvertToStr(GrowStr *growstr) {
    return growstr->content;
    free(growstr);
}

int main() {
    char* test = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm";
    GrowStr *gs = growStrCreate();
    printf("Grow string created!\m");
    for (int i = 0; test[i] != '\0'; i++) {
        growStrAdd(gs, test[i]);
        printf("Element %d added\n", i);
        printf("%s\n", gs->content);
    }
    printf("FINAL: %s\n", gs->content);
}


