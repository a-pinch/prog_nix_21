#include <string.h>

int stringStat(const char *string, int multiplier, int *count){
    (*count)++;
    return strlen(string)*multiplier;
}
