#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t m;
int multiples;

void* thread_handler(void* arg) {
	int number = *(int*)arg;	
	
	pthread_mutex_lock(&m);
	if (number % 2 == 0 || number % 5 == 0) {
		multiples++;
	}
	pthread_mutex_unlock(&m);
}


int main(int argc, char* argv[]) {
	pthread_t* t = (pthread_t*)malloc(sizeof(pthread_t)*argc);
	int numbers[argc];
	for (int i = 1; i < argc; i++) {
		int param = atoi(argv[i]);
		printf("%d\n", param);
		numbers[i] = param;
	}

	pthread_mutex_init(&m, NULL);
	
	for (int i = 1; i < argc; i++) {
		pthread_create(&t[i], NULL, thread_handler, (void*)&numbers[i]);
	}
	
	for (int i = 1; i < argc; i++) {
		pthread_join(t[i], NULL);
	}	
	
	pthread_mutex_destroy(&m);

	free(t);
	printf("The number of multiples of 2 or 5: %d\n", multiples);
	return 0;
}
