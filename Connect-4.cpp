#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

char returnNorm(char raw){
	//take the raw value of the character, and return a copy of a "cleaned up" version of it
	
	if(raw == '*' || raw == '~' || raw == 'l' || raw == 'w' || raw == 't'){
		raw = ' ';
	}
	
	return raw;
}

int findEmpty(char board[7][6], int col){
	for(int i = 0; i < 6; i++){
		if(returnNorm(board[col][i]) == ' '){
			return i;
		}
	}
	
	// use 6 as the failcase if the column is full -> this is needed for some calculations later
	return 6;
}

//board handling functions
void resetBoard(char board[7][6]){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 7; j++){
			board[j][i] = (i == 0 ? '*' : ' ');
		}
	}
}

void printBoardRaw(char board[7][6]){
	cout << " 1 2 3 4 5 6 7 " << endl;
	cout << " - - - - - - - " << endl;
	
	for(int i = 5; i >= 0; i--){
		cout << "|";
		for(int j = 0; j < 7; j++){
			cout << board[j][i] << (j == 6 ? "|" : " ");
		}
		cout << endl;
	}
	cout << " - - - - - - - " << endl;
	cout << " 1 2 3 4 5 6 7 " << endl;
	cout << "\n\n" << endl;
}

void printBoard(char board[7][6]){
	cout << " 1 2 3 4 5 6 7 " << endl;
	cout << " =-=-=-=-=-=-= " << endl;
	
	for(int i = 5; i >= 0; i--){
		cout << "|";
		for(int j = 0; j < 7; j++){
			cout << returnNorm(board[j][i]) << (j == 6 ? "|" : " ");
		}
		cout << endl;
	}
	cout << " =-=-=-=-=-=-= " << endl;
	cout << " 1 2 3 4 5 6 7 " << endl;
	cout << "\n\n" << endl;
}

void playPiece(char board[7][6], bool isComp, int col){
	int row = findEmpty(board, col);
	char newPiece = (isComp ? 'O' : 'X');
	
	board[col][row] = newPiece;
	
	if(row < 6){
		board[col][row + 1] = '*'; 
	}
	
	//updateBoardSigns
}

int getColInput(char board[7][6]){
	int newCol = 0;
	do {
		do{
			cout << "Please input the number of the column that you would like to play in: ";
			cin >> newCol;
			cout << endl;
			newCol -= 1;
			
		// keep looping until the input is within the range of the board
		} while (newCol < 0 || newCol >= 7);
	// keep looping if the selected column was full
	} while (findEmpty(board, newCol) == 6);
		
	return newCol;
}

bool playerTurn(char board[7][6]){
	int newCol = getColInput(board);
	playPiece(board, false, newCol);
	printBoard(board);
	
	//return gotFour(board, newCol);
	return true;
}

bool computerTurn(char board[7][6]){
	int newCol = getColInput(board);
	playPiece(board, true, newCol);
	printBoard(board);
	
	//return gotFour(board, newCol);
	return false;
}

void gameEnd(int turnCount){
	if(turnCount % 2){
		cout << "CONGRATULATIONS!!! YOU WIN!!!" << endl;
	} else {
		cout << "CONGRADULATE ME!!! AS I WON!!" << endl;
	}
}

int main(){
	//create the board
	char board[7][6];
	resetBoard(board);
	
	bool gameOver = false;
	int turnCount = 0;
	
	printBoard(board);

	
	while(!gameOver){
		gameOver = playerTurn(board);
		turnCount++;
		
		if(!gameOver){
			gameOver = computerTurn(board);
			turnCount++;
		
		}
	}
	
	gameEnd(turnCount);
}