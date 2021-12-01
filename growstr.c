#ifndef setcal
#include <stdio.h>
#include <stdlib.h>
#endif

#define GROWSTR_DEFAULT_SIZE 10
#define GROWSTR_SIZE_MULTIPLIER 10
#define GROWSTR_OK 0
#define GROWSTR_ERR 1

// GrowStr, home.

typedef struct growStr
{
    // Current length of the string.
    int length;
    // Size of allocated memroy for the string.
    int size;
    // String storing the content.
    char* content;
} GrowStr;

/**
 * This function creates a new instance of GrowString
 * @return An empty GrowStr
 */
GrowStr* growStrCreate()
{
    // Allocating the string array
    char* content = malloc(sizeof(char) * GROWSTR_DEFAULT_SIZE);
    GrowStr* gs = malloc(sizeof(GrowStr));

    if (content == NULL || gs == NULL)
    {
        return NULL;
    }

    // Cleaning the String.
    content[0] = '\0';

    // Assigning the values of the new GrowStr instance.
    gs->length = 0;
    gs->size = GROWSTR_DEFAULT_SIZE;
    gs->content = content;

    return gs;
}

/**
 * Adds a new character into an exsiting GrowStr instance.
 * @return GROWSTR_OK if successfull and GROWSTR_ERR if the character could not
 *be added.
 * @param growstr GrowStr to be added into
 * @param ch Character that will be added into the growstring
 * @return GROWSTR_ERR on if the appendinw was unsuccessfull, otherwise
 *GROWSTR_OK.
 */
int growStrAdd(GrowStr* growstr, char ch)
{
    // Checking if the string is large enough for another char to be added to it
    // (accounts for terminator).
    if (growstr->length + 1 > growstr->size - 1)
    {
        // Reallocating the array.
        char* buffer = NULL;
        // To make the need for reallocation less frewquent the new string size will
        // be multiplied by a constant.
        int newSize = growstr->size * GROWSTR_SIZE_MULTIPLIER;
        buffer = (char*)realloc(growstr->content, newSize * sizeof(char));
        if (buffer == NULL)
        {
            return GROWSTR_ERR;
        }
        growstr->content = buffer;
        growstr->size = newSize;
    }

    // Adding the new char.
    growstr->content[growstr->length++] = ch;
    growstr->content[growstr->length] = '\0';
    return GROWSTR_OK;
}

/**
 * This function destroys the growstring and returns you an optimized string.
 * The Growstr is no longer valid after calling this.
 * @param growstr GrowStr that will be converted to string
 * @return content of growstr
 */
char* growStrConvertToStr(GrowStr* growstr)
{
    char* str = malloc(sizeof(char) * growstr->length);
    if (str == NULL)
    {
        printf("SUSUS hella susu");
        exit(1);
    }
    for (int i = 0; i < growstr->length+1; i++)
    {
        str[i] = growstr->content[i];
    }
    //FIXME: next line sus corruption I think guys uwu
    //free(growstr->content);
    free(growstr);
    return str;
}

// Test function do not call
// int main() {
//     char *test = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopa"
//                  "sdfghjklzxcvbnm"
//                  "123456789012345678901234567890";
//     GrowStr *gs = growStrCreate();
//     printf("Grow string created!\n");
//     for (int i = 0; test[i] != '\0'; i++) {
//         growStrAdd(gs, test[i]);
//         printf("Element %d added\n", i);
//         printf("%s\n", gs->content);
//     }
//     printf("FINAL: %s\n", gs->content);
// }
