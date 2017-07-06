#ifndef standards_h_
#define standards_h_
#include<stdio.h>
#define WIDTH 100
#define CH_OUT '-'
#define QUIT '6'

void outputDivider(FILE* fptr, char ch, unsigned int total);
void outputMenu(FILE* fptr);
void flushScreenInput();

void logTime(FILE* fptr);
int get_sequence();

#endif
