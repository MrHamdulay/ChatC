#include <stdio.h>

extern int failed;

#define test(message, test) do { if(test) { printf("%s: passed!\n", message); }\
                                 else { printf("%s: failed!\n", message); failed++; }\
                               } while(0);
