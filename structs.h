typedef struct testType
{
    int test;
} TestType;

typedef enum
{
    SetType,
    RelationType
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
    char **obsah;
} Set;

typedef struct
{
    int id;
    Set *set_p;
    Relation *relation_p;
    SubjectType subjectType;

} Subject;
