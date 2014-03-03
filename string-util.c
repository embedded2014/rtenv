#include "stm32f10x.h"
#include "RTOSConfig.h"

#include <stddef.h>
#include <stdarg.h>

#include "string-util.h"

int strcmp(const char *a, const char *b) __attribute__ ((naked));
int strcmp(const char *a, const char *b)
{
	asm(
        "strcmp_lop:                \n"
        "   ldrb    r2, [r0],#1     \n"
        "   ldrb    r3, [r1],#1     \n"
        "   cmp     r2, #1          \n"
        "   it      hi              \n"
        "   cmphi   r2, r3          \n"
        "   beq     strcmp_lop      \n"
		"	sub     r0, r2, r3  	\n"
        "   bx      lr              \n"
		:::
	);
}

int strncmp(const char *a, const char *b, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
		if (a[i] != b[i])
			return a[i] - b[i];

	return 0;
}

size_t strlen(const char *s) __attribute__ ((naked));
size_t strlen(const char *s)
{
	asm(
		"	sub  r3, r0, #1			\n"
        "strlen_loop:               \n"
		"	ldrb r2, [r3, #1]!		\n"
		"	cmp  r2, #0				\n"
        "   bne  strlen_loop        \n"
		"	sub  r0, r3, r0			\n"
		"	bx   lr					\n"
		:::
	);
}

void puts(const char *s)
{
	while (*s) {
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
			/* wait */ ;
		USART_SendData(USART2, *s);
		s++;
	}
}

void print_to_console( const char *str )
{
	/* IRQ */
	puts( str );
}

/* @param dest_end A char pointer which points to 
 * the end of the destination string.
 * @param source A char pointer which points to the
 * begin of the source string.
 * strapp() is different from c standard strcat(),
 * which strapp() will return a char-pointer points 
 * to the end of the destination string. */
char *strapp( char *dest_end, const char *source )
{
	char *d_e = dest_end;
	const char *s = source;

	while( ( *d_e++ = *s++ ) != '\0' )
		;

	return d_e;
}

/* Copy string from source to dest. */
char *strcpy( char *dest, const char *source )
{
	char *d = dest;
	const char *s = source;

	while ( ( *d++ = *s++ ) != '\0' )
		;

	return dest;
}

/* C Standard Function */
char *strcat( char *dest, const char *source )
{
	strcpy( &dest[strlen(dest)], source );
	return dest;
}

/* To not to call print_to_console function frequently,
 * use buffered string. If the buffer is full, a new-line
 * is added to buffer, or flush() is called, the buffer
 * would be sent to the print_to_console() and then cleared. */
#define PRINTF_BUF_LEN	100

char	p_buffer[ PRINTF_BUF_LEN + 1 ];
char *	p_buffer_ptr = p_buffer;
int		p_buffer_i = 0;

void flush()
{
	/* Append a null character. */
	*p_buffer_ptr = '\0';
	print_to_console( p_buffer );
	/* Reset index.(Clear the buffer) */
	p_buffer_ptr = p_buffer;
}

int printf( const char *format, ... )
{
	va_list ap;
	char ch[2] = { '0', '\0' }, *ap_str, itoa_buf[32];
	const char *f = format;
	
	va_start( ap, format );

	/* Parsing the formatted string */
	while ( *f != '\0' )
	{
		/* Normal text. */
		if ( *f != '%' )
		{
			*p_buffer_ptr++ = *f;
		}
		else
		{
			/* Discard '%' and get formatted indicator. */
			switch( *++f )
			{
				case 's':	/* String */
				case 'S':
					ap_str = va_arg( ap, char * );
					p_buffer_ptr = strapp( p_buffer_ptr, ap_str );
					break;
				case 'c':	/* Character */
				case 'C':
					*p_buffer_ptr++ = va_arg( ap, int );
					break;
				case 'i':	/* Integer */
				case 'I':
				case 'u':
				case 'U':
					itoa( va_arg( ap, int ), itoa_buf, 10 );
					p_buffer_ptr = strapp( p_buffer_ptr, itoa_buf );
					break;
				default:
					break;
			}	// end of switch( *++f )
		}	// end of else( *f == '%' )
		/* If the current character is new line character,
		 * or the buffer is full, flush the buffer. */
		if ( *f == '\n' || *f == '\r' ||
				p_buffer_ptr - p_buffer <= PRINTF_BUF_LEN - 1 )
			flush();
		/* Switch to the next character. */
		++f;
	}	// end of while( *f != '\0' )
}	// end of printf() func
