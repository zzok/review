#ifdef _DEBUG
  #define TRACE(_print,_semiblock_size,_S,_p ) \
  { \
    int _i; \
    printf( _print ); \
    for( _i = 0; _i < _semiblock_size; _i++ ) \
      printf("%02x",_S[ _p * _semiblock_size + _i ]); \
    printf("\n"); \
  }
#else // _DEBUG
  #define TRACE(_print,_semiblock_size,_S,_p )
#endif // _DEBUG

