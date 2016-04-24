/*
  Permutation
  Descr: bytewise revert of semiblock1 || semiblock2.
  Params:
    Inout unsigned char* semiblock1: poinetr to first array for permutation. After return there will be semiblock2.
	Inout unsigned char* semiblock2: pointer to second array for permutation. After return there will be semiblock1.
	In zise: size of semiblock1 and semiblock2 arrays.
  Return: -
*/
void Permutation( unsigned char* semiblock1, unsigned char* semiblock2, unsigned size );