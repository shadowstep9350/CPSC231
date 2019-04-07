#include <asf.h>

#define PMWA IOPORT_CREATE_PIN(PIOA, 23)
#define PMWB IOPORT_CREATE_PIN(PIOA, 19)

pwm_channel_t pwm_opts;

int motor(void){
	
	sysclk_init();
	board_init();
	
	//PWM Clock options
	pwm_clock_t pwm_clock_opts = {
		.ul_clka = 10000, //10Khz frequency = .1 ms steps
		.ul_clkb = 0,
		.ul_mck =  sysclk_get_main_hz() //main clock speed is 240Mhz!, not 120mhz
	};
	
	//PWM options
	pwm_opts.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_opts.ul_period = 200; //20ms period
	pwm_opts.ul_duty = 0;
	pwm_opts.channel = PWM_CHANNEL_0;
	
	//configure IO pins
	pio_configure_pin( PMWA, PIO_TYPE_PIO_PERIPH_B );
	pio_configure_pin( PMWB, PIO_TYPE_PIO_PERIPH_B );
	
	//Enable PWM clock
	pmc_enable_periph_clk(ID_PWM);
	
	//disable temporarily
	pwm_channel_disable(PWM, PWM_CHANNEL_0);
	
	//Start PWM
	pwm_init( PWM, &pwm_clock_opts );
	pwm_channel_init( PWM, &pwm_opts );
	pwm_channel_enable( PWM, PWM_CHANNEL_0 );
	
	uint32_t duty;
	
	/*while(true){
		pwm_channel_update_duty( PWM, &pwm_opts, duty = 3 ); // 0 degrees = .6ms high = 3% duty cycle
		delay_ms(1000);
		
		pwm_channel_update_duty( PWM, &pwm_opts, duty = 8 ); // 90 degrees = 1.5ms high = ~8% duty cycle
		delay_ms(1000);
		
		//pwm_channel_update_duty( PWM, &pwm_opts, duty = 12.5 ); // 180 degrees = 2.4ms high = 12% duty cycle
		//delay_ms(1500);
		
		
	}*/
}