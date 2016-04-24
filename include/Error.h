#define OK 0
#define ERR_BAD_PARAMS 1
#define ERR_SHORT_ARRAY 2
#define ERR_MALLOC 3
#define ERR_BAD_BLOCKSIZE 4
#define ERR_FILE_OPEN 5
#define ERR_BIG_FILE 6


#define PRINT_ERROR_AND_RETURN(_error) \
	{ \
		printf("ERROR %d", _error); \
		return _error; \
	}


