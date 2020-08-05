
#include<fstream>
#include<iostream>

using namespace std;
const int N = 8;
/*you can change N to any positive integer; however, the solution is not
gauranteed for large integers due to the huge computational size of the
general problem*/

/*This program is written based on the popular algorithm of backtracking to solve
for the possible configuration of the N queen problem*/

/*Please, note that the solutions generated from this program are not all the
feasible solutions. This is due to the nature of the recursion function that
terminates once a solution is found along a specific tree that represents a
feasible solution*/

/*To generate all the solutions, I should first understand how to store a tree in
the memory and how to traverse it. Please, note that my knowledge as a physics
senior does not qualify for such experience in coding trees in C++!*/

/*Another important fact is that some solutions may be equivalent or isomorphic
if they belong to the same symmetry group applied on the chess board. This means
that not all the generated solution by this program are fundamental solutions.*/

/*The program can be modified to get solutions for arbitrary N queen on N*N chess
board; however, the program has not been tested for more than N=27 due to
time constraints*/

//First,I will write all utility functions that will be used in the main program

/*initialize an empty chess board*/
void make_clear_board(int board[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = 0;
		}
	}
}


/*Printing out the chess board*/
void print_chess_board(int mat[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << mat[i][j] << " ";
		}
		cout << "\n";
	}
	cout << endl;
}

/*setting up the bounding function to check whether a cell is attacked or not.*/
bool is_safe(int board[N][N], int row, int col) {
	int count = 0;
	for (int j = 0; j < col; j++) {
		for (int i = 0; i < N; i++) {
			if (board[i][j] == 1) {
				if (i == row || j == col || abs(i - row) == abs(j - col)) /*||
					abs(i + row) == abs(j + col))*/
					/*remember that we compare the current cell
					in the current column with only the left columns
					queen cells. We need only a constaraint on the difference
					diagonals*/
				{
					count = count++;
				}
			}
		}
	}
	if (count >= 1) {
		return false;
	}
	else {
		return true;
	}
}

/*setting up a function that returs the number of safe cells in a certain column
in a chess board where all preceding columns are already have a queen each
such that they are not attacking each other*/
int num_safe(int board[N][N], int col) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		if (is_safe(board, i, col)) {
			count++;
		}
	}
	return count;
}

/*This function will return the rows of a given column where a queen can be placed
and not be attacked by the other queens on the board*/
void get_safe_cells(int board[N][N], int col, int arr[N]) {

	int size = num_safe(board, col);
	int count = -1;

	for (int i = 0; i < N; i++) {
		arr[i] = -1;
	}

	for (int i = 0; i < N; i++) {
		if (is_safe(board, i, col)) {
			count++;
			arr[count] = i;
		}
	}
}

/*setting up a function to solve the n queen problem*/
bool NQueen_solver(int board[N][N], int col) {
	if (col == N) {
		return true;
	}
	for (int i = 0; i < N; i++) {
		if (is_safe(board, i, col)) {
			board[i][col] = 1;

			if (NQueen_solver(board, col + 1)) {
				return true;
			}
			board[i][col] = 0;
		}
	}

	return false;
}


/*to get all solutions resulted by placing the first queen in the first column in
different rows*/

void get_1st_col_solutions(int board[N][N]) {
	make_clear_board(board);
	for (int i = 0; i < N; i++) {
		board[i][0] = 1;
		if (NQueen_solver(board, 1)) {
			print_chess_board(board);
		}
		else {
			cout << "solution is not feasible for i =" << i << endl;
		}

		make_clear_board(board);

	}
}

/*This is another version of the function that takes also a text file as
a parameter in order to output the result into it to store the solutions on
the hard derive in a text file*/

void get_1st_col_solutions(int board[N][N], fstream& output) {
	make_clear_board(board);
	for (int i = 0; i < N; i++) {
		board[i][0] = 1;
		if (NQueen_solver(board, 1)) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					output << board[i][j] << " ";
				}
				output << endl;
			}
			output << endl << endl;
		}
		else {
			cout << "solution is not feasible for i =" << i << endl;
		}

		make_clear_board(board);

	}
}



/*Now, I will try to generate all possible solutions for N queens on N*N board*/

bool all_solutions(int board[N][N], int col) {
	if (col == N) {
		print_chess_board(board);
		return true;
	}

	int arr1[N];
	get_safe_cells(board, col, arr1);

	for (int i = 0; i < N; i++) {
		if (arr1[i] >= 0) {
			board[arr1[i]][col] = 1;

			if (all_solutions(board, col + 1)) {
				return true;
			}
			board[arr1[i]][col] = 0;
		}
	}

	return false;
}
/*Sadly, I have faced the same problem presented by the NQueen_solver function,
This function is a recursion function. It terminates once it finds a feasible
solution. If I managed to make the recursion function not terminate after finding
the first solution, this function "all_solutions" will generate all feasible
solutions for a general N queens on N*N chess board.*/

//The main program:

int main()
{
	//Display the solution on the console window
	int chess_board[N][N];

	get_1st_col_solutions(chess_board);


	//For writing the solution in a .txt file on the computer:

	/*fstream file;
	file.open("qsolve8.txt");

	if (!file) {
		cout << "Error!";
		return 0;
	}
	cout << "The file is oppened successfuly;";

	//defining the chess board

	int chess_board[N][N];

	get_1st_col_solutions(chess_board, file);


	file.close();



	return 0;*/

}