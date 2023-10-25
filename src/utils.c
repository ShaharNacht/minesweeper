#include <stdlib.h>

#include "utils.h"

int clamp( int value, int minimum, int maximum )
{
	if ( value < minimum )
	{
		return minimum;
	}
	else if ( value > maximum )
	{
		return maximum;
	}
	else
	{
		return value;
	}
}

int random_range( int minimum, int maximum )
{
	return minimum + (int)( ( maximum - minimum ) * ( rand() / ( RAND_MAX + 1.0 ) ) );
}