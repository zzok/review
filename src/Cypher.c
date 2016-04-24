#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Ariph.h"
#include "CypherImpl.h"
#include "Trace.h"
#include "Error.h"

int EncryptWtoS(unsigned char const *in, unsigned blocksize, unsigned len, unsigned char *out){
	unsigned char *S;
	unsigned semiblocksCount = len * 2;
	unsigned semiblockSize = blocksize / 2;
	unsigned iterCount = 6*(semiblocksCount-1);
	unsigned iter;
	unsigned shift = 0;


	if( ( NULL == in ) || ( NULL == out ) )
		return ERR_BAD_PARAMS;

	if( semiblocksCount < 3 )
		return ERR_SHORT_ARRAY;

	if( semiblockSize < 4 )
		return ERR_SHORT_ARRAY;

	if( NULL == ( S = (unsigned char*) malloc( len * blocksize ) ) )
		return ERR_MALLOC;
	memcpy( S, in, blocksize * len );

	iterCount = 6*(semiblocksCount-1);

	for( iter = 1; iter <= iterCount; iter++ )
	{
		/*
		A_prev -> S[ shift * semiblockSize ]
		R2 -> S[ shift+1 * semiblockSize ]
		--
		A_new -> S[ shift+1 * semiblockSize ]
		Rn_new -> S[ shift * semiblockSize ]
		*/
		TRACE( "Aprev : ", semiblockSize, S, (shift)%semiblocksCount );
		TRACE( "R2    : ", semiblockSize, S, (shift+1)%semiblocksCount );

		Permutation( &S[ (shift)%semiblocksCount * semiblockSize ], &S[ (shift+1)%semiblocksCount * semiblockSize ], semiblockSize );
		TRACE( "A_new : ", semiblockSize, S, (shift+1)%semiblocksCount );
		TRACE( "Rn_new: ", semiblockSize, S, (shift)%semiblocksCount );

		XorArrayWithUnsigned( &S[ (shift+1)%semiblocksCount * semiblockSize ], semiblockSize, iter );
		TRACE( "XOR   : ", semiblockSize, S, (shift+1)%semiblocksCount );

		shift++;
	}

	memcpy( out, &S[ iterCount%semiblocksCount * semiblockSize ], semiblockSize * ( semiblocksCount - (iterCount%semiblocksCount) ) );
	memcpy( &out[ semiblockSize * ( semiblocksCount - (iterCount%semiblocksCount) ) ], S, semiblockSize * (iterCount%semiblocksCount) );

	free( S );
	return 0;
}

int DecryptWtoS(unsigned char *in, unsigned blocksize, unsigned len, unsigned char *out){
	unsigned char *S;
	unsigned semiblocksCount = len * 2;
	unsigned iterCount;
	unsigned iter;
	unsigned shift = 0; // note: shift left in deW
	unsigned semiblockSize = blocksize / 2;

	if( (NULL == in) || (NULL == out) )
		return ERR_BAD_PARAMS;

	if( semiblocksCount < 3 )
		return ERR_SHORT_ARRAY;

	if( semiblockSize < 4 )
		return ERR_SHORT_ARRAY;

	if( NULL == ( S = (unsigned char*) malloc( len * blocksize ) ) )
		return ERR_MALLOC;
	memcpy( S, in, blocksize * len );

	iterCount = 6*(semiblocksCount-1);

	for( iter = iterCount; iter >= 1; iter-- )
	{
		/*
		A_prev -> S[ shift * semiblockSize ]
		Rn -> S[ shift+1 * semiblockSize ]
		--
		A_new -> S[ shift+1 * semiblockSize ]
		R2_new -> S[ shift * semiblockSize ]
		*/
		TRACE( "Aprev : ", semiblockSize, S, (semiblocksCount-(shift)%semiblocksCount)%semiblocksCount );
		TRACE( "R2    : ", semiblockSize, S, (semiblocksCount-(shift+1)%semiblocksCount)%semiblocksCount );

		XorArrayWithUnsigned( &S[ (semiblocksCount-(shift)%semiblocksCount)%semiblocksCount * semiblockSize ], semiblockSize, iter );
		TRACE( "XOR   : ", semiblockSize, S, (semiblocksCount-(shift)%semiblocksCount)%semiblocksCount );

		Permutation( &S[ (semiblocksCount-(shift)%semiblocksCount)%semiblocksCount * semiblockSize ], &S[ (semiblocksCount-(shift+1)%semiblocksCount)%semiblocksCount * semiblockSize ], semiblockSize );
		TRACE( "A_new : ", semiblockSize, S, (semiblocksCount-(shift+1)%semiblocksCount)%semiblocksCount );
		TRACE( "R2_new: ", semiblockSize, S, (semiblocksCount-(shift)%semiblocksCount)%semiblocksCount );

		shift++;
	}

	memcpy( out, &S[ (semiblocksCount-iterCount%semiblocksCount)%semiblocksCount * semiblockSize ], semiblockSize * (iterCount%semiblocksCount) );
	memcpy( &out[ semiblockSize * (iterCount%semiblocksCount) ], S, blocksize*len-(semiblockSize * (iterCount%semiblocksCount)) );

	free( S );
	return 0;
}