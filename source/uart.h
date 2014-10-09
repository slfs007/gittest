#ifndef uart_h
#define uart_h
#include"reg51.H"
typedef unsigned char 	BYTE;
typedef unsigned int 	WORD;
#define FOSC	12000000L
#define BAUD	2400
#define Q_MAX 32


struct uart1queue
{
	int head;
	int end;
	int length;
	char buf[Q_MAX];
};
extern bit busy1;
extern char ch1;
extern struct uart1queue u1buf;

void uart1_clr( void);
void uart1_init( void);
void uart1_putchar(char ch);
void uart1_puts(char *s);
char uart1_getchar( unsigned char *ch);

#endif