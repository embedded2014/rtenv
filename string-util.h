#ifndef STRING_UTIL
#define STRING_UTIL

#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n);
int strcmp(const char *a, const char *b);
int strncmp(const char *a, const char *b, size_t n);
size_t strlen(const char *s);
void puts(const char *s);
void print_to_console( const char *str );
char *strapp( char *dest_end, const char *source );
char *strcpy( char *dest, const char *source );
char *strcat( char *dest, const char *source );
void flush();
int printf( const char *format, ... );
void itoa( int n, char *dst, int base );

#endif	/* STRING_UTIL */
