#include <math.h>

void XorArrayWithUnsigned( unsigned char *a, unsigned sizeA, unsigned b )
{
	int i;

#ifdef _BIG_ENDIAN
	for(i=1;i<=sizeof(unsigned);i++)
#else // _BIG_ENDIAN
	for(i=sizeof(unsigned);i>=1;i--)
#endif
	{
		a[sizeA-i] ^= b & 0xff;
		b = b >> 8;
	}
}

void RevertArray( unsigned char *array, unsigned size )
{
	char tmp;
	int i;

	for(i=0;i<size/2;i++)
	{
		tmp = array[i];
		array[i] = array[size-1-i];
		array[size-1-i] = tmp;
	}
}
