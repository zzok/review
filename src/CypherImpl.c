#include "Ariph.h"

void Permutation( unsigned char* semiblock1, unsigned char* semiblock2, unsigned size )
{
	RevertArray( semiblock1, size );
	RevertArray( semiblock2, size );
}

