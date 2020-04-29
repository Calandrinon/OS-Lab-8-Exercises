#include <stdio.h>
#include <time.h>
#include <stdbool.h>

int main() {
	time_t t1 = time(NULL);
	int number_of_primes = 0;	
	
	for (int i = 1; i <= 1000000; i++) {
		bool prime = true;
		for (int j = 2; j <= i / 2; j++) {
			if (i % j == 0) {
				prime = false;	
				break;
			}
		}

		if (prime)
			number_of_primes++;
		printf("i=%d\n", i);
	}

	time_t t2 = time(NULL);	
	double x = difftime(t2, t1);	
	printf("time: %.0f\n", x);	
	printf("number of primes: %d\n", number_of_primes);
	return 0;	
}
