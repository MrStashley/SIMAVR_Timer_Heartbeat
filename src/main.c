#include <avr/io.h>
#include <avr/interrupt.h>

#define BAUD 9600
#define TIMER1_COUNT_3_SEC 12  // F_CPU / 64 / TIMER_COMP_TIME * 3
#define TIMER_COUNT_30_MS 30   // F_CPU / 64 / 256 * (30 / 1000)
#define TIMER_COMP_TIME 65000
#define LED0 (1 << PORTB5)
#define LED1 (1 << PORTD7)

void timer1_init(void);
void setLedOn(uint8_t led);
void setLedOff(uint8_t led);
void init_trace_file(void);
void timer2_init();

uint8_t timer1_count;
uint8_t timer0_count;
uint8_t timer2_count;
uint8_t led0_count;

int main(void){
	SREG |= (1 << 7);
	led0_count = 0;
	timer0_count = 0;
	timer1_count = 0;
	timer2_count = 0;

	init_trace_file();
	timer1_init();

	while(1) {} // loop to keep program running
}

void init_trace_file(void){
	setLedOn(LED0);
	setLedOff(LED0);
}

void startTimer0(void) {
	TCCR0B |= (1 << CS01) | (1 << CS00); 	// confier ctc mode and prescaler of 64
	TCNT0 = 0; 				// init timer counter
	TIMSK0 |= (1 << TOIE0); 		// enable timer interrupt
}

void stopTimer0(void){
	TCCR0B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // clear timer mode and prescaler
	timer0_count = 0;
}


void startTimer2(void){
	TCCR2B |= (1 << CS01) | (1 << CS00); 	// confier ctc mode and prescaler of 64
	TCNT2 = 0; 				// init timer counter
	TIMSK2 |= (1 << TOIE2); 		// enable timer interrupt
}

void stopTimer2(void){
	TCCR2B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10)); // clear timer mode and prescaler
	timer2_count = 0;
}

void timer1_init(void) {
	TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); 	//Configure CTC mode, prescaler of 64
	OCR1A = TIMER_COMP_TIME; 		// Set Output Compare Register A to trigger interrupt every 65000 counts
	TCNT1 = 0;				// initialize timer counter
	TIMSK1 |= (1 << OCIE1A); 		// enable timer interrupt
}

void setLedOn(uint8_t led) {
	if(led == LED0){
		PORTB |= LED0;
		startTimer0();
	} else if (led == LED1) {
		PORTD |= LED1;
		startTimer2();
	}
}

void setLedOff(uint8_t led){
	if(led == LED0){
		PORTB &= ~(LED0);
		stopTimer0();
	} else if (led == LED1) {
		PORTD &= ~(LED1);
		stopTimer2();
	}
}

ISR(TIMER0_OVF_vect) {
	if(++timer0_count >= TIMER_COUNT_30_MS){
		setLedOff(LED0);
	}
}

ISR(TIMER2_OVF_vect) {
	if(++timer2_count >= TIMER_COUNT_30_MS){
		setLedOff(LED1);
	}
}

ISR(TIMER1_COMPA_vect){
	timer1_count++;

	if(led0_count != 0){ // blink led0 five times
		setLedOn(LED0);
		if(++led0_count > 5){
			led0_count = 0; 
		}
	}
	setLedOn(LED1); 	// blink led1
	if((timer1_count) % TIMER1_COUNT_3_SEC == 0 && led0_count == 0) {
		// proc every 3 seconds
		// start led0 procedure
		led0_count++;
		setLedOn(LED0);
	}
}

