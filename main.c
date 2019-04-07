#include <asf.h>
#include <Motor.c>
#include <string.h>

#define LED1 IOPORT_CREATE_PIN(PIOC, 20)
#define LED2 IOPORT_CREATE_PIN(PIOA, 16)
#define LED3 IOPORT_CREATE_PIN(PIOC, 22)

#define PMWL0 IOPORT_CREATE_PIN(PIOA, 19)
#define PMWL1 IOPORT_CREATE_PIN(PIOA, 20)
#define PMWL2 IOPORT_CREATE_PIN(PIOA, 30)

#define PMWL0_PERIPHERAL PIO_TYPE_PIO_PERIPH_B
#define PMWL1_PERIPHERAL PIO_TYPE_PIO_PERIPH_B
#define PMWL2_PERIPHERAL PIO_TYPE_PIO_PERIPH_A

#define PWML0_CHANNEL PWM_CHANNEL_0
#define PWML1_CHANNEL PWM_CHANNEL_1
#define PWML2_CHANNEL PWM_CHANNEL_2

void Button_Handler(uint32_t id, uint32_t mask){
	uint32_t led;

	if(ID_PIOA == id && PIO_PA0 == mask){led = LED1;}
	else if(ID_PIOC == id && PIO_PC29 == mask){led = LED2;}
	else if(ID_PIOC == id && PIO_PC30 == mask){led = LED3;}
	else{return;}
	
	ioport_set_pin_level(led, !ioport_get_pin_level(led));
}

void configure_buttons(void){
	const uint32_t irq_priority = 5;
	//Configure Pushbutton 1
	pmc_enable_periph_clk(ID_PIOA);
	pio_set_debounce_filter(PIOA, PIN_PUSHBUTTON_1_MASK, 10);
	pio_handler_set(PIOA, ID_PIOA,
	PIN_PUSHBUTTON_1_MASK, PIN_PUSHBUTTON_1_ATTR, Button_Handler);
	NVIC_EnableIRQ((IRQn_Type) ID_PIOA);
	pio_handler_set_priority(PIOA, (IRQn_Type) ID_PIOA, irq_priority);
	pio_enable_interrupt(PIOA, PIN_PUSHBUTTON_1_MASK);

	//Configure Pushbutton 2
	pmc_enable_periph_clk(ID_PIOC);
	pio_set_debounce_filter(PIOC, PIN_PUSHBUTTON_2_MASK, 10);
	pio_handler_set(PIOC, ID_PIOC,
	PIN_PUSHBUTTON_2_MASK, PIN_PUSHBUTTON_2_ATTR, Button_Handler);
	NVIC_EnableIRQ((IRQn_Type) ID_PIOC);
	pio_handler_set_priority(PIOC, (IRQn_Type) ID_PIOC, irq_priority);
	pio_enable_interrupt(PIOC, PIN_PUSHBUTTON_2_MASK);

	//Configure Pushbutton 3
	pmc_enable_periph_clk(ID_PIOC);
	pio_set_debounce_filter(PIOC, PIN_PUSHBUTTON_3_MASK, 10);
	pio_handler_set(PIOC, ID_PIOC,
	PIN_PUSHBUTTON_3_MASK, PIN_PUSHBUTTON_3_ATTR, Button_Handler);
	NVIC_EnableIRQ((IRQn_Type) ID_PIOC);
	pio_handler_set_priority(PIOC, (IRQn_Type) ID_PIOC, irq_priority);
	pio_enable_interrupt(PIOC, PIN_PUSHBUTTON_3_MASK);
}

void printOLED(uint32_t row, uint32_t col, uint32_t text){
	ssd1306_set_page_address(row);
	ssd1306_set_column_address(col);
	ssd1306_write_text(text);
}

void typeScreen(void){
	printOLED(3,0,"Type");
	printOLED(3,45,"Quantity");
	printOLED(3,114,"Roll");
}

void quantityScreen(void){
	printOLED(3,0,"Increase");
	printOLED(3,55,"Back");
	printOLED(3,88,"Decrease");
}

void displayAllTypes(void){
	printOLED(0,0,"4-Sided");
	printOLED(1,0,"6-Sided");
	printOLED(2,0,"8-Sided");
	printOLED(0,55,"10-Sided");
	printOLED(1,55,"12-Sided");
	printOLED(2,55,"20-Sided");
}

void displayAllQty(uint8_t qt1, uint8_t qt2, uint8_t qt3, uint8_t qt4, uint8_t qt5, uint8_t qt6){
	char num[5];
	printOLED(0,39,itoa(qt1, num, 10));
	printOLED(1,39,itoa(qt2, num, 10));
	printOLED(2,39,itoa(qt3, num, 10));
	printOLED(0,100,itoa(qt4, num, 10));
	printOLED(1,100,itoa(qt5, num, 10));
	printOLED(2,100,itoa(qt6, num, 10));
}

void standardDisplay(uint8_t qt1, uint8_t qt2, uint8_t qt3, uint8_t qt4, uint8_t qt5, uint8_t qt6){
	displayAllTypes();
	displayAllQty(qt1, qt2, qt3, qt4, qt5, qt6);
	delay_ms(300);
	ssd1306_clear();
}

void blinkTypes(uint8_t D4, uint8_t D6, uint8_t D8, uint8_t D10, uint8_t D12, uint8_t D20, uint8_t qt1, uint8_t qt2, uint8_t qt3, uint8_t qt4, uint8_t qt5, uint8_t qt6){
	typeScreen();
	standardDisplay(qt1, qt2, qt3, qt4, qt5, qt6);
	if(D4 == 1){printOLED(0,0,"4-Sided");}
	if(D6 == 1){printOLED(1,0,"6-Sided");}
	if(D8 == 1){printOLED(2,0,"8-Sided");}
	if(D10 == 1){printOLED(0,55,"10-Sided");}
	if(D12 == 1){printOLED(1,55,"12-Sided");}
	if(D20 == 1){printOLED(2,55,"20-Sided");}
	displayAllQty(qt1, qt2, qt3, qt4, qt5, qt6);
	typeScreen();
	delay_ms(300);
	ssd1306_clear();
}

void blinkQuantity(uint8_t D4, uint8_t D6, uint8_t D8, uint8_t D10, uint8_t D12, uint8_t D20, uint8_t qt1, uint8_t qt2, uint8_t qt3, uint8_t qt4, uint8_t qt5, uint8_t qt6){
	char num[5];
	quantityScreen();
	standardDisplay(qt1, qt2, qt3, qt4, qt5, qt6);
	displayAllTypes();
	if(D4 == 1){printOLED(0,39,itoa(qt1, num, 10));}
	if(D6 == 1){printOLED(1,39,itoa(qt2, num, 10));}
	if(D8 == 1){printOLED(2,39,itoa(qt3, num, 10));}
	if(D10 == 1){printOLED(0,100,itoa(qt4, num, 10));}
	if(D12 == 1){printOLED(1,100,itoa(qt5, num, 10));}
	if(D20 == 1){printOLED(2,100,itoa(qt6, num, 10));}
	quantityScreen();
	delay_ms(300);
	ssd1306_clear();
}
void displayAll(uint8_t qt1, uint8_t qt2, uint8_t qt3, uint8_t qt4, uint8_t qt5, uint8_t qt6){
	ssd1306_clear();
	displayAllTypes();
	displayAllQty(qt1, qt2, qt3, qt4, qt5, qt6);
}

void centerServos(void){
	pwm_opts.channel = PWML0_CHANNEL;
	pwm_channel_update_duty( PWM, &pwm_opts, 8);
	
	pwm_opts.channel = PWML1_CHANNEL;
	pwm_channel_update_duty( PWM, &pwm_opts, 8);
	
	pwm_opts.channel = PWML2_CHANNEL;
	pwm_channel_update_duty( PWM, &pwm_opts, 8);
}

void initAll(void){ //Initializes Channels, Pins, Etc.
	sysclk_init();
	board_init();
	ssd1306_init();
	ssd1306_clear();
	configure_buttons();
	
}

int main(void){
	uint8_t type=0,quantitySel=0,i=0,D4=0,D6=0,D8=0,D10=0,D12=0,D20=0;
	
	initAll();
	
	pwm_clock_t pwm_clock_opts = {.ul_clka = 10000,.ul_clkb = 0,.ul_mck =  sysclk_get_main_hz()};
	pwm_channel_t pwm_opts = {.ul_prescaler = PWM_CMR_CPRE_CLKA,.ul_period	= 200,.ul_duty = 0};
	
	pio_configure_pin(PMWL0, PMWL0_PERIPHERAL);
	pio_configure_pin(PMWL1, PMWL1_PERIPHERAL);
	pio_configure_pin(PMWL2, PMWL2_PERIPHERAL);
	
	pmc_enable_periph_clk(ID_PWM);
	
	pwm_channel_disable(PWM, PWML0_CHANNEL);
	pwm_channel_disable(PWM, PWML1_CHANNEL);
	pwm_channel_disable(PWM, PWML2_CHANNEL);
	
	pwm_init( PWM, &pwm_clock_opts );
	
	pwm_opts.channel = PWML0_CHANNEL;
	pwm_channel_init(PWM, &pwm_opts);
	pwm_channel_enable(PWM, PWML0_CHANNEL);
	
	pwm_opts.channel = PWML1_CHANNEL;
	pwm_channel_init(PWM, &pwm_opts);
	pwm_channel_enable(PWM, PWML1_CHANNEL);
	
	pwm_opts.channel = PWML2_CHANNEL;
	pwm_channel_init(PWM, &pwm_opts);
	pwm_channel_enable(PWM, PWML2_CHANNEL);
	
	pwm_opts.channel = PWML0_CHANNEL;
	pwm_channel_update_duty( PWM, &pwm_opts, 8);
	
	pwm_opts.channel = PWML1_CHANNEL;
	pwm_channel_update_duty( PWM, &pwm_opts, 8);
	
	pwm_opts.channel = PWML2_CHANNEL;
	pwm_channel_update_duty( PWM, &pwm_opts, 8);
	
	while(1){
		if(quantitySel == 0){
			if(type==0){blinkTypes(0,1,1,1,1,1,D4,D6,D8,D10,D12,D20);}
			if(type==1){blinkTypes(1,0,1,1,1,1,D4,D6,D8,D10,D12,D20);}
			if(type==2){blinkTypes(1,1,0,1,1,1,D4,D6,D8,D10,D12,D20);}
			if(type==3){blinkTypes(1,1,1,0,1,1,D4,D6,D8,D10,D12,D20);}
			if(type==4){blinkTypes(1,1,1,1,0,1,D4,D6,D8,D10,D12,D20);}
			if(type==5){blinkTypes(1,1,1,1,1,0,D4,D6,D8,D10,D12,D20);}
				
			if(ioport_get_pin_level(LED1)==0){
				ioport_set_pin_level( LED1, 1);
				type++;
				if(type==6){type=0;}	
			}
				
			if(ioport_get_pin_level(LED2)==0){
				ioport_set_pin_level( LED2, 1);
				ssd1306_clear();
				quantitySel = 1;
			}
			if(ioport_get_pin_level(LED3)==0){
				
				ioport_set_pin_level( LED3, 1);
				displayAll(D4,D6,D8,D10,D12,D20);
				
				for(i=D4;i > 0;i--){
					
					pwm_opts.channel = PWML0_CHANNEL;
					pwm_channel_update_duty(PWM, &pwm_opts, 3);
					delay_ms(1000);
	
					pwm_opts.channel = PWML0_CHANNEL; 
					pwm_channel_update_duty(PWM, &pwm_opts, 7.9);
					delay_ms(1200);
					D4--;
					
					displayAll(D4,D6,D8,D10,D12,D20);
				}
					
				for(i=D6;i > 0;i--){
					
					pwm_opts.channel = PWML0_CHANNEL;
					pwm_channel_update_duty(PWM, &pwm_opts, 13);
					delay_ms(1000);
	
					pwm_opts.channel = PWML0_CHANNEL; 
					pwm_channel_update_duty(PWM, &pwm_opts, 7.90);
					delay_ms(1200);
					D6--;
					
					displayAll(D4,D6,D8,D10,D12,D20);
				}	
				
				for(i=D8;i > 0;i--){
					
					pwm_opts.channel = PWML1_CHANNEL;
					pwm_channel_update_duty(PWM, &pwm_opts, 3);
					delay_ms(1000);
	
					pwm_opts.channel = PWML1_CHANNEL; 
					pwm_channel_update_duty(PWM, &pwm_opts, 8);
					delay_ms(1000);
					D8--;
					
					displayAll(D4,D6,D8,D10,D12,D20);
				}	
				
				for(i=D10;i > 0;i--){
					
					pwm_opts.channel = PWML1_CHANNEL;
					pwm_channel_update_duty(PWM, &pwm_opts, 13);
					delay_ms(1000);
	
					pwm_opts.channel = PWML1_CHANNEL; 
					pwm_channel_update_duty(PWM, &pwm_opts, 8);
					delay_ms(1000);
					D10--;
					
					displayAll(D4,D6,D8,D10,D12,D20);
				}	
				
				for(i=D12;i > 0;i--){
					
					pwm_opts.channel = PWML2_CHANNEL;
					pwm_channel_update_duty(PWM, &pwm_opts, 3);
					delay_ms(1000);
	
					pwm_opts.channel = PWML2_CHANNEL; 
					pwm_channel_update_duty(PWM, &pwm_opts, 8);
					delay_ms(1000);
					D12--;
					
					displayAll(D4,D6,D8,D10,D12,D20);
				}	
				
				for(i=D20;i > 0;i--){
					
					pwm_opts.channel = PWML2_CHANNEL;
					pwm_channel_update_duty(PWM, &pwm_opts, 13);
					delay_ms(1000);
	
					pwm_opts.channel = PWML2_CHANNEL; 
					pwm_channel_update_duty(PWM, &pwm_opts, 8);
					delay_ms(1000);
					D20--;
					
					displayAll(D4,D6,D8,D10,D12,D20);
				}	
			}
		}
		if(quantitySel == 1){
			
			if(type==0){blinkQuantity(0,1,1,1,1,1,D4,D6,D8,D10,D12,D20);}
			if(type==1){blinkQuantity(1,0,1,1,1,1,D4,D6,D8,D10,D12,D20);}
			if(type==2){blinkQuantity(1,1,0,1,1,1,D4,D6,D8,D10,D12,D20);}
			if(type==3){blinkQuantity(1,1,1,0,1,1,D4,D6,D8,D10,D12,D20);}
			if(type==4){blinkQuantity(1,1,1,1,0,1,D4,D6,D8,D10,D12,D20);}
			if(type==5){blinkQuantity(1,1,1,1,1,0,D4,D6,D8,D10,D12,D20);}
				
			if(ioport_get_pin_level(LED1)==0){
				
				ioport_set_pin_level( LED1, 1);
				if(type == 0){D4++;}
				if(type == 1){D6++;}
				if(type == 2){D8++;}
				if(type == 3){D10++;}
				if(type == 4){D12++;}
				if(type == 5){D20++;}
			}
			
			if(ioport_get_pin_level(LED2)==0){
				ioport_set_pin_level( LED2, 1);
				ssd1306_clear();
				quantitySel = 0;
			}
			
			if(ioport_get_pin_level(LED3)==0){
				ioport_set_pin_level( LED3, 1);
				if(type == 0){D4--;}
				if(type == 1){D6--;}
				if(type == 2){D8--;}
				if(type == 3){D10--;}
				if(type == 4){D12--;}
				if(type == 5){D20--;}	
			}
		}
	}
}