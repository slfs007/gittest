#include"uart.h"

bit busy1;

struct uart1queue u1buf;

void uart1_init( void)
{

	uart1_clr();

	SCON = 0X50;
	TMOD = 0X20;
	TH1 = TL1 = -(FOSC/12/32/BAUD);
	TR1 = 1;
	ES = 1;
	EA = 1;
}
void uart1_clr( void)
{
	u1buf.head = 0; 
	u1buf.end = 0;
	u1buf.length = 0;
}
void uart1_putchar(char ch)
{
	while(busy1);
	ACC = ch;
	busy1 = 1;
	SBUF = ACC;
}
void uart1_puts(char *s)
{
	while(*s)
	{
		uart1_putchar(*s++);
	}
}
char uart1_getchar( unsigned char *ch)
{
	char flag;
	if(u1buf.length == 0)
	{
		flag = 0;
		*ch = 0;
	}else
	{	
		flag = 1;
		*ch = u1buf.buf[u1buf.head++];
		u1buf.length--;
		if(u1buf.head == Q_MAX)
			u1buf.head = 0;
	}
	return flag;
}
void uart1_isr() interrupt 4
{
	if(RI)
	{
		RI = 0;
		u1buf.buf[u1buf.end++] = SBUF;
		u1buf.length++;
		if(u1buf.end == (Q_MAX))
		{
			u1buf.end = 0;
		}
	}
	if(TI)
	{
		TI = 0;
		busy1 = 0;
	}
}
