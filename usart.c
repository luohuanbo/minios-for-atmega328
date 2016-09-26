#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>


//#define BAUDRATE	9600
//#define BAUDRATE	14400
//#define BAUDRATE	19200
//#define BAUDRATE	28800
//#define BAUDRATE	38400
#define BAUDRATE	57600

#define BIT(bit)	(1 << bit)
#define SET(ctl, bits)	(ctl |= bits)
#define CLR(ctl, bits)	(ctl &= ~bits)
#define WAIT_USART()	while ( !( UCSR0A & BIT(UDRE0) ) )


int fputc(int data,FILE *f)  
{  
	WAIT_USART();
	UDR0 = (data=='\r') ? '\n' : data;

	return data;
}  
  

void UsartConfig()
{
	// 设置波特率UBRR
	UBRR0L = F_CPU/16/BAUDRATE -1;
	UBRR0H = (F_CPU/16/BAUDRATE -1)>>8;

	// 设置USART
	SET(UCSR0B, BIT(RXEN0)+BIT(TXEN0)+BIT(RXCIE0) );
	
	fdevopen((int (*)(char, FILE*))fputc,0);

	sei();	// 开启中断
}


ISR(USART_RX_vect)
{
	putchar(UDR0);

}
