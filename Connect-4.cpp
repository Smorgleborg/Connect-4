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
	cout << " - - - - - - - " << "\n\n" << endl;
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
	cout << " =-=-=-=-=-=-= " << "\n\n" << endl;
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

void playerTurn(board[7][6]){
	
}


int main(){
	char board[7][6];
	resetBoard(board);	
	printBoard(board);
	printBoardRaw(board);
	
	playPiece(board, false, 3);
	
	printBoardRaw(board);
}