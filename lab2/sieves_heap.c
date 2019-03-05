#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COLUMNS 6
int counter = 0;

void print_number(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS
	if (counter < COLUMNS - 1){
		printf("%10d ", n);
		printf("\t");
		counter++;
	}
	else{
		printf("%10d ", n);
		printf("\n");
		counter = 0;
	}
  }


void print_sieves(int n){
	bool *numbers;
	numbers = (bool*) malloc(sizeof(bool) * (n+1));
	for (int i = 0; i <= n+1; i++){
		numbers[i] = true;
	}
	for (int j = 2; j*j <= n+1; j++){
		for(int k = j * 2; k <= n+1; k += j){
			numbers[k] = false;
		}
	}

	for (int l = 1; l <= n+1; l++){
		if (numbers[l] == true){
			print_number(l);
		}
	}

free(numbers);
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}
