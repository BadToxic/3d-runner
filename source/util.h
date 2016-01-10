#ifndef UTIL_H
#define UTIL_H

#include <time.h>

// reverses a string 'str' of length 'len'
void reverse(char*, int);

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int, char[], int);

// Converts a floating point number to string.
void ftoa(float, char*, int);

// Calculates the signum of a number
int sign(int);

// Write time to a string
void getTimeString(char[], struct tm*);

#endif /* UTIL_H */