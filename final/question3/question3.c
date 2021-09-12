
/*
 * Final Exam Question 3
 * Name: Ayman Shahriar
 * Tutorial: T11
 * UCID: 10180260
 */


// Include files
#include "gpio.h"
#include "systimer.h"


// Function prototypes:

// Initialize GPIO 22 as output pin
void init_GPIO22_to_output();

// setting GPIO 22 output pin
void set_GPIO22();

// clearing GPIO 22 output pin
void clear_GPIO22();

// initializing GPIO 24 as input pin
void init_GPIO24_to_input();

// getting the level of GPIO 24 input pin
unsigned int get_GPIO24_level();



// main method
void main() {

	// Set up GPIO pin #22 to be an output pin
    init_GPIO22_to_output();
	

	// Set up GPIO pin #24 to be an input pin
	init_GPIO24_to_input();	

	// go into an infinite loop, displaying pattern 1 or 2 depending of the button is being pressed or not
	while(1) {

		// check if button is being pressed
        if (get_GPIO24_level() == 0) {
			
			// if the button is not being pressed, display pattern 1
			displayPattern1();
      	}

		else {
			
			// if the button is being pressed, display pattern 2
			displayPattern2();
		}

	}

}




// Display pattern 1

	void pattern1() {
		
		// turn LED on
		set_GPIO22();

		// Delay 0.5 second using the system timer
    	microsecond_delay(500000);

		// turn LED off
		clear_GPIO22();	

		// Delay 0.5 second using the system timer
    	microsecond_delay(500000);

	}



// Display pattern2

	void pattern2() {		

		// turn LED on
	    set_GPIO22();

	    // Delay 0.25 second using the system timer
	    microsecond_delay(250000);

	    // turn LED off
	    clear_GPIO22();

 	   	// Delay 0.25 second using the system timer
  	   	microsecond_delay(250000);


    	// turn LED on
	    set_GPIO22();

	    // Delay 0.25 second using the system timer
	    microsecond_delay(250000);

	    // turn LED off
 	    clear_GPIO22();

	   	// Delay 0.25 second using the system timer
 	    microsecond_delay(250000);


	   	// turn LED on
 	   	set_GPIO22();

	    // Delay 0.5 second using the system timer
	    microsecond_delay(500000);

 	   	// turn LED off
    	clear_GPIO22();

	   	// Delay 0.5 second using the system timer
		microsecond_delay(500000);
		
	} 



// This function will initialize GPIO pin #22 to be an output pin

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




// This function will set GPIO pin #22 (which is set as output pin) to a high level (1)

void set_GPIO22() {
    register unsigned int r;
	// To set GPIO pin 22 to a high value (3.3V), set the corresponding bit in the GPIO Pin Output Set Register 0 (GPSET0) to 1
    r = (0x1 << 22);
    *GPSET0 = r;
}



// This function will clear GPIO pin #22 (which is set as output pin) to a low level (0)

void clear_GPIO22() {
    register unsigned int r;
	// To set GPIO pin 22 to a low value (0V), set the corresponding bit in the GPIO Clear Register 0 (GPCLR0) to 1
    r = (0x1 << 22);
    *GPCLR0 = r;
}



// This function will initialize GPIO pin #24 to be an input pin

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



// This function returns 1 if the GPIO pin 24 is pulled high, and returns 0 if the pin is pulled low
unsigned int get_GPIO24_level() {

    register unsigned int r;
	  
	  
    // Get the contents of the GPIO Pin Level Register 0 (GPLEV0)
    r = *GPLEV0;
	  
    // Isolate pin 24, and return its value (a 0 if low, or a 1 if high)
    return ((r >> 24) & 0x1);
}
















