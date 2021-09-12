/*
 * Final Exam Question 4
 * Name: Ayman Shahriar
 * Tutorial: T11
 * UCID: 10180260
 */



// Header files to include
#include "gpio.h"
#include "systimer.h"
#include "SNES.h"
#include "FrameBuffer.h"


// Create macros for SNES controller inputs
#define UP		0x00000010
#define DOWN	0x00000020
#define LEFT	0x00000040
#define RIGHT	0x00000080
#define START	0x00000008


// HTML RGB color codes used
#define BLACK     0x00000000
#define WHITE     0x00FFFFFF
#define BLUE      0x000000FF
#define YELLOW    0x00FFFF00
#define GREEN     0x00008000
#define ORNGE	  0x00FFA500
#define GRAY      0x00808080


// Function headers
int getButton();
void polling_loop();
void void drawCheckerboard(int numberOfRows, int numberOfColumns, int squareSize, unsigned int color1, unsigned int color2);


int getButton() {

	// Read data from the SNES controller
    data = get_SNES();
		
	// if up button is pressed, return 1
	if (data == UP) {
		return 1;
	}

	// if down button has been pressed, return 2
	else if (data == DOWN) {
		return 2;
	}

	// if left button had been pressed, return 3
	else if (data == LEFT) {
		return 3;
	}	    

	// if right button has been pressed, return 4
	else if (data == RIGHT) {
		return 4;
	}

	// if any other button has been pressed, or no button had been pressed, return 0;
	else {
		return 0;
	}


}



// This function polls the SNES controller 60 times a second using the getButton() function, 
// and redraws the frame buffer as necessary.

void polling_loop() {
	
	// set the default row size, column size, and square size that will be displayed
	int rows = 12;
    int columns = 16;
	int squareSize = 64;
	
	// this variable is used to hold the value of the button pressed
	int button;

	// this variable is used to hold the last button value pressed (initially 0)
	int currentState = 0;


    // Loop forever, reading from the SNES controller 60 times per second
    while (1) {	

		// retrieve button pressed (returns 0 if no button has been pressed)
		button = getButton();
		
		// check if the state of the controller has changed
		if (button != currentState) {

			// check if state has changed to 1
			if (button == 1) {

			    // Redraw checkerboard pattern using blue and yellow
	    		drawCheckerboard(rows, columns, squareSize, BLUE, YELLOW);
			}

			// check if state has changed to 2
			else if (button == 2) {

				// Redraw checkerboard pattern using green and orange
	            drawCheckerboard(rows, columns, squareSize, GREEN, ORANGE);
			}

			// check if state has changed to 3
			else if (button == 3) {
			
				// Fill entire framebuffer with gray
				drawCheckerboard(rows, columns, squareSize, GRAY, GRAY);

			}

			// check if state has changed to 4
			else if (button == 4) {
			
				// first set columns to 32, rows to 24, square size to 32
				columns = 32;
				rows = 24;
				squareSize = 32;			

				// draw a 32 x 24 black and white checkerboard pattern, where each square is 32 x 32 pixels in size
				drawCheckerboard(rows, columns, size, BLACK, WHITE);

				// reset the columns to 16, rows to 12, square size to 64
				columns = 16;
	   	        rows = 12;
	            squareSize = 64;

			}

		}

		// Record the state of the controller
		currentState = button;

		// Delay 1/60th of a second
		microsecond_delay(16667);
		

	}  // end of while loop
}  // end of function




// This function takes number of rows, number of columns, square size, two colours, 
// and creates a checkerboard pattern according to these specifications

void drawCheckerboard(int numberOfRows, int numberOfColumns, int squareSize, unsigned int color1, unsigned int color2) {
    int i, j;

    // Draw the rows from the top down
    for (i = 0; i < numberOfRows; i++) {
		// Draw the squares for the evenly numbered rows
		if ((i % 2) == 0) {
		    // Draw alternating squares starting with the first color
		    for (j = 0; j < numberOfColumns; j += 2) {
			drawSquare(i * squareSize, j * squareSize, squareSize, color1);
			drawSquare(i * squareSize, (j + 1) * squareSize, squareSize, color2);
		    }
		}
		// Draw the squares for the oddly numbered rows
		else {
		    // Draw alternating squares starting with the second color
		    for (j = 0; j < numberOfColumns; j += 2) {
			drawSquare(i * squareSize, j * squareSize, squareSize, color2);
			drawSquare(i * squareSize, (j + 1) * squareSize, squareSize, color1);
		    }
		}
    }	    
}














