#include "./string.h"



// most optimized
size_t stringLength( const char* str )
{
	if ( str )
	{
		const char* p = str;
		while ( *str ) str++;
		return str - p;
	}
	else puts( "string::stringLength - Error - cannot process NULL string!" );
	return 0;
}



char* createString( char* str )
{
	return strcpy( malloc(stringLength( str )), str );
}



void appendString( char* str1, const char* str2 )
{
	if ( str1 && str2 )
	{
		str1 = realloc( str1, stringLength(str1) + stringLength(str2) );
		strcat( str1, str2 );
	}
	else puts( "string::appendString - Error - cannot process NULL string!" );
}



bool isEqualString( const char* str1, const char* str2 )
{
	if ( stringLength(str1) != stringLength(str2) ) return false;
	while ( *str1 && *str2 )
	{
		if ( *str1 != *str2 ) return false;
		str1++;
		str2++;
	}
	return true;
}
