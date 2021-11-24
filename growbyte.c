#include <stdio.h>
#include <stdlib.h>

#define GROWBYTE_DEFAULT_SIZE 10
#define GROWBYTE_OK 0
#define GROWBYTE_ERR 1

// GrowByte, home.

typedef struct growByte {
  // The current length of the string in content
  int length;
  // The size of the allocated memory for content.
  int size;
  // The string storing the content
  void *content;
} GrowByte;

GrowByte *growStrCreate(int typeSize) {
  // Allocating the array
  char *content = malloc(typeSize * GROWBYTE_DEFAULT_SIZE);

  if (content == NULL) {
    return NULL;
  }

  // Emptying the string
  content[0] = '\0';

  GrowByte *gs = malloc(sizeof(GrowByte));
  gs->length = 0;
  gs->size = GROWBYTE_DEFAULT_SIZE;
  gs->content = content;
  return gs;
}

int growStrAdd(GrowByte *growstr, void *element) {
  if (growstr->length + 1 > growstr->size) {
    void *buffer = NULL;
    int newSize = growstr->size * 2;
    buffer = realloc(growstr->content, newSize * growstr->typeSize);
    if (buffer == NULL) {
      printf("What the hecc\n");
      exit(1);
    } else {
      growstr->content = buffer;
      growstr->size = newSize;
    }
  }

  // Adding the new char.
  growstr->content[growstr->length++] = (element);
  growstr->content[growstr->length] = '\0';
  return GROWBYTE_OK;
}

// Returns malloced string.
char *growStrConvertToArray(GrowByte *growstr) {
  char *str = malloc(growstr->typeSize * growstr->length);
  if (str == NULL) {
    printf("SUSUS hella susu");
    exit(1);
  }
  for (int i = 0; i < growstr->length; i++) {
    str[i] = growstr->content[i];
  }
  free(growstr->content);
  free(growstr);
  return str;
}

int main() {
  char *test = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopa"
               "sdfghjklzxcvbnm"
               "123456789012345678901234567890";
  GrowByte *gs = growStrCreate();
  printf("Grow string created!\n");
  for (int i = 0; test[i] != '\0'; i++) {
    growStrAdd(gs, test[i]);
    printf("Element %d added\n", i);
    printf("%s\n", gs->content);
  }
  printf("FINAL: %s\n", gs->content);
}
