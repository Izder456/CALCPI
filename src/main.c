////////////////////////////////////////
// { prgmCALCPI } { v1.5 }
// Author: izder456
// License: n/a
// Description: calculates pi
////////////////////////////////////////

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Other available headers: stdarg.h, setjmp.h, assert.h, ctype.h, float.h, iso646.h, limits.h, errno.h */

/* uint8_t is an unsigned integer that can range from 0-255. */
/* It performs faster than just an int, so try to use it (or int8_t) when possible */

/* Put function prototypes here */
void printText(const char * text, uint8_t xpos, uint8_t ypos);
int getGcd(int n1, int n2);
void float2str(float value, char * str);
#define INPUT_SIZE 10

/* Put all your code here */
int main(void) {
    char one[18] = "Total Iterations:";
    char two[11] = "Max Value:";
    int a;
    int i;
    float c = 1.;
    int m;
    float f, g;
    float p;
    char inputBuffer[INPUT_SIZE];
    char * ptr;
    char astr[9], pstr[9];
    char prompt[] = "";

    os_ClrHomeFull();
    prompt[0] = 0;
    printText(one, 0, 0);
    os_GetStringInput(prompt, inputBuffer, INPUT_SIZE);
    i = strtol(inputBuffer, & ptr, 0);

    prompt[0] = 0;
    printText(two, 0, 1);
    os_GetStringInput(prompt, inputBuffer, INPUT_SIZE);
    m = strtol(inputBuffer, & ptr, 0);


    printText("Estimate of pi:", 0, 2);
    printText("I=", 0, 4);
    for (a = 0; a <= i; a++) {
        f = randInt(0, m);
        g = randInt(0, m);
        if (getGcd(f, g) == 1)
            c++;
        p = sqrt((6 * a) / c);
        float2str(p, pstr);
        printText(pstr, 0, 3);
        sprintf(astr, "%d", a);
        printText(astr, 2, 4);
        if (os_GetCSC()) {
            printText("Interrupt detected", 0, 5);
            break;
        }
    }
    printText("Done!", 0, 6);
    while (!os_GetCSC());
    os_ClrHomeFull();

    return 0;
}

/* Draw text on the homescreen at the given X/Y cursor location */
void printText(const char * text, uint8_t xpos, uint8_t ypos) {
    os_SetCursorPos(ypos, xpos);
    os_PutStrFull(text);
}
/* get the gcd of two numbers */
int getGcd(int n1, int n2) {
    if (n2 != 0)
        return getGcd(n2, n1 % n2);
    else
        return n1;
}
/* convert float to string */
void float2str(float value, char * str) {
    real_t tmp_real = os_FloatToReal(value);
    os_RealToStr(str, & tmp_real, 9, 1, 9);
}