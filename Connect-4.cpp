#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class spaceStats{
	public:
		int col;
		int row;
		char type;
		spaceStats(int initCol, int initRow, int initType);
		void setCoords(int newCol, int newRow);
};

spaceStats :: spaceStats(int initCol, int initRow, int initType){
	col = initCol;
	row = initRow;
	type = initType;
}

void spaceStats :: setCoords(int newCol, int newRow){
	col = newCol;
	row = newRow;
}

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

// This is a MASSIVELY IMPORTANT Function for the rest of the program.... Be Warned!
int checkDir(char board[7][6], int col, int row, char player, spaceStats &barrier, bool incAllBlank, bool incOneBlank, bool includeAst, bool up, bool down, bool left, bool right){
	barrierType = 'E'; // if this E gets returned, we know there was an error somewhere... hence the 'E'
	bool barrierFound = false;
	int vertMod = 0;
	int horizMod = 0;
	
	//this is the int that will be returned, start at one, to assume the starting space is the colour we're looking for
	int lineCount = 1;
	
	//calculate the vertical and horizontal modifiers
	if(up && down){
		cout << "ERROR: 'up' and 'down' are both true." << endl;
	} else {
		if(up) vertMod = 1;
		else if(down) vertMod = -1;
	}
	
	if(left && right){
		cout << "ERROR: 'left' and 'right' are both true." << endl;
	} else {
		if(right) horizMod = 1;
		else if(left) horizMod = -1;
	}
	
	//keep looping if the next check is in the bounds of the board, and until the 
	for(int i = 1; col+i*horizMod >= 0 && col+i*horizMod < 7 && row+i*vertMod >= 0 && row+i*vertMod < 6 && !barrierFound; i++){
		char charToCheck = board[col + i*horizMod][row + i*vertMod];
		if(incAllBlank){
			if(charToCheck != player && returnNorm(charToCheck) != ' '){
				barrierFound = true;
				barrier.type = charToCheck;
				barrier.setCoords(col+i*horizMod, row+i*vertMod);
			} else {
				lineCount++;
			}
		} else if(includeAst){
			if(charToCheck != player && returnNorm(charToCheck) != '*'){
				barrierFound = true;
				barrier.type = charToCheck;
				barrier.setCoords(col+i*horizMod, row+i*vertMod);
			} else {
				lineCount++;
			}
		} else {
			if(charToCheck != player){
				//loop ONE more time if the incOneBlank bool was true
				if(incOneBlank && returnNorm(charToCheck) == ' '){
					incOneBlank = false;
				} else {
					barrierFound = true;
					barrier.type = charToCheck;
					barrier.setCoords(col+i*horizMod, row+i*vertMod);
				}
			} else {
				lineCount++;
			}
		}
	}
	
	//if no barrier was found, return 'B' to signify that the barrier was the border
	if(!barrierFound) barrier.type = 'B';
	barrier.col = -1;
	barrier.row = -1;
	
	return lineCount;
}

//Another Massively important function, However, this one simply implements the previous one in a nicer way, and gathers a lot of info from it
int checkAllDirs(char board[7][6], int col, int row, char player, spaceStats &barrier1, spaceStats &barrier2, bool incAllBlank, bool incOne, bool includeAst){
	int maxVal = 0;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	
	//create 2 spaceStats objects to keep track of the important barriers, any more than 2 isn't important, but we'll need to make sure that the 2 barriers are, in fact, useful
	
	//loop once for each direction, including diagonals, one for the all false state, but we'll ignore that one later
	for(int i = 0; i < 9; i++){
		//set up the direction bools, so I don't have to keep writing out the checkDir function... It's just too long, and this is more fun! 
		if(i/3 == 0){
			up = true;
			down = false;
		} else if(i/3 == 1){
			up = false;
			down = false;
		} else {
			up = false;
			down = true;
		}
		
		if(i%3 == 0){
			left = true;
			right = false;
		} else if(i%3 == 1){
			left = false;
			right = false;
		} else {
			left = false;
			right = true;
		}
		
		if(up || down || left || right){
			checkDir(board, col, row, player, barrier, incAllBlank, incOneBlank, includeAst, up, down, left, right);
		}
		
		
	}
	return maxVal;
}



//Functions to use the checkDir functions
int checkNew(char board[7][6], int col, char &barrierType, bool incAllBlank, bool incOne, bool includeAst){
	// the player and the heightOffset are both assumed
	return 0;
}

int checkOld(char board[7][6], int col, char player, char &barrierType, bool incAllBlank, bool incOne, bool includeAst){
	// the height offset is assumed
	return 0;
}

int checkNext(char board[7][6], int col, char &barrierType, bool incAllBlank, bool incOne, bool includeAst){
	// the player and the heightOffset are both assumed
	return 0;
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
	return false;
}

bool computerTurn(char board[7][6]){
	int newCol = getColInput(board);
	playPiece(board, true, newCol);
	printBoard(board);
	
	char barrierType = 'M';
	
	cout << "checkDir - E ==> " << checkDir(board, newCol, findEmpty(board, newCol) - 1, 'O', barrierType, false, true, false, false, false, false, true) << endl << "With barrierType: " << barrierType << endl;
	
	
	//return gotFour(board, newCol);
	return false;
}

void gameEnd(int turnCount){
	if(turnCount % 2){
		cout << "CONGRATULATIONS!!! YOU WIN!!!" << endl;
	} else {
		cout << "CONGRADULATE ME!!! I WON!!!!!" << endl;
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