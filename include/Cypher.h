/*
  EncryptWtoS
  Descr: encrypt array by WtoS alg.
  Params:
    In unsigned char const *in: pointer to array to encrypt.
	In unsigned blocksize: size of cypher block (in bytes).
	In unsigned len: size of array (in blocks).
	Out unsigned char *out: pointer to array for result.
  Return: -
*/
int EncryptWtoS(unsigned char const *in, unsigned blocksize, unsigned len, unsigned char *out);

/*
  DecryptWtoS
  Descr: decrypt array by WtoS alg.
  Params:
    In unsigned char const *in: pointer to array to decrypt.
	In unsigned blocksize: size of cypher block (in bytes).
	In unsigned len: size of array (in blocks).
	Out unsigned char *out: pointer to array for result.
  Return: -
*/
int DecryptWtoS(unsigned char *in, unsigned blocksize, unsigned len, unsigned char *out);
