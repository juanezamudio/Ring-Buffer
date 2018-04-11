/**
 * Ring-Buffer Lab
 * April 4th, 2018
 *
 * jzamudio - Juan Zamudio
 * rhuamanicarpio - Rosario Huamani Carpio
 */

/**
 * Creating,and,reaping,threads:
 *  pthread_create()
 *  pthread_join()
 *
 * Determining thread ID:
 *  pthread_self()
 *
 * Terminating threads:
 *  pthread_cancel()
 *  pthread_exit()
 *  exit() [terminates,all,threads]
 *  return [terminates,current,thread]
 *
 * Synchronizing,access,to,shared,variables:
 *  pthread_mutex_init
 *  pthread_mutex_[un]lock
 */

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 10;

// global declarations
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_value = PTHREAD_COND_INITIALIZER;
pthread_cond_t has_space = PTHREAD_COND_INITIALIZER;

pthread_t consumer0;
pthread_t consumer1;
pthread_t producer;

struct message {
  int value;          /* value to be passed to consumer */
  int consumer_sleep; /* time (in ms) for consumer to sleep */
  int line;           /* line number in input file */
  int print_code;     /* output code */
  int quit;           /* non-zero if consumer should exit */
};



void *threadProducer (void *vargp) {

}

void *threadConsumer0 (void *vargp) {

}

void *threadConsumer1 (void *vargp) {

}

int main() {
  pthread_create(&consumer0, NULL, &threadConsumer0(&consumer0), &consumer0);
  pthread_create(&consumer1, NULL, &threadConsumer1(&consumer1), &consumer1);


}
