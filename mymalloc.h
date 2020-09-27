#ifndef _MYMALLOC_H
#define _MYMALLOC_H

//#include "mymalloc.c"
#include <stdlib.h>
#include <stdio.h>

#define SIZE 4096

#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

static char myblock[SIZE];



void* mymalloc(size_t numberOfBytes, char* file, int line); // Declare our myMalloc
void myfree(void* ptr, char* file, int line); // Declare our myfree
void initialize(); 
void printmyblock(); 
#endif



