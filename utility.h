#ifndef UTILITY_H_
#define UTILITY_H_

#ifndef setcal
#include <stdio.h>
#include <stdlib.h>
#endif

#endif // UTILITY_H_

void memoryCrash(){
    fprintf(stderr, "Failed to allocate memory on the machine. The program cannot continue!");
    exit(1);
}
