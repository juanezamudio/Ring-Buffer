/**
 * Ring-Buffer Lab
 * April 4th, 2018
 *
 * Juan Zamudio - jzamudio
 * Rosario Huamani Carpio - rhuamanicarpio
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

void ringBuffer (pthread_t threadP, pthread_t threadC1, pthread_t threadC2, struct message msg) {

}

void threadProducer() {
  return;
}

void threadConsumer0() {
  return;
}

void threadConsumer1() {
  return;
}

void getMilli(int consumer_sleep_milli) {
  int milisec = consumer_sleep_milli; // length of time to sleep, in miliseconds
  struct timespec req = {0};
  req.tv_sec = 0;
  req.tv_nsec = milisec * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);
}

int main(int argc, char **argv) {
  // pthread_create(&consumer0, NULL, threadConsumer0, NULL);
  // pthread_create(&consumer1, NULL, threadConsumer1, NULL);
  // pthread_create(&producer, NULL, threadProducer, NULL);

  char inputline[100];
  int value;
  int producer_sleep;
  int consumer_sleep;
  int print_code;
  int line_number = 1;

  struct message msg;

  while (fgets(inputline, 1000, stdin) != NULL) {
      sscanf(inputline, "%d %d %d %d", &value, &producer_sleep, &consumer_sleep, &print_code);
      printf("%s", inputline);

      msg.value = value;
      msg.consumer_sleep = consumer_sleep;
      msg.print_code = print_code;
      msg.line = line_number;
      msg.quit = 0;

      if (consumer_sleep != 0) {
        getMilli(consumer_sleep);
      }

      line_number++;
  }


}
