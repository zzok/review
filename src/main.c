#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#include "Cypher.h"
#include "Error.h"

#define PRINT_USING \
	{ \
		printf("USING: WtoS blocksize file [encr/decr]\n"); \
		printf("       Note: file should contain no more than 1024 bytes\n"); \
		printf("       Note: if size of file is not multiple of blocksize it will be added by zeros\n"); \
		return ERR_BAD_PARAMS; \
	}

int main(int argc, char* argv[])
{
	long bs;
	char *p;
	unsigned blocksize;
	unsigned char in[1024];
	unsigned char out[1024];
	unsigned inlen;
	int ret;
	int i;
	int c;
	FILE *file;

	if( argc < 3 )
		PRINT_USING;

	errno = 0;
	bs = strtol(argv[1], &p, 10);
	if (errno != 0 || *p != '\0' || bs > INT_MAX || bs < 0)
		PRINT_ERROR_AND_RETURN( ERR_BAD_BLOCKSIZE );
	blocksize = (unsigned)bs;
	
	if( NULL == (file = fopen( argv[2], "rb" )) )
		PRINT_ERROR_AND_RETURN( ERR_FILE_OPEN );

	i=0;
	while (EOF != (c = getc( file )) )
	{
		if( i >= 1024 )
		{
			fclose( file );
			PRINT_ERROR_AND_RETURN( ERR_BIG_FILE );
		}
		in[i++] = (unsigned char)c;
	}
	inlen = i;
	fclose( file );
	/* adding zeros for last block */

	while( inlen%blocksize )
	{
		if( inlen >= 1024 )
		{
			fclose( file );
			PRINT_ERROR_AND_RETURN( ERR_BAD_BLOCKSIZE );
		}
		in[inlen++] = 0;
	}

	if( argc >= 4 )
	{
		if( 0 == strcmp( argv[3], "decr" ) )
		{
			ret = DecryptWtoS( in, blocksize, inlen/blocksize, out );
			if( OK != ret )
				PRINT_ERROR_AND_RETURN( ret );
		} else if(  0 == strcmp( argv[3], "encr" ) )
		{
			ret = EncryptWtoS( in, blocksize, inlen/blocksize, out );
			if( OK != ret )
				PRINT_ERROR_AND_RETURN( ret );
		} else
			PRINT_USING;
	} else
	{
		ret = EncryptWtoS( in, blocksize, inlen/blocksize, out );
		if( OK != ret )
			PRINT_ERROR_AND_RETURN( ret );
	}

	if( NULL == (file = fopen( argv[2], "wb" )) )
		PRINT_ERROR_AND_RETURN( ERR_FILE_OPEN );

	for( i = 0; i < inlen; i++ )
		putc( out[i], file );
	fclose( file );

	return ret;
}