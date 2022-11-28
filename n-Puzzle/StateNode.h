#include <list>
#include <iostream>
using namespace std;
#pragma once
const int n_size = 9;
const int col = 3;
const int row = 3;
class StateNode
{
public:
	list <StateNode> childern;
	StateNode* parent ;
	int blankPosition = 0;
	int puzzle[n_size]; 

	StateNode(int board[]) {
		setBoard(board);
	}
	StateNode() {
		for (int i = 0; i < n_size; i++)
			puzzle[i] = 0;
	};
	void setBoard(int board[]) {
		for (int i = 0; i < n_size; i++)
			this->puzzle[i] = board[i];
	}
	bool goalTest() {
		bool isGoal = true;
		int minmum = puzzle[0];
		for (int i = 1; i < n_size; i++) {
			if (minmum > puzzle[i]) {
				isGoal = false;
				break;
			}
			minmum = puzzle[i];
		}
		return isGoal;
	}

	// Explain moves
	/*
		expand node ---> legal moves of node
		1 2 3 
		4 5 6     ===> 1 2 3 4 5 6 7 8 0
		7 8 0
		=======================================
		explaine:
		_________
		1- Move right:
	    the only possible move to move right is (NOT in last column)
		the check for this condition in 1D array: ( indexBlank % number of cols != zero and not grater than number of columns)
		since count start from 0 in array we need to change condition into (col - 1)

		2- Move left:
		the only possible move to move left is (NOT in first column)
		the check for this condition in 1D array: ( indexBlank % number of cols != zero )
		since count start from 0 in array we need to change condition into (col - 1)
	*/

	void moveRight(int board[], int indexBlank) {
		if (indexBlank % col < col - 1) {
			// i don't to change my curr board
			int tempBoard[n_size];
			copyBoard(board, tempBoard);

			// swap 
			int temp = tempBoard[indexBlank + 1];
			tempBoard[indexBlank + 1] = tempBoard[indexBlank];
			tempBoard[indexBlank] = temp;

			StateNode *child = new StateNode(tempBoard);
			child->parent = this;
			childern.push_back(*child);
		}
	}
	void moveLeft(int board[], int indexBlank) {
		if (indexBlank % col > 0) {
			// i don't to change my curr board
			int tempBoard[n_size];
			copyBoard(board, tempBoard);

			// swap 
			int temp = tempBoard[indexBlank - 1];
			tempBoard[indexBlank - 1] = tempBoard[indexBlank];
			tempBoard[indexBlank] = temp;

			StateNode* child = new StateNode(tempBoard);
			child->parent = this;
			childern.push_back(*child);
			/*StateNode child(tempBoard);
			child.parent = this;
			childern.push_back(child);*/
		}
	}
	void moveUp(int board[], int indexBlank) {
		if (indexBlank - col >= 0) {

			// i don't to change my curr board
			int tempBoard[n_size];
			copyBoard(board, tempBoard);

			// swap 
			int temp = tempBoard[indexBlank - col];
			tempBoard[indexBlank - col] = tempBoard[indexBlank];
			tempBoard[indexBlank] = temp;

			StateNode* child = new StateNode(tempBoard);
			child->parent = this;
			childern.push_back(*child);
			/*StateNode child(tempBoard);
			child.parent = this;
			childern.push_back(child);*/
		}
	}
	void moveDown(int board[], int indexBlank) {
		if (indexBlank + col < n_size) {

			// i don't to change my curr board
			int tempBoard[n_size];
			copyBoard(board, tempBoard);

			// swap 
			int temp = tempBoard[indexBlank + col];
			tempBoard[indexBlank + col] = tempBoard[indexBlank];
			tempBoard[indexBlank] = temp;

			StateNode* child = new StateNode(tempBoard);
			child->parent = this;
			childern.push_back(*child);
			/*StateNode child(tempBoard);
			child.parent = this;
			childern.push_back(child);*/
		}
	}

	// to copy values b/w to boards
	void copyBoard(int srcBoard[], int disBoard[]) {
		for (int i = 0; i < n_size; i++) {
			disBoard[i] = srcBoard[i];
		}
	}

	// print Board
	void printBoard() {
		cout << endl;
		int m = 0;
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < col; j++) {
				cout << puzzle[m] <<" ";
				m++;
			}
			cout << endl;
		}
	}

	// to check if it the same puzzle after make a move
	bool isSamePuzzle(int board[]) {
		bool samePuzzle = true;
		for(int i=0; i<n_size; i++)
			if (puzzle[i] != board[i]) {
				samePuzzle = false;
				break;
			}
		return samePuzzle;
	}
	
	// expand all moves and that is correct will create a node as child
	void ExpandNodes() {
		for (int i = 0; i < n_size; i++) {
			if (puzzle[i] == 0) 
				blankPosition = i;
		}
		moveRight(puzzle, blankPosition);
		moveUp(puzzle, blankPosition);
		moveDown(puzzle, blankPosition);
		moveLeft(puzzle, blankPosition);
	}
};

