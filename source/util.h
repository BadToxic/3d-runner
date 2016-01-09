#ifndef UTIL_H
#define UTIL_H

// reverses a string 'str' of length 'len'
void reverse(char*, int);

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int, char[], int);

// Converts a floating point number to string.
void ftoa(float, char*, int);

#endif /* UTIL_H */