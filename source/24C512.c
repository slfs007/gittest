#include "24C512.H"
void start()
{
 SDA = 1;
 SCL = 1;
 delayNOP();
 SDA = 0;
 delayNOP();
 SCL = 0;
}

void stop()
{
 SDA = 0;
 delayNOP();
 SCL = 1;
 delayNOP();
 SDA = 1;
}

unsigned char shin()
{
	unsigned char i,read_data;
	for(i = 0; i < 8; i++)
	{
	SCL = 1;
	read_data <<= 1;
	//  read_data |= (unsigned char)SDA;
	read_data |= SDA;
	SCL = 0;
 }
 return(read_data);
}

bit shout(unsigned char write_data) 
{
	unsigned char i;
	bit ack_bit;
	for(i = 0; i < 8; i++)  // ????8??
	{
		SDA = (bit)(write_data & 0x80);
		_nop_();
		SCL = 1;
		delayNOP();
		SCL = 0;
		write_data <<= 1;
	}
	SDA = 1;  
	delayNOP();
	SCL = 1;
	delayNOP();
	ack_bit = SDA;
	SCL = 0;
	return ack_bit; 
}
void write_byte( unsigned char device_addr, unsigned int data_addr, unsigned char write_data)
{
	start();
	
	shout(0xa0 | (device_addr << 1));//10100 [dev_bit1] [dev_bit2] [w/r]
	
	shout(data_addr >> 8);
	shout(data_addr & 0xff);
	shout(write_data);
	stop();
	delayms(10); 
}

unsigned char read_current( unsigned char device_addr)
{
	unsigned char read_data;
	start();
	shout(0xa1 | (device_addr << 1));//10100 [dev_bit1] [dev_bit2] [1]
	read_data = shin();
	stop();
	return read_data;
}
unsigned char read_random( unsigned char device_addr, unsigned int random_addr)
{
	start();
	shout( 0xa0 | (device_addr << 1));
	shout(random_addr >> 8);
	shout(random_addr & 0xff);
	return(read_current( device_addr));
}
void delayms(unsigned int ms) 
{
 unsigned char k;
 while(ms--)
 {
  for(k = 0; k < 120; k++);
 }
}
