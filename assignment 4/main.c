/*
 * Assignment 4
 * Name: Ayman Shahriar
 * Tutorial: T11
 * UCID: 10180260
 *
 * Note: My stratergy for this assignment was to make the game in c that printed the maze in the terminal,
 * check if it works, and then implement the pi/SNES controller components.
 * So I am confident that the game logic works/
 */




// Header files to include
#include "uart.h"
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

// Create macros to represent 0 and 1 as TRUE and FALSE
#define TRUE 	1
#define FALSE 	0




// Function prototypes:

// Initialize GPIO pint 9, 10, 11 for I/O with SNES controller
void initSNES();

// Check if player has reached the exit or not
int reachedExit(int x, int y);

// Resets the maze to the start state
void resetMaze();

// Displays the maze to screen. Takes an integer input  where TRUE means
// the game is won, and FALSE means the game is not yet won.
void displayMaze(int fameFinished);




// Coordinates of player (default coordinate is (0, 2))
int playerX = 0;
int playerY = 2;

// This is the maze of the game.
// 1 represents wall, 2 represents player, 3 represents entry, 4 represents exit
int maze[12][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {3, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1},
    {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 4},
    {1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};





void main()
{	

	// these will be used to retrieve the button pressed in the controller
	unsigned short data, currentState = 0xFFFF;
	
	// Set up the UART serial port
	uart_init();
    	
	// Initialize GPIO pins #9, #10, #11 to handle SNES IO
	initSNES();
       	
	// Initialize the frame buffer
	initFrameBuffer();

    // Print out a message to the console
    uart_puts("Program starting.\n");
    
	// Display the maze. The player is not displayed yet
	displayMaze(FALSE);
		

   	// Keep on looping until the player presses start, then you
   	// add the player to the maze and start the game.   
	
	start:  // a goto label, used to restart the game once it's finished
	while(1) {
		printf( "\nPress s to start :");
	    c = getchar();
		
		// Read data from the SNES controller
    	data = get_SNES();

		// Check if start has been pressed
		if (data != currentState) {
	    	if (data == START) {

			// If start has been pressed, show player in the entry of the maze
			maze[2][0] = 2;
			displayMaze(FALSE);

			// record state of controller
			currentState = data
			
			// exit this loop, and move into the main loop of the game
			break;
			}
		}
		
		// Delay 1/30th of a second, since we are reading from the SNES controller 30 times per second
    		microsecond_delay(33333);

	}	


    // This is the main game loop, where you can move through the maze
    while (1) {
    	// Read data from the SNES controller
    	data = get_SNES();

		// Check if UP, DOWN, LEFT, RIGHT has been pressed
		if (data != currentState) {
			
			switch(data) {
			
			// if left is pressed and there is no obstacle, move player to the left in the maze
   			case LEFT:		
				if ((maze[playerY][playerX-1] == 0) || (maze[playerY][playerX-1] == 4)) {
					// update maze and player coordinates
					maze[playerY][playerX] = 0;
					playerX -= 1;
					maze[playerY][playerX] = 2;
				}
				break;
			
			// if right is pressed and there is no obstacle, move player to the right in the maze
			case RIGHT:
				if ((maze[playerY][playerX+1] == 0) || (maze[playerY][playerX+1] == 4)) {
					// update maze and player coordinates
					maze[playerY][playerX] = 0;
					playerX += 1;
                    maze[playerY][playerX] = 2;
				}
				break;

			// if down is pressed and there is no obstacle, move player down the maze
			case DOWN:
				if ((maze[playerY+1][playerX] == 0) || (maze[playerY+1][playerX] == 4)) {
                    // update maze and player coordinates
					maze[playerY][playerX] = 0;
                    playerY += 1;
                    maze[playerY][playerX] = 2;
                }
                break;

			// if up is pressed and there is no obstacle, move player up the maze
			case UP:
                if ((maze[playerY-1][playerX] == 0) || (maze[playerY-1][playerX] == 4)) {
					// update maze and player coordinates
                    maze[playerY][playerX] = 0;
                    playerY -= 1;
                    maze[playerY][playerX] = 2;
                }
                break;

		
			} // end of switch statement
	
			
			// if the player has just left the start location, set it to 3 to signify that it's the start location
         	if (maze[2][0] == 0) {
           		maze[2][0] = 3;
			}
			
			// Display the maze with the changed player location
			displayMaze(FALSE);

			// Check if player has reached exit
			if (reachedExit(playerX, playerY) == TRUE) {
				
				// set player colour to red by diplaying maze with TRUE as input
				displayMaze(TRUE);

				// Go into a loop until START is pressed. Once start is pressed, we will to back to the start of the 
				// game using a goto statement
				int loop = TRUE;
				while(loop) {

					// Read data from the SNES controller
    				data = get_SNES();
					
					// Check is user has pressed start
					if (data != currentState) {
						if (data == START) {
							resetMaze();
							displayMaze(maze);

							// reset player coordinates
							playerX = 0;
							playerY = 2;
						
							// using a goto statement, go to the start of the game
							goto start;
						}
					}
					// Delay 1/30th of a second, since we are reading from the SNES controller 30 times per second
	    			microsecond_delay(33333);
				}
			}




		}
		
		// Delay 1/30th of a second, since we are reading from the SNES controller 30 times per second
    	microsecond_delay(33333);

  	} // end of main came loop




} // end of main method




// Initialize GPIO pint 9, 10, 11 for I/O with SNES controller
void initSNES() {

   	// Set up GPIO pin #9 for output (LATCH output)
    	init_GPIO9_to_output();
    
    	// Set up GPIO pin #11 for output (CLOCK output)
    	init_GPIO11_to_output();
    
    	// Set up GPIO pin #10 for input (DATA input)
    	init_GPIO10_to_input();
    
    	// Clear the LATCH line (GPIO 9) to low
    	clear_GPIO9();
    
    	// Set CLOCK line (GPIO 11) to high
    	set_GPIO11();

}



// This function takes in coordinates of player, and checks if those 
// coordinates are the same as the exit coordinates
int reachedExit(int x, int y) {
	if ((x == 15) && (y == 8)) {
	return TRUE;
	}
	else {
		return FALSE;
	}
}


// Resets the maze to the start state
void resetMaze() {
	// reset coordinates of player to coordinates of maze entry
	int playerX = 0;
	int playerY = 2;

	// set entry and exit in maze array
	maze[2][0] = 3;
	maze[8][15] = 4;

}


// This function will display the maze to the screen.
// Gray will represent wall, white will represent empty space,
// Red will represent player during the game, green will represent the player after the game,
// blue will represent the entry, purple will represent the exit.
//
// If the input is FALSE, the player will be red.
// If the input is TRUE, the player will be green.
void displayMaze(int gameFinished) {
	
	// in the display, each square will be 64 pixels in length and width
	int rows = 12;
    int columns = 16;
	int squareSize = 64;
        
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			
			// based on which value each cell of the maze contains, display the colour
			switch(maze[i][j]) {
			
			// for empty space, display white square			
			case 0:		
				drawSquare(i * squareSize, j * squareSize, squareSize, WHITE);
				break;

			// for wall, display gray square
			case 1:
				drawSquare(i * squareSize, j * squareSize, squareSize, GRAY);
				break;
			
			// for player, display red square if game is not finished, 
			// and green if game is finished
			case 2:
  				if (gameFinished == TRUE) {
					drawSquare(i * squareSize, j * squareSize, squareSize, GREEN);
					break;				
				}
				else
					drawSquare(i * squareSize, j * squareSize, squareSize, RED);
					break;

			// for entry, display blue square
			case 3:
				drawSquare(i * squareSize, j * squareSize, squareSize, BLUE);
				break;
			}

			// for exit, display purple square
			case 4:
				drawSquare(i * squareSize, j * squareSize, squareSize, PURPLE);
				break;				
		
		}

	}

}










