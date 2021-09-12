// Assignment 3
// Name: Ayman Shahriar
// UCID: 10180260
//

////// Note: According to Dr.Manzara, busy loops are rather inexact, and so he advised me to use the busy loop he used in
//////       his code as the "standard" time (ie. 0.5 seconds), and to half the countdown to make it 0.25 seconds.


// Include files
#include "uart.h"
#include "gpio.h"


// Function prototypes:

// initializing pins to output pins
void init_GPIO17_to_output();
void init_GPIO27_to_output();
void init_GPIO22_to_output();

// setting output pins
void set_GPIO17();
void set_GPIO27();
void set_GPIO22();

// clearing output pins
void clear_GPIO17();
void clear_GPIO27();
void clear_GPIO22();

// initializing pins to input pins
void init_GPIO23_to_input();
void init_GPIO24_to_input();

// getting the level of the input pins
unsigned int get_GPIO23();
unsigned int get_GPIO24();



// main method
void main() {

	// This will be used to set up the "countdown" in busy loops
    register unsigned int r;

    // Set up the UART serial port
    uart_init();
    
    // Set up GPIO pin #17 to be an output pin
    init_GPIO17_to_output();

	// Set up GPIO pin #27 to be an output pin
    init_GPIO27_to_output();

	// Set up GPIO pin #22 to be an output pin
    init_GPIO22_to_output();

	// Set up GPIO pin #23 to be an input pin
	init_GPIO23_to_input();

	// Set up GPIO pin #24 to be an input pin
	init_GPIO24_to_input();	

    // Print out a message to the console
    uart_puts("Program starting.\n");

	// This boolean variable will detect if Switch A is pressed
	bool isPressed = false;

	// This is used to initialize the busy loop to run for around 0.5 seconds
	r = 0x003FFFFF;	

	// Enter an infinite loop
	while(1) {
		
		// This while loop will display pattern 1. When Switch A is pressed, this loop will be exited
		while (1) {
			
			// If switch B is not pushed down, then LED's will be on for about 0.5 seconds
			if (getGPIO_24() == 0)	{
				r = 0x003FFFFF;
			
			// If switch B is pushed down, then LED's will be on for about 0.25 seconds
			} else {
				r = 0x00200000;			
			}	

			// turn on LED 1
			set_GPIO17();	

			// Delay using a busy loop
    		while (r--) {
					
				// If switch A is pressed, then the busy loop is exited
				if (getGPIO_23() == 1) {
					// set isPressed to true					
					isPressed = true;	
					// break from this busy loop					
					break;				
				}      
				asm volatile("nop");	
    		}
			
			// if switch has been pressed, then we exit this pattern 1 loop
			if (isPressed == true) {
				// set isPressed to false
				isPressed = false;				
								
				// break from this pattern 1 loop				
				break;					
			}

			// turn off LED 1
			void clear_GPIO17();

			// turn on LED 2
			set_GPIO27();	

			// Delay using a busy loop
    		while (r--) {
				// If switch A is pressed, then the busy loop is exited
				if (getGPIO_23() == 1) {
					// set isPressed to true
					isPressed = true;	
					
					// break from this busy loop					
					break;				
				}      
				asm volatile("nop");	
    		}

			// if switch has been pressed, then we exit this pattern 1 loop
			if (isPressed == true) {
				// set isPressed to false
				isPressed = false;				
								
				// break from this pattern 1 loop				
				break;			
			}

			// turn off LED 2
			void clear_GPIO27();

			// turn on LED 3
			set_GPIO22();	

			// Delay using a busy loop
    		while (r--) {
				// If switch A is pressed, then the busy loop is exited
				if (getGPIO_23() == 1) {
					// set isPressed to true					
					isPressed = true;	
					
					// break from this busy loop					
					break;				
				}      
				asm volatile("nop");	
    		}

			// if switch has been pressed, then we exit this pattern 1 loop
			if (isPressed == true) {
				// set isPressed to false
				isPressed = false;				
								
				// break from this pattern 1 loop				
				break;			
			}

			// turn off LED 3
			clear_GPIO22();
		}


		// This while loop will display pattern 2. When Switch A is pressed, this loop will be exited
		while (1) {
			
			// If switch B is not pushed down, then LED's will be on for about 0.5 seconds
			if (getGPIO_24() == 0)	{
				r = 0x003FFFFF;

			// If switch B is pushed down, then LED's will be on for about 0.25 seconds
			} else {
				r = 0x00200000;			
			}
			
			// turn on LED 2
			set_GPIO27();				

			// turn on LED 3
			set_GPIO22();	

			// Delay using a busy loop
    		while (r--) {
				// If switch A is pressed, then the busy loop is exited
				if (getGPIO_23() == 1) {
					// set isPressed to true					
					isPressed = true;	
					// break from this busy loop
					break;				
				}      
				asm volatile("nop");	      			
    		}

			// if switch has been pressed, then we exit this pattern 2 loop
			if (isPressed == true) {
				// set isPressed to false
				isPressed = false;
				// break from this pattern 2 loop
				break;			
			}

			// turn off LED 2
			clear_GPIO27();

			// turn off LED 3
			clear_GPIO22();

			// turn on LED 1
			set_GPIO17();	

			// Delay using a busy loop 
    		while (r--) {
				// If switch A is pressed, then the busy loop is exited
				if (getGPIO_23() == 1) {
					// set isPressed to true
					isPressed = true;
					// break from this busy loop	
					break;				
				}      
				asm volatile("nop");	      			
    		}

			// if switch has been pressed, then we exit this pattern 2 loop
			if (isPressed == true) {
				// set isPressed to false
				isPressed = false;
				// exit from this pattern 2 loop
				break;			
			}

			// turn off LED 1
			clear_GPIO17();
		}


	}


}




// The following three functions will initialize GPIO pins #17, #27, #22 to be output pins

void init_GPIO17_to_output() {
	register unsigned int r;
	
	// Get current contents of GPIO Function Select Register 1 (GPFSEL2)
	r = *GPFSEL1;

	// Clear bits 21-23. This maps to GPIO pin 17
	r &= ~(0x7 << 21);

	// Set pin 17 to an output pin by setting bits 21-23 to 001
	r |= (0x1 << 21);

	// Write new bit pattern back to GPIO Function Select Register 1 (GPFSEL1)
	*GPFSEL1 = r;

	// Now, we disable pull-up/pull-down control line for GPIO pin 17

	// Get the bit pattern in the GPPUPPDN1 register
	r = *GPPUPPDN1;

	// Zero out bits 2-3 in this bit pattern, since this maps to GPIO pin 17
	// The bit pattern 00 disables pullups/pulldowns
	r &= ~(0x3 << 2);

	// Write new bit pattern back to GPPUPPDN1 register
	*GPPUPPDN1 = r;
}


void init_GPIO27_to_output() {
	register unsigned int r;
	
	// Get current contents of GPIO Function Select Register 2 (GPFSEL2)
	r = *GPFSEL2;

	// Clear bits 21-23. This maps to GPIO pin 27
	r &= ~(0x7 << 21);

	// Set pin 27 to an output pin by setting bits 21-23 to 001
	r |= (0x1 << 21);

	// Write new bit pattern back to GPIO Function Select Register 2 (GPFSEL2)
	*GPFSEL2 = r;

	// Now, we disable pull-up/pull-down control line for GPIO pin 27

	// Get the bit pattern in the GPPUPPDN1 register
	r = *GPPUPPDN1;

	// Zero out bits 22-23 in this bit pattern, since this maps to GPIO pin 27
	// The bit pattern 00 disables pullups/pulldowns
	r &= ~(0x3 << 22);

	// Write new bit pattern back to GPPUPPDN1 register
	*GPPUPPDN1 = r;
}


void init_GPIO22_to_output() {
	register unsigned int r;
	
	// Get current contents of GPIO Function Select Register 2 (GPFSEL2)
	r = *GPFSEL2;

	// Clear bits 6-8. This maps to GPIO pin 22
	r &= ~(0x7 << 6);

	// Set pin 22 to an output pin by setting bits 6-8 to 001
	r |= (0x1 << 6);

	// Write new bit pattern back to GPIO Function Select Register 2 (GPFSEL2)
	*GPFSEL2 = r;

	// Now, we disable pull-up/pull-down control line for GPIO pin 22

	// Get the bit pattern in the GPPUPPDN1 register
	r = *GPPUPPDN1;

	// Zero out bits 12-13 in this bit pattern, since this maps to GPIO pin 22
	// The bit pattern 00 disables pullups/pulldowns
	r &= ~(0x3 << 12);

	// Write new bit pattern back to GPPUPPDN1 register
	*GPPUPPDN1 = r;
}




// The following three functions will set the GPIO pins #17, #27, #22 (which are set as output pins) to a high level (1)

void set_GPIO17() {
    register unsigned int r;
	// To set GPIO pin 17 to a high value (3.3V), set the corresponding bit in the GPIO Pin Output Set Register 0 (GPSET0) to 1
    r = (0x1 << 17);
    *GPSET0 = r;
}


void set_GPIO27() {
    register unsigned int r;
	// To set GPIO pin 27 to a high value (3.3V), set the corresponding bit in the GPIO Pin Output Set Register 0 (GPSET0) to 1
    r = (0x1 << 27);
    *GPSET0 = r;
}


void set_GPIO22() {
    register unsigned int r;
	// To set GPIO pin 22 to a high value (3.3V), set the corresponding bit in the GPIO Pin Output Set Register 0 (GPSET0) to 1
    r = (0x1 << 22);
    *GPSET0 = r;
}




// The following three functions will clear the GPIO pins #17, #27, #22 (which are set as output pins) to a low level (0)

void clear_GPIO17() {
    register unsigned int r;
	// To set GPIO pin 17 to a low value (0V), set the corresponding bit in the GPIO Clear Register 0 (GPCLR0) to 1
    r = (0x1 << 17);
    *GPCLR0 = r;
}


void clear_GPIO27() {
    register unsigned int r;
	// To set GPIO pin 27 to a low value (0V), set the corresponding bit in the GPIO Clear Register 0 (GPCLR0) to 1
    r = (0x1 << 27);
    *GPCLR0 = r;
}


void clear_GPIO22() {
    register unsigned int r;
	// To set GPIO pin 22 to a low value (0V), set the corresponding bit in the GPIO Clear Register 0 (GPCLR0) to 1
    r = (0x1 << 22);
    *GPCLR0 = r;
}




// The following two functions will initialize GPIO pins #23, #24 to be input pins

void init_GPIO23_to_input() {

    register unsigned int r;
    
    
    // Get the contents of the GPIO Function Select Register 2 (*GPFSEL2)
    r = *GPFSEL2;

	// Set pin 23 to be an input pin by clearing bits 9-11
    r &= ~(0x7 << 9);

	// Write new bit pattern back to GPIO Function Select Register 2 (GPFSEL2)
    *GPFSEL2 = r;


	// Now, we disable pull-up/pull-down control line for GPIO pin 23

    // Get the bit pattern of the GPPUPPDN1 register
    r = *GPPUPPDN1;

	// Zero out bits 14-15 in this bit pattern, since this maps to GPIO pin 23
	// The bit pattern 00 disables pullups/pulldowns
    r &= ~(0x3 << 14);

	// Write new bit pattern back to GPPUPPDN1 register
    *GPPUPPDN1 = r;
}


void init_GPIO24_to_input() {
    
	register unsigned int r;
    
    
    // Get the contents of the GPIO Function Select Register 2 (*GPFSEL2)
    r = *GPFSEL2;

	// Set pin 24 to be an input pin by clearing bits 12-14
    r &= ~(0x7 << 12);

	// Write new bit pattern back to GPIO Function Select Register 2 (GPFSEL2)
    *GPFSEL2 = r;


	// Now, we disable pull-up/pull-down control line for GPIO pin 24

    // Get the bit pattern of the GPPUPPDN1 register
    r = *GPPUPPDN1;

	// Zero out bits 16-17 in this bit pattern, since this maps to GPIO pin 24
	// The bit pattern 00 disables pullups/pulldowns
    r &= ~(0x3 << 16);

	// Write new bit pattern back to GPPUPPDN1 register
    *GPPUPPDN1 = r;
}



// The following two functions will get the level of GPIO pins #23, #24 (which are set as input pins)

unsigned int get_GPIO23() {

    register unsigned int r;
	  
	  
    // Get the contents of the GPIO Pin Level Register 0 (GPLEV0)
    r = *GPLEV0;
	  
    // Isolate pin 23, and return its value (a 0 if low, or a 1 if high)
    return ((r >> 23) & 0x1);
}


unsigned int get_GPIO24() {

    register unsigned int r;
	  
	  
    // Get the contents of the GPIO Pin Level Register 0 (GPLEV0)
    r = *GPLEV0;
	  
    // Isolate pin 24, and return its value (a 0 if low, or a 1 if high)
    return ((r >> 24) & 0x1);
}
















