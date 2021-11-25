#ifndef main
#include <string.h>
#endif

typedef struct testType
{
    int test;
} TestType;

typedef enum
{
    SetType,
    RelationType,
    UniverseType
} SubjectType;

typedef struct
{
    char *x;
    char *y;
} Pair;

typedef struct
{
    int id;
    int size;
    Pair pairs[];
} Relation;

typedef struct
{
    int id;
    int size;
    int *content;
} Set;


typedef struct
{
    int id;
    int size;
    char **content;
} Universe;

int getItemIndex(Universe *universe, char* word){
    for (int i = 0; i < universe->size; i++){
        if (strcmp(word, universe->content[i])){
            return i;
        }
    }
    return -1;
}

typedef struct
{
    int id;
    Set *set_p;
    Relation *relation_p;
    Universe *universe_p;
    SubjectType subjectType;

} Subject;
