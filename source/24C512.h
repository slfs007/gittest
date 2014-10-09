#ifndef _24C512_H_
#define _24C512_H_
#include <reg51.h>
#include <intrins.h>

sbit SDA = P3^7;       
sbit SCL = P3^6;
   
void start();
void stop();
unsigned char shin();
bit shout(unsigned char write_data);
void write_byte(unsigned char device_addr, unsigned int data_addr, unsigned char write_data);

void delayms(unsigned int ms);
unsigned char read_current( unsigned char device_addr);
unsigned char read_random( unsigned char device_addr, unsigned int random_addr);
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};

#endif _24C512_H_
