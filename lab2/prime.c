/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){
	int isPrime = 1;
	for (int i = 2; i < n; i++){
		if (n % i == 0){
			isPrime = 0;
			break;
		}
	}
	return isPrime;
		
	}

int main(void){
  printf("%d\n", is_prime(4));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(12)); // 383 is a prime.     Should print 1.
}

