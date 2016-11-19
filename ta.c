#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define SLEEP 0
#define N 100

/* 
Global variables here 
*/

void *student_func(void * params);
void *ta_func(void * ptr);


int main(int argc, char *argv[])
{
	int i;
	//N student threads 
	pthread_t students[N];
	int student_number[N];
	for(i=0;i<N;i++)
	{
		student_number[i]=i;
	}
	//TA thread
	pthread_t ta;
	//Lock for if TA is sleeping
	pthread_mutex_t isSleep;
	//Lock for if TA is in the room(office hours)
	pthread_mutex_t inRoom;
	//Lock for if TA is teaching another student
	pthread_mutex_t isOccupied;
	
	
	
	//Create N student thread
	for(i=0; i<N;i++)
	{
		pthread_t tpr = students[i];
		pthread_create(&tpr, NULL, student_func, &student_number[i]);
		printf("Student %d is initially waiting\n",i+1);
	}
	
	//Create TA thread
	pthread_create(&ta, NULL, ta_func, (void *) &i);
	 

	return 0;
}
void *student_func(void * ptr){

}
void *ta_func(void * ptr){

}
