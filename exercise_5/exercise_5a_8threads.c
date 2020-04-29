#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>

struct interval {
	int a, b;
};

int total_number_of_primes = 0;

void* primes(void* args) {		
	int number_of_primes = 0;	
	struct interval intv = *(struct interval*)args;	
	
	for (int i = intv.a; i <= intv.b; i++) {
		bool prime = true;
		for (int j = 2; j <= i / 2; j++) {
			if (i % j == 0 && i != j) {
				prime = false;	
				break;
			}
		}

		if (prime)
			number_of_primes++;
		//printf("i=%d\n", i);
	}

	total_number_of_primes += number_of_primes;
}

int main() {

	time_t t1 = time(NULL);

	pthread_t threads[8];
	
	struct interval ints[8] = {{1, 125000}, {125001, 250000}, {250001, 375000}, {375001, 500000}, {500001, 625000}, {625001, 750000}, {750001, 875000}, {875001, 1000000}};	

	for (int i = 0; i < 8; i++)	
		pthread_create(&threads[i], NULL, primes, &ints[i]);


	for (int i = 0; i < 8; i++)	
		pthread_join(threads[i], NULL);
	
	time_t t2 = time(NULL);	
	double x = difftime(t2, t1);	
	printf("time: %.0f\n", x);	

	printf("The total number of primes is %d.\n", total_number_of_primes);
	return 0;	
}
