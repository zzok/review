/*
  XorArrayWithUnsigned
  Descr: bytewise xor array with unsigned (BE to LE inverting inside).
  Params:
    Inout unsigned char *a: pointer to array for xoring.
	In unsigned sizeA: size of array for xoring (in bytes).
	In unsigned b: unsigned for xoring with array.
  Return: -
*/
void XorArrayWithUnsigned( unsigned char *a, unsigned sizeA, unsigned b );

/*
  RevertArray
  Descr: revert bytes in array.
  Params:
    Inout unsigned char *array: pointer to array for reverting.
	In unsigned size: size of array for reverting (in bytes).
  Return: -
*/
void RevertArray( unsigned char *array, unsigned size );
