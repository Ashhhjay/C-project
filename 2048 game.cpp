#include <iostream>
#include <cstdlib>
#include <ctime>			// Include the time library
#include <conio.h>        // Include the header file for console input/output
#include <iomanip>        // Include the input/output manipulators library setw , setprecision etc

using namespace std;

const int ROW = 4;       		 // Define a constant integer variable ROW with a value of 4
const int COL = 4;        		// Define a constant integer variable COL with a value of 4
int board[ROW][COL] = {0};     // Declare and initialize a 2D integer array named board, filled with zeros
int score = 0;
int high_score = 0;


void printBoard() {						// Declare a function named printBoard
	// Print the game board
	cout<<"\n\t\tPress \"w\" to go UP, \"s\" to go DOWN, \"a\" to go LEFT, \"d\" to go RIGHT\n";    
	cout<<"\t\tPress Esc anytime to quit the game\n\n\n";
	cout<<"\n\t\t\t\t\t\t\t\t\t"<<"Score = " << score << "   High Score: " << high_score << endl;;
	cout<<"\t\t\t\t\t";
    cout << "+------+------+------+------+" << endl;
    for (int i = 0; i < ROW; i++) {
    	cout<<"\t\t\t\t\t";
        for (int j = 0; j < COL; j++) {
            cout << "|";
            if (board[i][j] == 0) {
                cout << "      ";
            } else {
                
				cout << setw(6) << board[i][j]; 	// Print the value of a cell in the game board with a field width of 6 characters
            }
        }
        cout << "|" << endl;
        cout<<"\t\t\t\t\t";
        cout << "+------+------+------+------+" << endl;
    }
}


void initializeBoard() {
    srand(time(NULL));
    srand(time(NULL));  // Initialize the random number generator with the current time
    // Add two random tiles to the board with different values
    int row1, col1, row2, col2;
    do {
        // Generate random row and column indices for the first tile
        row1 = rand() % ROW;  			// Random row index from 0 to ROW-1
        col1 = rand() % COL;  			// Random column index from 0 to COL-1
        
        // Generate random row and column indices for the second tile
        row2 = rand() % ROW;  			// Random row index from 0 to ROW-1
        col2 = rand() % COL;  			// Random column index from 0 to COL-1
    } while (board[row1][col1] != 0 || board[row2][col2] != 0 || (row1 == row2 && col1 == col2));
    // Repeat the loop if either of the tiles is already occupied or if the indices are the same
    
    board[row1][col1] = (rand() % 2 + 1) * 2;  // randomly set the value to 2 or 4
    board[row2][col2] = (rand() % 2 + 1) * 2;  // randomly set the value to 2 or 4
}


void clearBoard() {
    for (int i = 0; i < ROW; i++) {   // Iterate over each row of the board
        for (int j = 0; j < COL; j++) {   // Iterate over each column of the board
            board[i][j] = 0;   // Set the cell value to 0
        }
    }
}


void addPiece() {
    // Generate a random position for the new tile
    int r, c;
    do {
        r = rand() % 4;   // Generate a random row index (0 to 3)
        c = rand() % 4;   // Generate a random column index (0 to 3)
    } while (board[r][c] != 0);   // Repeat the loop if the cell at the generated position is not empty
   
    int value = (rand() % 2 + 1) * 2;	// Generate a random value for the new tile (either 2 or 4)
    board[r][c] = value;				// Set the value of the new tile at the generated position
}


void upmove() {
    bool moved = false;   // Flag to track if any movement occurred during the operation
    
    // Iterate over each column
    for (int j = 0; j < COL; j++) {
        int firstRow = 0;   					// Index of the first non-zero element in the column
         
        for (int i = 1; i < ROW; i++) {			 // Iterate over each row, starting from the second row
            if (board[i][j] != 0) {  			 // If the current cell is not empty
                if (board[firstRow][j] == 0) {   // If the first row  element is empty
                    board[firstRow][j] += board[i][j];		 // Move the current element to the first non-zero position
                    board[i][j] = 0;
                    moved = true;
                }
                else if (board[firstRow][j] == board[i][j]) {   // If the current element matches the first non-zero element
                    board[firstRow][j] += board[i][j];			// Merge the current element with the first non-zero element
                    board[i][j] = 0;
                    moved = true;
                    score += board[firstRow][j];   				// Update the score by adding the merged value
                } else {
                    // Move the current element to the next position in the column
					firstRow++;
					board[firstRow][j] = board[i][j];	
					if (i != firstRow) {					// Check if the current tile was moved to a new position
					    board[i][j] = 0;					// Clear the previous position of the current tile
					    moved = true;						// Set the moved flag to true
					
                    }
                }
            }
        }
    }
    
    if (moved) {   // If any movement occurred during the operation
        addPiece();   // Add a new tile to the board
    }
}


void downmove() {
    bool moved = false;							// Flag to track if any movement occurred

    for (int j = 0; j < COL; j++) {
        int lastRow = ROW - 1; 					// Index of the last non-zero element in the column
        
        for (int i = ROW - 2; i >= 0; i--) {	// Traverse the column from bottom to top
            if (board[i][j] != 0) {				// If the current element is non-zero
                if (board[lastRow][j] == 0) {
                    board[lastRow][j] += board[i][j];	// If the last element is zero, move the current element to that position
                    board[i][j] = 0;
                    moved = true;
                }
                else if (board[lastRow][j] == board[i][j]) {
                    board[lastRow][j] += board[i][j];	 // If the last element is equal to the current element, merge them
                    board[i][j] = 0;
                    moved = true;
                    score += board[lastRow][j]; 			// Update the score
                } else {
                    // Move the current element to the next available position above it
                    lastRow--;
                    board[lastRow][j] = board[i][j];
                    if (i != lastRow) {
                        board[i][j] = 0;				// If the current element was moved, clear its previous position
                        moved = true;
                    }
                }
            }
        }
    }

    if (moved) {
        // If any movement occurred, add a new tile to the board
        addPiece();
    }
}


void leftmove() {
    bool moved = false; // Flag to track if any movement occurred

    for (int i = 0; i < ROW; i++) {
        int firstCol = 0; // Index of the first non-zero element in the row

        // Traverse the row from left to right
        for (int j = 1; j < COL; j++) {
            if (board[i][j] != 0) {
                // If the current element is non-zero
                if (board[i][firstCol] == 0) {
                    // If the first element is zero, move the current element to that position
                    board[i][firstCol] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                }
                else if (board[i][firstCol] == board[i][j]) {
                    // If the first element is equal to the current element, merge them
                    board[i][firstCol] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                    score += board[i][firstCol]; // Update the score
                } else {
                    // Move the current element to the next available position on the left
                    firstCol++;
                    board[i][firstCol] = board[i][j];

                    if (j != firstCol) {
                        // If the current element was moved, clear its previous position
                        board[i][j] = 0;
                        moved = true;
                    }
                }
            }
        }
    }

    if (moved) {
        // If any movement occurred, add a new tile to the board
        addPiece();
    }
}


void rightmove() {
    bool moved = false; // Flag to track if any movement occurred

    for (int i = 0; i < ROW; i++) {
        int lastCol = COL - 1; // Index of the last non-zero element in the row

        // Traverse the row from right to left
        for (int j = COL - 2; j >= 0; j--) {
            if (board[i][j] != 0) {
                // If the current element is non-zero

                if (board[i][lastCol] == 0) {
                    // If the last element is zero, move the current element to that position
                    board[i][lastCol] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                }
                else if (board[i][lastCol] == board[i][j]) {
                    // If the last element is equal to the current element, merge them
                    board[i][lastCol] += board[i][j];
                    board[i][j] = 0;
                    moved = true;
                    score += board[i][lastCol]; // Update the score
                } else {
                    // Move the current element to the next available position on the right
                    lastCol--;
                    board[i][lastCol] = board[i][j];

                    if (j != lastCol) {
                        // If the current element was moved, clear its previous position
                        board[i][j] = 0;
                        moved = true;
                    }
                }
            }
        }
    }

    if (moved) {
        // If any movement occurred, add a new tile to the board
        addPiece();
    }
}



bool check_game_over() {
    for (int i = 0; i < ROW-1; i++) {
        for (int j = 0; j < COL-1; j++) {
            if (board[i][j] == 0 || board[i][j+1] == 0) {
                // If there is an empty tile adjacent to the current tile, the game is not over
                return false;
            }
            if (board[i][j] == board[i+1][j]) {
                // If there are two adjacent tiles with the same value in a vertical direction, the game is not over
                return false;
            }
            if (board[i][j] == board[i][j+1]) {
                // If there are two adjacent tiles with the same value in a horizontal direction, the game is not over
                return false;
            }
            if (board[i][j] == 2048 || board[i+1][j] == 2048 || board[i][j+1] == 2048 || board[i+1][j+1] == 2048) {
                // If any tile has reached the value 2048, the player has won the game
                cout << "Congratulations! You won!" << endl;
                return true; 
            }
        }
    }
    // If none of the above conditions are met, the game is over
    return true;
}


void playGame() {
    system("cls"); // Clear the console screen
    initializeBoard(); // Initialize the game board
    printBoard(); // Print the initial state of the board
    char move;
    while (1) {
        move = getch(); // Get the user's move
        if (move == 'w' || move == 'W') {
            upmove(); // Perform the move in the up direction
        } else if (move == 's' || move == 'S') {
            downmove(); // Perform the move in the down direction
        } else if (move == 'a' || move == 'A') {
            leftmove(); // Perform the move in the left direction
        } else if (move == 'd' || move == 'D') {
            rightmove(); // Perform the move in the right direction
        } else if (move == 27) {
            cout << "Game over!" << endl; // If the user presses ESC, end the game
            break;
        } else {
            cout << "Invalid move!" << endl; // If the user enters an invalid move, display an error message and continue
            continue;
        }
        system("cls"); // Clear the console screen
        printBoard(); // Print the updated state of the board
        
        if (high_score < score) {
            high_score = score; // Update the high score if the current score is higher
        }
        
        // Check for game over
        if (check_game_over()) {
            cout << "Game over! Final score: " << score << endl; // Display the final score
            if (score > high_score) {
                high_score = score; // Update the high score if the current score is higher
                cout << "New high score: " << high_score << endl; // Display the new high score
            }
            break;
        }
    }
}


int main() {
    cout << "*************************************************Welcome to the game****************************************************\n";
    char choice;
    while (true) {
        cout << "(a) Play Game\n";
        cout << "(b) Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 'a' || choice == 'A') {
            playGame(); // Start the game
            break; // Exit the loop after the game ends
        } else if (choice == 'b' || choice == 'B') {
            cout << "Goodbye!\n";
            exit(0); // Exit the program
        } else {
            cout << "Invalid input, please enter 'a' or 'b'.\n";
        }
    }
    
    char askagain;
    while (true) {
        cout << "Play again? (y/n): ";
        cin >> askagain;
        if (askagain == 'y' || askagain == 'Y') {
            // Reset game variables and game board
            clearBoard();
            score = 0;
            playGame(); // Start the game again
        } else if (askagain == 'n' || askagain == 'N') {
            cout << "High score: " << high_score << endl;
            cout << "Thank you for playing the game (RANG BAAZ).";
            break; // Exit the loop and end the program
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
            continue;
        }
    }

    return 0;
}


