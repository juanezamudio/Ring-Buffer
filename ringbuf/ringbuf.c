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

#define BUFFER_SIZE 10

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
int consumer0_index = 0;
int consumer1_index = 1;

void enqueue(struct message msg) {
  pthread_mutex_lock(&mutex);

  if(count == BUFFER_SIZE) {
    pthread_cond_wait(&allow_produce, &mutex);
  }

  shared_buffer[enqueue_index] = msg;
  count++;

  if (enqueue_index == (BUFFER_SIZE - 1)) {
    enqueue_index = 0;
  } else {
    enqueue_index++;
  }

  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&allow_consume);
}

struct message dequeue() {
  struct message result;

  pthread_mutex_lock(&mutex);

  if (count == 0) {
    pthread_cond_wait(&allow_consume, &mutex);
  }

  result = shared_buffer[dequeue_index];
  count--;

  if (dequeue_index == BUFFER_SIZE - 1) {
    dequeue_index = 0;
  } else {
    dequeue_index++;
  }

  pthread_mutex_unlock(&mutex);
  pthread_cond_signal(&allow_produce);

  return result;
}

void nsleep(int sleep_milli) {
  int millisec = sleep_milli; // length of time to sleep, in miliseconds
  struct timespec req = {0};
  req.tv_sec = 0;
  req.tv_nsec = millisec * 1000000L;
  nanosleep(&req, (struct timespec *)NULL);
}

void *threadProducer() {
  char inputline[100];
  int value;
  int producer_sleep;
  int consumer_sleep;
  int print_code;
  int line_number = 1;

  struct message msg;
  struct message msgFinal1;
  struct message msgFinal2;

  // while (fgets(inputline, 100, stdin) != NULL) {

      // if (sscanf(inputline, "%d %d %d %d", &value, &producer_sleep, &consumer_sleep, &print_code) != EOF) {
    while (scanf(inputline, "%d %d %d %d", &value, &producer_sleep, &consumer_sleep, &print_code) > 0) {
        if (producer_sleep != 0) {
          nsleep(producer_sleep);
        }

        msg.value = value;
        msg.consumer_sleep = consumer_sleep;
        msg.print_code = print_code;
        msg.line = line_number;
        msg.quit = 0;

        enqueue(msg);

        if (msg.print_code == 1 || msg.print_code == 3) {
          printf("Producer: value %d from input line %d\n", value, line_number);
        }

      // } else {
      //   msgFinal1.quit = 1;
      //   msgFinal2.quit = 1;
      //
      //   enqueue(msgFinal1);
      //   enqueue(msgFinal2);
      // }
      //
      // if (msg.print_code == 1 || msg.print_code == 3) {
      //   printf("Producer: value %d from input line %d\n", value, line_number);
      // }
      line_number++;
  }

  msgFinal1.quit = 1;
  msgFinal2.quit = 1;

  enqueue(msgFinal1);
  enqueue(msgFinal2);

  return NULL;
}

void *threadConsumer0(void *index) {

  while(1) {
    struct message msg = dequeue();

    if (msg.quit == 0) {
      nsleep(msg.consumer_sleep);
      total_sum += msg.value;

      if (msg.print_code == 2 || msg.print_code == 3) {
        printf("Consumer %d: %d from input line %d; sum = %d\n", *((int *)index), msg.value, msg.line, total_sum);
      }
    } else {
      printf("Consumer %d: final sum is %d\n", *((int *)index), total_sum);

      index = &total_sum;
      pthread_exit(index);
    }
  }


  return NULL;
}

void *threadConsumer1(void *index) {

  while(1) {
    struct message msg = dequeue();

    if (msg.quit == 0) {
      nsleep(msg.consumer_sleep);
      total_sum += msg.value;

      if (msg.print_code == 2 || msg.print_code == 3) {
        printf("Consumer %d: %d from input line %d; sum = %d\n", *((int *)index), msg.value, msg.line, total_sum);
      }
    } else {
      printf("Consumer %d: final sum is %d\n", *((int *)index), total_sum);

      index = &total_sum;
      pthread_exit(index);
    }
  }


  return NULL;
}

int main(int argc, char **argv) {
  setlinebuf(stdout);

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&allow_produce, NULL);
  pthread_cond_init(&allow_consume, NULL);

  pthread_create(&consumer0, NULL, threadConsumer0, &consumer0_index);
  pthread_create(&consumer1, NULL, threadConsumer1, &consumer1_index);
  pthread_create(&producer, NULL, threadProducer, NULL);

  pthread_join(consumer0, NULL);
  pthread_join(consumer1, NULL);
  pthread_join(producer, NULL);


  printf("Main: total sum is %d\n", total_sum);
  return 1;
}
