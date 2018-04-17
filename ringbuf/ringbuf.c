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
pthread_cond_t allow_produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t allow_consume = PTHREAD_COND_INITIALIZER;

struct message {
  int value;          /* value to be passed to consumer */
  int consumer_sleep; /* time (in ms) for consumer to sleep */
  int line;           /* line number in input file */
  int print_code;     /* output code */
  int quit;           /* non-zero if consumer should exit */
};

pthread_t consumer0;
pthread_t consumer1;
pthread_t producer;
int total_sum = 0;
struct message shared_buffer[BUFFER_SIZE];
int count = 0;
int enqueue_index = 0;        // where to produce
int dequeue_index = 0;        // where to consume

void enqueue(struct message msg) {
  pthread_mutex_lock(&mutex);

  if(count < BUFFER_SIZE) {
    shared_buffer[buffer_index] = msg;
    count++;
    buffer_index++;
  } else {
    pthread_cond_wait(&allow_produce, &mutex);
  }
  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&allow_consume);
}

void dequeue() {
  pthread_mutex_lock(&mutex);

  if (count == BUFFER_SIZE) {
    buffer_index = 0;
    count--;
    return shared_buffer[buffer_index];
  } else {
    pthread_cond_wait(&allow_consume, &mutex);
  }

  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&allow_produce);

  if
}

// void ringBuffer (pthread_t threadP, pthread_t threadC1, pthread_t threadC2, struct message msg) {
//
// }

void *threadProducer(int value, int line_number) {
  char inputline[100];
  int value;
  int producer_sleep;
  int consumer_sleep;
  int print_code;
  int line_number = 1;

  struct message msg;
  struct message msgFinal1;
  struct message msgFinal2;

  while (fgets(inputline, 1000, stdin) != NULL) {

      if (sscanf(inputline, "%d %d %d %d", &value, &producer_sleep, &consumer_sleep, &print_code) != EOF) {
        printf("%s", inputline);

        if (producer_sleep != 0) {
          nsleep(producer_sleep);
        }

        msg.value = value;
        msg.consumer_sleep = consumer_sleep;
        msg.print_code = print_code;
        msg.line = line_number;
        msg.quit = 0;

        enqueue(msg);

        line_number++;
      } else {
        msgFinal1.quit = 1;
        msgFinal2.quit = 1;

        enqueue(msgFinal1);
        enqueue(msgFinal2);
      }
  }

  printf("Producer: value %d from input line %d\n", value, line_number);
}

void *threadConsumer0(void *index) {
  dequeue(struct message msg)

  return index;
}

void *threadConsumer1(void *index) {
  pthread_mutex_lock
  pthread_mutex_unlock
  return index;
}

void nsleep(int sleep_milli) {
  int millisec = sleep_milli; // length of time to sleep, in miliseconds
  struct timespec req = {0};
  req.tv_sec = 0;
  req.tv_nsec = millisec * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);
}

int main(int argc, char **argv) {
  setlinebuf(stdout);

  int retC0;
  int retC1;
  // int retP;
  int consumer0_index = 0;
  int consumer1_index = 1;

  retC0 = pthread_create(&consumer0, NULL, threadConsumer0, &consumer0_index);
  retC1 = pthread_create(&consumer1, NULL, threadConsumer1, &consumer1_index);
  // retP = pthread_create(&producer, NULL, threadProducer(value, line_number), NULL);


  pthread_join(consumer0, NULL);
  pthread_join(consumer1, NULL);

  printf("Main: total sum is %d\n", total_sum);
}
