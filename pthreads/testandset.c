//Andrew Marshall
//date:3/1/22
//file testandset.c
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


void *threadMaker(void *arg);

int testandset(int* lock);

int main (int arga, char *argb[]) {
    
    int iterations = 0;

    int threadnums = 0;

    char *threadnum = argb[1];

    char *iteration = argb[2];

	//if  makes sure there are three arguments 
	//atoi is converting strings to int 
    if (arga==3){
            threadnums =  atoi(threadnum);

            iterations = atoi(iteration);
        }
        else {
            printf("Not enough arguments, setting thread count to 4 and iterations to 10,000.\n");

            //default num of iterations and threads 
            iterations = 10000;

            threadnums = 4;
        }

    pthread_t newThread[threadnums];

    int status;

    for (int i = 0; i < threadnums; i++) {
        printf("Main here. Creating thread %d\n", i);
        // createing  the threads 
        status = pthread_create(&newThread[i], NULL, threadMaker, &iterations);
	//checking for errors 
        if (status != 0) {
            printf("Oops. pthread_create gave error code %d\n", status);
            exit(-1);
        }
    }

    
    return 0;
}

// the threadmaker function
void *threadMaker(void *arg) {
    

    int *iterations = (int *)arg;
    
    

    for (int i = 0; i < *iterations; i++) {
        
        
        printf("Hello World. Greetings from thread %d\n", i);
        
    }
   
    

    return NULL;
}
int testandset(int* lock){
    int LOCKED=0;
    int old;
    old= *lock;
    *lock = LOCKED;
    return old;
}
