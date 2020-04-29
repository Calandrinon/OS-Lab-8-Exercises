#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

int verified_numbers = 0, number_of_primes = 0;

typedef struct {
	int start, end;
} Interval;


void* check_primes(void* parameters) {
	Interval intv = *(Interval*)parameters;

	for (int i = intv.start; i <= intv.end; i++) {
		bool prime = true;
		for (int j = 2; j <= i / 2; j++) {
			if (i != j && i % j == 0) {
				prime = false;
				break;
			}
		} 
		
		//printf("%d\n", i);
		
		if (prime)
			number_of_primes++;
		verified_numbers++;
	}

}


int main() {
	int n;
	printf("Enter the number of threads: ");
	scanf("%d", &n);
	pthread_t threads[256];
	
	time_t t1 = time(NULL);	
	int last_end = 0;
	
	int range_end = 10000;

	for (int i = 1; i <= n; i++) {
		Interval intv = {last_end+1, last_end+range_end/n};		
		printf("Checking primes between %d and %d...\n", intv.start, intv.end);
		pthread_create(&threads[i], NULL, check_primes, &intv);
		last_end += range_end/n;
	} 
	
	for (int i = 1; i <= n; i++)
		pthread_join(threads[i], NULL);

	time_t t2 = time(NULL);
	double x = difftime(t2, t1);
	printf("Time elapsed: %.0f\n", x);		

	printf("The number of primes between 1 and %d is %d.\n", range_end, number_of_primes);	
	return 0;
}
