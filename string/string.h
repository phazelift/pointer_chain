#ifndef STRING_H_
#define STRING_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


size_t stringLength( const char* );
char* createString( char* );
void appendString( char*, const char* );
bool isEqualString( const char*, const char* );


#endif
