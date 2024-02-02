/*
 * smartWatch.c
 *
 *  Created on: 2 Feb 2024
 *      Author: Salah Bendary
 */

#include<avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define SEVEN_SEGMENT_DELAY 4

typedef unsigned char uint8;
volatile uint8 incrementFlag;
volatile struct time {
    uint8 hour_one;
    uint8 hour_zero;
    uint8 minute_one;
    uint8 minute_zero;
    uint8 second_one;
    uint8 second_zero;
} *TimeCalculation;

volatile struct time currentTime = {0, 0, 0, 0, 0, 0};

int main(void) {
    TimeCalculation = &currentTime;
    SevenSegmentInit();
    Timer1_COMP_Init();
	INT1_Init();
	INT0_Init();
	INT2_Init();
	PORTC &= 0xF0;
	PORTA &= 0xC0;
	while (1) {
		SevenSegmentTimecalculations();
	    SevenSegmentDisplay();
	}
    return 0;
}

void INT0_Init(void);
void INT1_Init(void);
void INT2_Init(void);
void Timer1_COMP_Init(void);
void SevenSegmentInit(void);
void SevenSegmentDisplay(void);
void SevenSegmentTimecalculations(void);

/* Description:
 * For System Clock = 1Mhz and prescaler F_CPU/1024.
 * Timer frequency will be around 1Khz, Ttimer = 1ms
 * For compare value approx equals to (977) the timer will generate compare match interrupt every 1 sec.
 * Compare interrupt will be generated every 1sec.
 */

/* Timer One Interrupt Service Routine */
ISR(TIMER1_COMPA_vect) {
	incrementFlag = 1;                         /* ISR only sets a flag to indicate that an increment is needed */
}
/* External INT1 Interrupt Service Routine */
ISR(INT1_vect) {
	TCCR1B &= ~(1 << CS10) & ~(1 << CS12);     /* Stop Watch time should be paused. by making CS10 = 0 and CS12 = 0 and we use OR equal to save other values of this register */
}
/* External INT0 Interrupt Service Routine */
ISR(INT0_vect) {                              /* Stop Watch time should be reset by making the timer values equal to zero */
	TimeCalculation->hour_one = 0;
	TimeCalculation->hour_zero = 0;
	TimeCalculation->minute_one = 0;
	TimeCalculation->minute_zero = 0;
	TimeCalculation->second_one = 0;
	TimeCalculation->second_zero = 0;
}
/* External INT2 Interrupt Service Routine */
ISR(INT2_vect) {
	TCCR1B |= (1 << CS12) | (1 << CS10);     /* Stop Watch time should be Resume. by making CS10 = 1 and CS12 = 1 and we use OR equal to save other values of this register */
}


/* Interrupt 1 Raising edge
External INT1 enable and configuration function */
void INT1_Init(void) {
DDRD &= (~(1 << PD3));                   /* Configure INT1/PD3 as input pin */
MCUCR |= (1 << ISC11) | (1 << ISC10);    /* Trigger INT1 with the raising edge */
GICR |= (1 << INT1); 				    /* Enable external interrupt pin INT1 */
}

/* Both Interrupt 0 & Interrupt 2 Falling edge
External INT0 enable and configuration function */
void INT0_Init(void) {
DDRD &= (~(1 << PD2));                  /* Configure INT0/PD2 as input pin */
MCUCR |= (1 << ISC01);                  /* Trigger INT0 with the raising edge */
GICR |= (1 << INT0);                    /* Enable external interrupt pin INT0 */
PORTD |= (1 << PD2);                    /* Internal  pull-up resistor */
}

/* External INT2 enable and configuration function */
void INT2_Init(void) {
DDRB &= (~(1 << PD2));                  /* Configure INT2/PB2 as input pin */
GICR |= (1 << INT2);                    /* Enable external interrupt pin INT2 */
PORTB |= (1 << PD2);                    /* Internal  pull-up resistor */
}
void Timer1_COMP_Init(void) {

	TCNT1 = 0;                              /* Set Timer1 initial value to 0 */
	OCR1A = 977;                            /* Set Timer compare value to 977  */
	TIMSK = (1 << OCIE1A);                   /* Enable Timer1 Compare Interrupt  */
	sei();
	/* Configure timer1 control register
	 * 1. Non PWM mode FOC1A for Register A =1
	 * 2. CTC Mode WGM012 where Top value = OCR1A
	 * 3. No need for OC0 in this example so COM1A1/COM1B1 = 0, COM1A0/COM1B0 = 0
	 * 4. clock = F_CPU/1024 CS12=1 CSCS11=0 CS10=1
	 */
	TCCR1A = (1 << FOC1A);
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);

}
void SevenSegmentInit(void) {
	/* Initialization of SevenSegments and decoder */
	DDRC |= 0x0F;
	DDRA |= 0x3F;
}
void SevenSegmentDisplay(void) {
		// Applying Multiplexing method
		PORTA = (PORTA & 0xC0) | (1 << 0);  /* PORTA = 0xC0 */
		PORTC = (PORTC & 0xF0) | (TimeCalculation->second_zero & 0x0F);
		_delay_ms(SEVEN_SEGMENT_DELAY);

		PORTA = (PORTA & 0xC0) | (1 << 1);  /* PORTA = 0xC1 */
		PORTC = (PORTC & 0xF0) | (TimeCalculation->second_one & 0x0F);
		_delay_ms(SEVEN_SEGMENT_DELAY);

		PORTA = (PORTA & 0xC0) | (1 << 2);  /* PORTA = 0xC4 */
		PORTC = (PORTC & 0xF0) | (TimeCalculation->minute_zero & 0x0F);
		_delay_ms(SEVEN_SEGMENT_DELAY);

		PORTA = (PORTA & 0xC0) | (1 << 3);  /* PORTA = 0xC8 */
		PORTC = (PORTC & 0xF0) | (TimeCalculation->minute_one & 0x0F);
		_delay_ms(SEVEN_SEGMENT_DELAY);

		PORTA = (PORTA & 0xC0) | (1 << 4);  /* PORTA = 0xD0 */
		PORTC = (PORTC & 0xF0) | (TimeCalculation->hour_zero & 0x0F);
		_delay_ms(SEVEN_SEGMENT_DELAY);

		PORTA = (PORTA & 0xC0) | (1 << 5);  /* PORTA = 0xE0 */
		PORTC = (PORTC & 0xF0) | (TimeCalculation->hour_one & 0x0F);
		_delay_ms(SEVEN_SEGMENT_DELAY);
}

/* Time Calculations for seconds, minutes, hours  */
void SevenSegmentTimecalculations(void) {
    if (incrementFlag == 1) { // Checking the flag
        TimeCalculation->second_zero++;
        incrementFlag = 0;
    }

    if (TimeCalculation->second_zero == 10) {
        TimeCalculation->second_zero = 0;
        TimeCalculation->second_one += 1;
    }

    if (TimeCalculation->second_one == 6) {
        TimeCalculation->second_one = 0;
        TimeCalculation->minute_zero += 1;
    }

    if (TimeCalculation->minute_zero == 10) {
        TimeCalculation->minute_zero = 0;
        TimeCalculation->minute_one += 1;
    }

    if (TimeCalculation->minute_one == 6) {
        TimeCalculation->minute_one = 0;
        TimeCalculation->hour_zero += 1;
    }

    if (TimeCalculation->hour_zero == 10) {
        TimeCalculation->hour_zero = 0;
        TimeCalculation->hour_one += 1;
    }

    if (TimeCalculation->hour_one == 10) {
        TimeCalculation->hour_one = 0;
        TimeCalculation->hour_zero = 0;
        TimeCalculation->minute_one = 0;
        TimeCalculation->minute_zero = 0;
        TimeCalculation->second_one = 0;
        TimeCalculation->second_zero = 0;
    }
}


