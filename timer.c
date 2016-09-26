#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


void Timer1Config(int ms){

	TCNT1 = 0;
	TCCR1B |= (1 << WGM12); // Configure timer1 for CTC mode
	TCCR1B |= (1 << CS12)|(1 << CS10); // Start timer at F_CPU/1024
	TIMSK1 |= (1 << OCIE1A);
	OCR1A = ms*(F_CPU/1024/1000); 

	sei();
}
