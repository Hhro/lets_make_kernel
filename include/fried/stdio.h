#ifndef _STDIO_H
#define _STDIO_H 1

#define EOF (-1)

int kPrintf(const char* __restrict, ...);
int kPutchar(int);
int kPuts(const char*);
char kGetch();

#endif