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

	pthread_t thread1, thread2;
	
	struct interval first = {1, 500000};	
	struct interval second = {500001, 1000000};	
	pthread_create(&thread1, NULL, primes, &first);
	pthread_create(&thread2, NULL, primes, &second);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	time_t t2 = time(NULL);	
	double x = difftime(t2, t1);	
	printf("time: %.0f\n", x);	

	printf("The total number of primes is %d.\n", total_number_of_primes);
	return 0;	
}
