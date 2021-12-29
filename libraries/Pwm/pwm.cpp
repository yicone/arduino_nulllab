#include "pwm.h"

#if defined(__LGT8FX8P__) || defined(__LGT8FX8E__)
// Log(HSP v3.7): PWM working mode
// Function:
//	wmode: pwm working mode
//		- PWM_MODE_NORMAL: normal single output  //单输出
//		- PWM_MODE_COMPM0: complementary dual output 
//		- PWM_MODE_COMPM1: complementary dual output (inverted)
//		- PWM_MODE_COMPM2: complementary dual output 
//		- PWM_MODE_COMPM3: complementary dual output (inverted)
//	fmode: pwm frequency settings
//		- PWM_FREQ_SLOW: slow range
//		- PWM_FREQ_NORMAL: normal range
//		- PWM_FREQ_FAST: fast range 
//		- PWM_FREQ_BOOST: boost target frequency by x4
//	dband: dead band settings
//		- only valid for complementary working mode 
// note:
//		- Timer 2 is used for system tick, so don't touch!!
//static uint8_t tmr1_boost_en = 0;
//static uint8_t tmr3_boost_en = 0;

void pwmMode(uint8_t pin, uint8_t wmode, uint8_t fmode, uint8_t dband)
{
	volatile uint8_t *pTCCRX = 0;

	uint8_t timer = digitalPinToTimer(pin) & 0xf0;

	if(timer == TIMER0) { // TIMER0
		pTCCRX = &TCCR0B;
		if(wmode == PWM_MODE_NORMAL) {
			cbi(TCCR0B, DTEN0);
			cbi(TCCR0A, COM0B0);
		} else {
			sbi(TCCR0B, DTEN0);
			TCCR0A = (TCCR0A & ~_BV(COM0B0)) | (wmode & 0x10);
			DTR0 = ((dband & 0xf) << 4) | (dband & 0xf);
		}

		if((fmode & PWM_FREQ_BOOST) == PWM_FREQ_BOOST) {
			// enable frequency boost (x4) mode
			sbi(TCKCSR, F2XEN);
			delayMicroseconds(10);
			sbi(TCKCSR, TC2XS0);					
		} else if(bit_is_set(TCKCSR, TC2XS0)) {
			cbi(TCKCSR, TC2XS0);
			delayMicroseconds(10);
			cbi(TCKCSR, F2XEN);				
		}
	} else if(timer == TIMER1) { // TIMER1
		pTCCRX = &TCCR1B;
		if(wmode == PWM_MODE_NORMAL) {
			cbi(TCCR1C, DTEN1);
			cbi(TCCR1A, COM1B0);
		} else {
			sbi(TCCR1C, DTEN1);
			TCCR1A = (TCCR1A & ~_BV(COM1B0)) | (wmode & 0x10);
			DTR1L = dband;
			DTR1H = dband;
		}
		if((fmode & PWM_FREQ_BOOST) == PWM_FREQ_BOOST) {
			sbi(TCKCSR, F2XEN);
			delayMicroseconds(10);
			sbi(TCKCSR, TC2XS1);
		} else if(bit_is_set(TCKCSR, TC2XS1)) {
			cbi(TCKCSR, TC2XS1);
			delayMicroseconds(10);
			cbi(TCKCSR, F2XEN);
		}		
	} else if(timer == TIMER3) { // TIMER3
		pTCCRX = &TCCR3B;
		if(wmode == PWM_MODE_NORMAL) {
			cbi(TCCR3C, DTEN3);
			cbi(TCCR3A, COM3B0);
		} else {
			sbi(TCCR3C, DTEN3);
			TCCR3A = (TCCR3A & ~_BV(COM3B0)) | (wmode & 0x10);
			DTR3A = dband;
			DTR3B = dband;
		}
	}

	if(pTCCRX == 0) return;

	if((fmode & 0x7f) == PWM_FREQ_SLOW) {
		*pTCCRX = (*pTCCRX & 0xf8) | PWM_FREQ_SLOW;	// prescale = 1024 (slowest mode)
	} else if((fmode & 0x7f) == PWM_FREQ_FAST) {
		*pTCCRX = (*pTCCRX & 0xf8) | PWM_FREQ_FAST; // prescale = 1 (fastest mode)
	} else if ((fmode & 0x7f) == PWM_FREQ_NORMAL) {
		*pTCCRX = (*pTCCRX & 0xf8) | PWM_FREQ_NORMAL;	// prescale = 64 (default)
	}
}

// Log(HSP v3.7): enhanced PWM settings
// Function:
//	- set PWM frequency (unit: Hz), return maximum duty cycle 
// Note: 
//	- only PWM Timer1/Timer3 support frequency update
uint16_t pwmFrequency(uint8_t pin, uint32_t fhz)
{
	uint16_t icrx = 0;
	uint8_t csxs = 0;
	uint8_t boost = 0;
	volatile uint8_t *pICRX = 0;

	uint8_t timer = digitalPinToTimer(pin) & 0xf0;

	// Note for TIMER0 
	// ============================================================================
	// timer 0 working in FPWM mode which TOP is fixed to 0xFF
	// so we can change its prescale to set frequency range (fast/normal/slow)
	// fast mode:	16000000/(1*256) = 62.5K, support boost up to 62.5x4 = 250KHz
	// normal mode:	16000000/(64*256) = 976Hz, support boost up to 3.9KHz
	// slow mode:	16000000/(1024*256) = 61Hz, support boost up to 244Hz
	// ============================================================================

	if(timer == TIMER1) { // TIMER1
		pICRX = &ICR1L;
		csxs = TCCR1B & 0x7;
		boost = bit_is_set(TCKCSR, TC2XF1);
	} else if(timer == TIMER3) { // TIMER3
		pICRX = &ICR3L;
		csxs = TCCR3B & 0x7;
	}

	if(pICRX == 0) return 0xff;

	// DO NOT try to merge the two cases, compiler will try to 
	// optimize the divider if either of oprands is constant value
	if(boost == 0) {
		if(csxs == PWM_FREQ_FAST) { // fast mode
			icrx = (uint16_t) ((F_CPU >> 1) / fhz);
		} else if(csxs == PWM_FREQ_NORMAL) { // normal mode
			icrx = (uint16_t) ((F_CPU >> 7) / fhz);
		} else if(csxs == PWM_FREQ_SLOW) { // slow mode
			icrx = (uint16_t) ((F_CPU >> 11) / fhz);
		}
	} else {
		if(csxs == PWM_FREQ_FAST) { // fast mode
			icrx = (uint16_t) ((64000000UL >> 1) / fhz);
		} else if(csxs == PWM_FREQ_NORMAL) { // normal mode
			icrx = (uint16_t) ((64000000UL >> 7) / fhz);
		} else if(csxs == PWM_FREQ_SLOW) { // slow mode
			icrx = (uint16_t) ((64000000UL >> 11) / fhz);
		}	
	}
	
	atomicWriteWord(pICRX, icrx);

	return icrx;
}

// Log(HSP v3.7):
// Function:
//	- return frequency (in Hz) by give PWM resolution (bits width of duty)
// Note: 
//	- timer0/2 works in FPWM mode, pwm frequency is fixed by given mode
//	- timer1/3 works in PCPWM mode, means frequency reduced by a half
uint32_t pwmResolution(uint8_t pin, uint8_t resBits)
{
	uint8_t csxs = 0;
	uint8_t boost = 0;
	uint32_t freq = 0x0UL;

	uint8_t timer = digitalPinToTimer(pin) & 0xf0;

	if(timer != TIMER1 && timer != TIMER3)
		return 0x0UL;

	if(timer == TIMER1) { // TIMER1
		csxs = TCCR1B & 0x7;
		boost = bit_is_set(TCKCSR, TC2XF1);
	} else if(timer == TIMER3) { // TIMER3
		csxs = TCCR3B & 0x7;
	}	
	
	if(boost != 0) {
		if(csxs == PWM_FREQ_FAST) {
			freq = (64000000UL >> 1) / (1 << resBits);
		} else if(csxs == PWM_FREQ_SLOW) {
			freq = (64000000UL >> 11) / (1 << resBits);
		} else { // PWM_FREQ_NORMAL
			freq = (64000000UL >> 7) / (1 << resBits);
		}
	} else {
		if(csxs == PWM_FREQ_FAST) {
			freq = (F_CPU >> 1) / (1 << resBits);
		} else if(csxs == PWM_FREQ_SLOW) {
			freq = (F_CPU >> 11) / (1 << resBits);
		} else { // PWM_FREQ_NORMAL
			freq = (F_CPU >> 7) / (1 << resBits);
		}
	}

	// update pwm frequency
	pwmFrequency(pin, freq);

	return freq;
}
#endif