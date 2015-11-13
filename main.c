 #include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include <stdlib.h>

#define E6_on PORTE |= (1<<PINE6);
#define E6_off PORTE &= ~(1<<PINE6);


void sleep_ms(uint16_t ms);
void sleep_us(uint16_t us);
void servo_set (uint8_t servo_NR,int16_t servo_position);



int main(void)
{
	MCUCR = (1 << JTD); MCUCR = (1 << JTD); //disable jtag
	MCUCR = (1 << JTD); MCUCR = (1 << JTD); //disable jtag
	clock_prescale_set(clock_div_1); //set clock prescaler to 1 (CPU-clock to 16MHz)

	DDRE |= (1 << DDE6) ;//port e 6  als  ausgang
	DDRB = 0xff; //alle als ausgang
	


    while(1)
    {
	servo_set(0,80);//bremse unten
	servo_set(1,120);//gas unten
	sleep_ms(20);
	sleep_ms(6150);
	
	
	servo_set(0,250);//bremse oben
	servo_set(1,-100);//gas oben//-220 || 120
	sleep_ms(20);
	sleep_ms(25000);
	
	

    //quit old game
	servo_set(1,120);//gas unten
	sleep_ms(100);
	servo_set(1,-100);//gas oben
	sleep_ms(500);
	
	//start new game
	servo_set(1,120);//gas unten
	sleep_ms(100);
	servo_set(1,-100);//gas oben
	sleep_ms(100);	

	//wait for new game to start
	sleep_ms(1000);
	
	
	}

}     


/* sleep schlaufe */
void sleep_us(uint16_t us){
	while(us){
		us--;
		_delay_us(1);
	}
}
/* sleep schlaufe */
void sleep_ms(uint16_t ms){
	while(ms){
		ms--;
		_delay_ms(1);
	}
}


void servo_set (uint8_t servo_NR,int16_t servo_position)
{
	
	if (servo_NR < 0 || servo_NR > 8){return;} //servonummer falsch || keine pos. angegeben
		
	PORTB |= (1<<servo_NR); //servo pin high
	sleep_us (750+servo_position);
	PORTB &= ~(1<<servo_NR);  //servo pin low
}
