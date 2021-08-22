#include "STM32FDiscovery.h"

int count1 = 0;
int count2 = 0;
volatile int i = 0;
int count3 = 0;
int index1 = 0;
int index2 = 0;
int process_data = 0;
char buffer[30] = "";
char data;
char *help_text = "help";
char *enter = "\n<< ";
char *error = "Invalid input. Please check the command by entering 'help' or 'HELP'.\n>> ";
char *LED1 = "THE GREEN LED IS ON.\n>> ";
char *LED2 = "THE ORANGE LED IS ON.\n>> ";
char *LED3 = "THE RED LED IS ON.\n>> ";
char *LED4 = "THE BLUE LED IS ON.\n>> ";
char *LED5 = "THE GREEN LED IS OFF.\n>> ";
char *LED6 = "THE ORANGE LED IS OFF.\n>> ";
char *LED7 = "THE RED LED IS OFF.\n>> ";
char *LED8 = "THE BLUE LED IS OFF.\n>> ";
char *LED9 = "ALL LEDS ARE ON.\n>> ";
char *LED10 = "ALL LEDS ARE OFF.\n>> ";
char *LED11 = "ALL LEDS ARE TOGGLE.\n>> ";  

unsigned int uart_data[114]= { 
47 ,42 ,42 ,42, 42, 42, 42, 42, 42, 42, 
42 ,42 ,42 ,42, 42, 42, 42, 42, 42, 42, 
42 ,42 ,42 ,42, 42, 42, 42, 42, 42, 42, 
42 ,42 ,42 ,42, 47, 10, 47, 42, 32, 76, 
69 ,68 ,32 ,99, 111, 110, 116, 114, 111, 
108 ,32 ,83 ,104, 101, 108, 108, 32, 102, 
111 ,114, 32, 83, 84, 77, 51, 50, 70, 52, 
32 ,42 ,47 ,10 ,47 ,42 ,42 ,42 ,42 ,42 ,
42 ,42 ,42 ,42 ,42 ,42 ,42 ,42 ,42 ,42 ,
42 ,42 ,42 ,42 ,42 ,42 ,42 ,42 ,42 ,42 ,
42 ,42 ,42 ,42 ,42 ,42 ,42 ,42 ,47, 10, 62, 62, 32}; // reset interrupt messages

char help[400] = "* Command List\n - LEDON\n   + argument [1, 2, 3, 4]\n - LEDOFF\n   + argument [1, 2, 3, 4]\n - LEDON ALL\n   + no argumnet\n - LEDOFF ALL\n   + no argumnet\n - LED TOGGLE\n   + no argument\n>> "; // help messages

void clk(void)
{
	RCC_CR = 0;
	RCC_PLLCFGR = 0;
	RCC_CFGR = 0;
		
	RCC_CR |= (1<<16); // HSE set
	while( (RCC_CR & ( 1<<17) ) == 0 ); // wait until HSE ready
	
	RCC_PLLCFGR |= 8;//0x00000008; // set PLLM
	RCC_PLLCFGR |= (336<<6);//|= (336<<6); // 		set PLLN
	RCC_PLLCFGR |= (0<<16); // set PLLP
	RCC_PLLCFGR |= (7<<24);//0x07000000; // set PLLQ

	RCC_PLLCFGR |= (1<<22); // set PLL src HSE
	

	RCC_CR |= (1<<24); // PLL ON
	while( (RCC_CR & (1<<25)) == 0); // wait until PLL ready
	
	FLASH_ACR |= 5;
	RCC_CFGR |= 2; // set PLL to system clock
	
		
	while( (RCC_CFGR & (12) ) != 8); // wait until PLL ready
	
	RCC_CFGR |= (1<<12) | (1<<10); // set APB1 div 4
	RCC_CFGR |= (1<<15); // set APB2 div2	
}

void set_usart2() {
    // USART PA2, PA3
    RCC_AHB1ENR     |= 1<<0;
    GPIOA_MODER     |= (1<<5) | (1<<7); // use alternate mode PA2, PA3
    GPIOA_AFRL      |= (7<<8) | (7<<12); // use Alternate function 7

    // set USART2
    RCC_APB1ENR     |= (1<<17); // usart2 clk enable
    USART2_CR1      |= (0<<12);
    USART2_CR2      |= (0<<13) | (0<<12);

    USART2_BRR      |= (unsigned int)(42000000/115200);

    USART2_CR1      |= (1<<3) | (1<<2); // tx enable, rx enable 
    USART2_CR1      |= (1<<5); // RXNE interrupt enable by using interrupt mode not polling
    USART2_CR1      |= (1<<13); // USART enable 

    // USART interrupt enable
    NVIC_ISER1      |= 1<<6 ; // why using 6?? because ISER1 0~31, ISER1 start to 32 so can use 6


}

char USART2_receive(void){
    while(!(USART2_SR & (1<<5))); // checking being ready for reception
        return USART2_DR;
}

void USART2_transmit(char data){
    USART2_DR = data;
    while ( !(USART2_SR & (1<<7)) ); // checking transmission
    while ( !(USART2_SR & (1<<6)) ); // checking transmission
}

void USART2_print_string(char *str){ // transmit string
    for(int i=0; str[i]; i++)
        USART2_transmit(str[i]);
}

void USART2_IRQHandler() {
        data = USART2_receive();
    
        USART2_DR = data;
        while ( !(USART2_SR & (1<<7)) ); // checkng transmission
        while ( !(USART2_SR & (1<<6)) );

        buffer[index1] = data;
        index1++;

        if(data == '\r'){
            USART2_print_string(enter);
            for(i=0; i<4; i++){
                if( (buffer[i] == 'h')|| (buffer[i] == 'H')){
                    count3++;
                }
                else if( (buffer[i] == 'e')|| (buffer[i] == 'E')){
                    count3++;
                }
                else if( (buffer[i] == 'l')|| (buffer[i] == 'L')){
                    count3++;
                }
                else if( (buffer[i] == 'p')|| (buffer[i] == 'P')){
                    count3++;
                }
                else{
                    count3 =0;
                }
            }
            if(count3 == 4){
                USART2_print_string(help);
                
            }
            
            if( (buffer[0] == 'L') && (buffer[1] == 'E') && (buffer[2] == 'D') && (buffer[3] == 'O') && (buffer[4] == 'N') && (buffer[5] == ' ') ){        // LED ON
                if(buffer[6] == '1'){
                    GPIOD_ODR |= 1<<12;
                    USART2_print_string(LED1);
                }
                else if(buffer[6] == '2'){
                    GPIOD_ODR |= 1<<13;
                    USART2_print_string(LED2);
                }
                else if(buffer[6] == '3'){
                    GPIOD_ODR |= 1<<14;
                    USART2_print_string(LED3);
                }
                else if(buffer[6] == '4'){
                    GPIOD_ODR |= 1<<15;
                    USART2_print_string(LED4);
                }
                count2++;
                
            }
            if( (buffer[0] == 'L') && (buffer[1] == 'E') && (buffer[2] == 'D') && (buffer[3] == 'O') && (buffer[4] == 'F') && (buffer[5] == 'F') && (buffer[6] == ' ')){        // LED OFF
                if(buffer[7] == '1'){
                    GPIOD_ODR &= ~(1<<12);
                    USART2_print_string(LED5);
                }
                else if(buffer[7] == '2'){
                    GPIOD_ODR &= ~(1<<13);
                    USART2_print_string(LED6);
                }
                else if(buffer[7] == '3'){
                    GPIOD_ODR &= ~(1<<14);
                    USART2_print_string(LED7);
                }
                else if(buffer[7] == '4'){
                    GPIOD_ODR &= ~(1<<15);
                    USART2_print_string(LED8);
                }
                count2 ++;
                
            }
            if( (buffer[0] == 'L') && (buffer[1] == 'E') && (buffer[2] == 'D') && (buffer[3] == 'O') && (buffer[4] == 'N') && (buffer[5] == ' ') && (buffer[6] == 'A') && (buffer[7] == 'L') && (buffer[8] == 'L')){        // LEDON ALL
                GPIOD_ODR |= 1<<12;
                GPIOD_ODR |= 1<<13;
                GPIOD_ODR |= 1<<14;
                GPIOD_ODR |= 1<<15;
                USART2_print_string(LED9);
                count2 ++;
                
            }
            if( (buffer[0] == 'L') && (buffer[1] == 'E') && (buffer[2] == 'D') && (buffer[3] == 'O') && (buffer[4] == 'F') && (buffer[5] == 'F') && (buffer[6] == ' ') && (buffer[7] == 'A') && (buffer[8] == 'L') && (buffer[9] == 'L') ){        // LEDOFF ALL
                GPIOD_ODR &= ~(1<<12);
                GPIOD_ODR &= ~(1<<13);
                GPIOD_ODR &= ~(1<<14);
                GPIOD_ODR &= ~(1<<15);
                USART2_print_string(LED10);
                count2++;
                
            }
            if( (buffer[0] == 'L') && (buffer[1] == 'E') && (buffer[2] == 'D') && (buffer[3] == ' ') && (buffer[4] == 'T') && (buffer[5] == 'O') && (buffer[6] == 'G') && (buffer[7] == 'G') && (buffer[8] == 'L') && (buffer[9] == 'E') ){        // LED TOGGLE
                GPIOD_ODR ^= 1 << 12;
                GPIOD_ODR ^= 1 << 13;
                GPIOD_ODR ^= 1 << 14;
                GPIOD_ODR ^= 1 << 15;
                USART2_print_string(LED11);
                count2++;
            }
            if( ! ( (count3 == 4) || (count2 > 0) )){
            USART2_print_string(error); // error message for invalid input 
            }
       
           
            count2 = 0;
            count3 = 0;
            index1 = 0;
            buffer[index1] = '\0'; // buffer reset
            process_data = 1;
            if(process_data == 1){
                process_data =0;
            }
        }


        USART2_CR1 |= (1<<5); // set USART Interrupt


}
void EXTI0_IRQHandler() {

    GPIOD_ODR ^= 1 << 12;
    GPIOD_ODR ^= 1 << 13;
    GPIOD_ODR ^= 1 << 14;
    GPIOD_ODR ^= 1 << 15;

    EXTI_PR |= 1<<0;    // clear pending bit for EXTI0
}

    




int main (void)
{
	
	clk();
	
	RCC_CFGR |= 0x04600000;

    /* PORT A */
	RCC_AHB1ENR  |= 1<<0; //RCC clock enable register	
    GPIOA_MODER  |= 0<<0; // input mode
    GPIOA_OTYPER |= 0<<0; // output push-pull
    GPIOA_PUPDR  |= 0<<0; // no pull-up, pull-down

    /* button intr set */
    SYSCFG_EXTICR1 |= 0<<0; //EXTI0 connect to PA0
    EXTI_IMR       |= 1<<0; //Mask EXTI0
    EXTI_RTSR      |= 1<<0; //risign edge trigger enable
    EXTI_FTSR      |= 0<<0; //falling edge trigger disable
    NVIC_ISER0     |= 1<<6; // enable EXTI0 interrupt
	
	/* PORT D */
	RCC_AHB1ENR  |= 1<<3;		// PORTD enable
	GPIOD_MODER  |= 1<<24;		// PORTD 12 general output mode
	GPIOD_MODER  |= 1<<26;		// PORTD 13 general output mode
	GPIOD_MODER  |= 1<<28;		// PORTD 14 general output mode
	GPIOD_MODER  |= 1<<30;		// PORTD 15 general output mode
	GPIOD_OTYPER |= 0x00000000;
	GPIOD_PUPDR	 |= 0x00000000;
	
    set_usart2();

    while( count1 < 114){
        USART2_DR = uart_data[count1++];
        while ( !(USART2_SR & (1<<7)) ); // checking transmission
        while ( !(USART2_SR & (1<<6)) );
    }


	while(1) {
//        if( GPIOA_IDR & 0x00000001 ) {
//            GPIOD_ODR ^= 1 << 13;
//           GPIOD_ODR ^= 1 << 14;
//            GPIOD_ODR ^= 1 << 15;
//        }
	}
}
