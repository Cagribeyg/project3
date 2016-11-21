#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define WAITING 0
#define BORED 1
#define ASKING 2
#define LEFT (student_no+1)%N
#define RIGHT (student_no+2)%N
#define N 100
#define SLEEP 50

int state[N];
pthread_cond_t cond[N];
pthread_mutex_t mutex[N];
pthread_mutex_t sleepLock;

void *student_func(void * num);
void *ta_func(void * ptr);
void askTA(int student_no);
void leaveTAroom(int student_no);
int ta_is_sleeping();
void test(int student_no);


int main(int argc, char *argv[])
{
	int i;
	//N student threads 
	pthread_t students[N];
	int student_number[N];
	//Mutex initiation and state defining
	for(i=0;i<N;i++)
	{
		state[i]= WAITING;
		student_number[i]=i;
		pthread_mutex_init(&mutex[i], NULL);
		pthread_cond_init(&cond[i], NULL);
	}

	//TA thread
	pthread_t ta;
	
	

	//Create N student thread
	for(i=0; i<N;i++)
	{

		pthread_t tpr = students[i];
		pthread_create(&tpr, NULL, student_func, (void *) &i);
		printf("Student %d is initially waiting\n",i);
		pthread_join(tpr,NULL);
	}
	
        
	
	//Create TA thread
	pthread_create(&ta, NULL, ta_func, (void *) &i);
	 

	return 0;
}
void *student_func(void * student_no){
	

	while(1)
	{
		int *num= (int *) student_no;
		int x = *num;
		sleep(1);
		askTA(x);
		sleep(0);
		leaveTAroom(x);
	}

}



void *ta_func(void * ptr){

}
void askTA(int student_no)
{
	pthread_mutex_lock(&mutex[student_no]);
	printf("Student %d is asking TA a question\n",student_no );
	state[student_no]=BORED;
	test(student_no);

	while(state[student_no]!=ASKING)
	{
		printf("aa\n");
		pthread_cond_wait(&cond[student_no],&mutex[student_no]);
	}

	pthread_mutex_unlock(&mutex[student_no]);


	
}
void test(int student_no)
{
	if(state[LEFT]!=ASKING && state[RIGHT]!=ASKING&&state[student_no]==BORED)
	{
		//printf("asd\n");
		state[student_no]=ASKING;
		pthread_cond_signal(&cond[student_no]);

	}
}
void leaveTAroom(int student_no)
{
	pthread_mutex_lock(&mutex[student_no]);
	printf("Student %d has lock and leaving the room\n", student_no);
	state[student_no] = WAITING;
	test(LEFT);
	test(RIGHT);
	pthread_mutex_unlock(&mutex[student_no]);

}
/*int ta_is_sleeping()
{
	static int slp = SLEEP;

	int temp;
	pthread_mutex_lock(&sleepLock);
	if(slp > 0)
		slp--;
	temp = slp;
	pthread_mutex_unlock(&sleepLock);
	return temp;
}*/

