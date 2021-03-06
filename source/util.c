#include "util.h"
#include <string.h>
#include<math.h>
// reverses a string 'str' of length 'len'
void reverse(char *str, int len) {

    int i = 0, j = len - 1, temp;
	
    while (i<j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
		j--;
    }
	
}

 // Converts a given integer x to string str[].  d is the number
 // of digits required in output. If d is more than the number
 // of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d) {

    int i = 0;
    while (x) {
        str[i++] = (x%10) + '0';
        x = x / 10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d) {
        str[i++] = '0';
	}
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint) {

    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
 
    // check for display option after point
    if (afterpoint != 0) {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}

// Calculates the signum of a number
int sign(int n) {

    if (n > 0) {
		return 1;
	}
	else if (n < 0) {
		return -1;
	}
	else {
		return 0;
	}
}

// Write time to a string
void getTimeString(char time_string[], struct tm *time) {

    char hour_string[2];
	char min_string[2];
	char sec_string[2];
	intToStr(time->tm_hour, hour_string, 2);
	intToStr(time->tm_min, min_string, 2);
	intToStr(time->tm_sec, sec_string, 2);
	strcpy(time_string, hour_string);
	strcat(time_string, ":");
	strcat(time_string, min_string);
	strcat(time_string, ".");
	strcat(time_string, sec_string);
	
}