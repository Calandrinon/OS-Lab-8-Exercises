#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define TH_NR 5

int v, n;
pthread_mutex_t m, m2;

void* thread_handler(void* arg) {
	char* my_string = (char*)arg;
	
	for (int i = 0; i < strlen(my_string); i++) {
		if (my_string[i] >= '0' && my_string[i] <= '9') {
			pthread_mutex_lock(&m);
			n++;	
			pthread_mutex_unlock(&m);
		} else if (my_string[i] == 'a' || my_string[i] == 'e' ||  my_string[i] == 'i' ||  my_string[i] == 'o' ||  my_string[i] == 'u') {	
			pthread_mutex_lock(&m2);
			v++;	
			pthread_mutex_unlock(&m2);
		}
	}

	return NULL;	
}

int main() {
	pthread_t t[TH_NR];	
	char* strings[TH_NR];
	FILE* f = fopen("file.txt", "r");

	for (int i = 0; i < TH_NR; i++) {
		strings[i] = (char*)malloc(sizeof(char)*50);	
		fgets(strings[i], 50, f);
	}

	pthread_mutex_init(&m, NULL);

	for (int i = 0; i < TH_NR; i++) {
		pthread_create(&t[i], NULL, thread_handler, strings[i]);
	}


	for (int i = 0; i < TH_NR; i++) {
		pthread_join(t[i], NULL);
	}
	
	pthread_mutex_destroy(&m);
	pthread_mutex_destroy(&m2);



	for (int i = 0; i < TH_NR; i++) {
		free(strings[i]);
	}

	printf("The number of vowels: %d\n", v);
	printf("The number of digits: %d\n", n);
	return 0;
}
