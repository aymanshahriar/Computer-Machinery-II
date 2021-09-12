#include <stdio.h>


// macros
#define TRUE 1
#define FALSE 0


// function prototypes
void printMaze();
int reachedExit(int x, int y);
void resetMaze();


// variables
int playerX = 0;
int playerY = 2;



// 0 represents empty, 1 represents walls, 2 represents player
// 3 represents entrance, 4 represents exit
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

int main() {
	int c;
	
	printMaze(maze);
		
   	// put a loop here where you keep on looping until the player presses 
   	// start, then you show the location of the player and start the game.   

   	// once this loop is exited, add the player to the maze and print.
	
	start:  // a goto label
	while(1) {
		printf( "\nPress s to start :");
        c = getchar();
		if (c == 's') {
			// show player in the entry of maze
			maze[2][0] = 2;
			printMaze(maze);
			break;
		}

	}	
		

	while(1) {

   		printf( "\nEnter a value :");
   		c = getchar();

		printf("%s", "\n");

		switch(c) {
   			case 'a':		
				if ((maze[playerY][playerX-1] == 0) || (maze[playerY][playerX-1] == 4)) {
					maze[playerY][playerX] = 0;
					playerX -= 1;
					maze[playerY][playerX] = 2;
				}
				//printMaze(maze);
				break;
			
			case 'd':
				if ((maze[playerY][playerX+1] == 0) || (maze[playerY][playerX+1] == 4)) {
					maze[playerY][playerX] = 0;
					playerX += 1;
                    maze[playerY][playerX] = 2;
				}
    			//printMaze(maze);
				break;

			case 's':
				if ((maze[playerY+1][playerX] == 0) || (maze[playerY+1][playerX] == 4)) {
                    maze[playerY][playerX] = 0;
                    playerY += 1;
                    maze[playerY][playerX] = 2;
                }
                //printMaze(maze);
                break;

			case 'w':
                if ((maze[playerY-1][playerX] == 0) || (maze[playerY-1][playerX] == 4)) {
                    maze[playerY][playerX] = 0;
                    playerY -= 1;
                    maze[playerY][playerX] = 2;
                }
                //printMaze(maze);
                break;

		
			} // end of case
	
			
			// if the player has just left the entry location, set it to 3 to signify that it's the start location
         	if (maze[2][0] == 0) {
           		maze[2][0] = 3;
			}
			
			printMaze();

			if (reachedExit(playerX, playerY) == TRUE) {
				int loop = TRUE;
				while(loop) {
					printf( "\nYou won. Enter r to play again:");
					c = getchar();
					if (c == 'r') {
						resetMaze();
						printMaze();

						// reset player coordinates
						playerX = 0;
						playerY = 2;
						
						// using a goto statement, go to the start of the game
						goto start;
						
					}
				}
			}
	

	} // end of infinite loop

  	return 0;
} // end of main method





void printMaze() {
	for(int i = 0; i < 12; i++) {
        
    for(int j = 0; j < 16; j++) {
        printf("%d ", maze[i][j]);
    }
        
	printf("\n");
    }

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


