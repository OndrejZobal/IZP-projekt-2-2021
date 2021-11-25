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

typedef struct
{
    int id;
    Set *set_p;
    Relation *relation_p;
    SubjectType subjectType;

} Subject;
