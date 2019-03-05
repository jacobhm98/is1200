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
	int totNumbers = 8000;
	bool numbers[totNumbers];
	for (int i = 0; i <= totNumbers; i++){
		numbers[i] = true;
	}
	for (int j = 2; j*j <= totNumbers; j++){
		for(int k = j * 2; k <= totNumbers; k += j){
			numbers[k] = false;
		}
	}
	int count = 0;
	for (int l = 2; l < totNumbers; l++){
		if (numbers[l] == true){
			count++;
		}
		if (count == n){
			printf("%d", l);
			break;
		}
	}


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
