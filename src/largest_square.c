/*
author: Nicholas A. Hays
date: 2018-05-15T08:02:37+00:00
repo: https://github.com/nhays89/LargestSubSquare.git
*/

#include <stdio.h>
#include <stdlib.h>
/*
Given a 2d bool matrix as input find the largest square region of all 1s (largest sub square in bool matrix).

i.e

input:
1 1 1 0 0 1
1 1 1 1 0 1
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 0 0
0 1 1 1 1 1

output:
4

input process conversion:

1 1 1 0 0 1         1 1 1 0 0 1
1 1 1 1 0 1         1 2 2 1 0 1
1 1 1 1 1 1   -->   1 2 3 2 1 1
1 1 1 1 1 1   -->   1 2 3 3 2 2
1 1 1 1 0 0         1 2 3 4 0 1
0 1 1 1 1 1         0 1 2 3 1 1


Solution:

Create a duplicate array of input size, lets call it square_arr.
We will use this array to record the maximum square that can be built at each index.
Lets also have a variable to store the largest square size, max_square.
Iterate through the input bool array of cells starting at (0,0) to (n,m).
If the value at cell (i,j) is 1, then check neighboring cells in the square_arr to the left (i, i -1), below (i -1, i), and below and to the left (i - 1, i - 1) (if array bounds permits).
The smallest of those neighbors (+1) will determine the largest possible square that can be generated at cell (i,j) -> index_max_square.
We write index_max_square to square_arr, and then we check its value against 'max_square' to see if its the new largest possible square. If so, we set index_max_square to max_square.
Repeat this process until each index is checked then return the value of max_square to the caller.
*/
static void print_arr(const int * bool_arr, const int n, const int m);
static int process(int * bool_arr, const int n, const int m);
static int smallest(const int left, const int left_down, const int down);
int main(int argc, char *argv[]) {
	int n, m;
	int res = scanf(" %d %d", &n, &m);
	if(res  == EOF) {
		perror("incorrect args. expected input format = %d %d.");
		exit(EXIT_FAILURE);
	}
	int *bool_arr = malloc(sizeof(int) * n * m);
	if(bool_arr == NULL) {
		perror("unable to allocate memory");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(scanf("%d", &bool_arr[i * n + j]) != 1) {
				perror("invalid input argument");
				exit(EXIT_FAILURE);
			} 
		}
	}

	/*
	//debug
	printf("%d %d\n", n, m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			printf("%d ", (bool_arr[i * n + j]));
		}
		printf("\n");
	}
	printf("\n");
	*/
	printf("%d", process(bool_arr, n, m));
	free(bool_arr);		
}

/*
Determines the maximum possible square in a bool matrix.

	input process conversion:

1 1 1 0 0 1         1 1 1 0 0 1
1 1 1 1 0 1         1 2 2 1 0 1
1 1 1 1 1 1   -->   1 2 3 2 1 1
1 1 1 1 1 1   -->   1 2 3 3 2 2
1 1 1 1 0 0         1 2 3 4 0 1
0 1 1 1 1 1         0 1 2 3 1 1



@param bool_arr - boolean matrix
@param n - rows
@param m - columns
*/
static int process(int * bool_arr, const int n, const int m) {
	int * max_square_arr = malloc(sizeof(int) * n * m);
	if(max_square_arr == NULL) {
		perror("unable to allocate memory");
		exit(EXIT_FAILURE);
	}
 	int index_max_square;
	int max_square = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			int cur_index = i * n + j;
			index_max_square = bool_arr[cur_index];
			if(i > 0 && j > 0 && index_max_square == 1) {
				int left = max_square_arr[cur_index - 1];
				int left_down = max_square_arr[((i - 1) * n) + j - 1];
				int down = max_square_arr[((i - 1) * n) + j];
				index_max_square = smallest(left, left_down, down) + 1;
			}
			max_square_arr[cur_index] = index_max_square;
			if(index_max_square > max_square) {
				max_square = index_max_square;
			}
			// printf("%d ", index_max_square); //debug
		}
		// printf("\n"); //debug
	}
	free(max_square_arr);
	return max_square;
}


/*

Returns the smallest of three integers.

@param left - left of current index
@param left_down - left and down from current index
@param down - down from the current index
*/
static int smallest(const int left, const int left_down, const int down) {
	if(left < left_down) {
		if(left < down) {
			return left;
		} else {
			return down;
		}
	} else {
		if(left_down < down) {
			return left_down;
		} else {
			return down;
		}
	}
}








