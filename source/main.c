#include "include.h"

unsigned char led_buf[32];
unsigned char chinese[2];
void led_display( unsigned char buf[32]);
void get_cc_matrix(unsigned char cc[2],unsigned char matrix[32]);//cc:chinese characters

void main()
{ 
	unsigned char i;
	uart1_init();
	P0=0;P1=0;P2=0;

	while(1)
	{ 
		if( uart1_getchar(& (chinese[0]) ))
		{
			uart1_getchar(& (chinese[1]));
			get_cc_matrix(chinese,led_buf);
			for( i = 0;i < 64; i++)
			{
				led_display(led_buf);
			}
		}
		led_display(led_buf);
	}
}
void get_cc_matrix(unsigned char cc[2],unsigned char matrix[32])//cc:chinese characters
{
	unsigned long offset;
	unsigned char q,w,ch,i,j;
	q = cc[0] - 0xa1;
	w = cc[1] - 0xa1;

	offset = (q * 94 + w);
	offset <<= 5;
	for(i = 0;i < 32;i++)
	{
		ch= read_random( offset >> 16, (offset & 0xffff) + i);
		matrix[i] = 0;
		for( j = 0; j < 8; j ++)
		{
			matrix[i] |= ( ((ch >> (7-j)) &0x01)<< (j)) ;
		}
	}
}
void led_display(unsigned char buf[32])
{
	unsigned char scan=0,i,j;
	
	for(i=0;i<16;i++)
	{ 
		P1=scan;
		for(j=0;j<20;j++) 
		{ 			
			P2=buf[i * 2 ] ;
			P0=buf[i * 2 + 1] ;
		}
		scan++;
	}
}