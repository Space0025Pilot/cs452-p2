/**File: lab.c
 * Author: Caitlyn Nelson
 * Date: 10/08/2024
 * Description: Definition of support functions used in main.c and implemented from lab.h
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "lab.h"
#include "../tests/harness/unity.h"

/* Variables */
// queue_t* queue;
// int currentSize = 0;
// int maxCapacity = 0;
// bool shutdownFlag = false;
// pthread_cond_t queueNotEmpty;
// pthread_cond_t queueNotFull;
// pthread_mutex_t queueLock;


typedef struct queue{
  int currentSize;
  int maxCapacity;
  bool shutdownFlag;
  pthread_cond_t queueNotEmpty;
  pthread_cond_t queueNotFull;
  pthread_mutex_t queueLock;
} *queue_t;


queue_t queue_init(int capacity){

  queue_t queue = (queue_t)malloc(sizeof(queue_t) * 10);
  queue->maxCapacity = capacity;
  queue->shutdownFlag = false;

  pthread_cond_init (&(queue->queueNotEmpty), NULL);
  pthread_cond_init (&(queue->queueNotFull), NULL);

  pthread_mutex_init (&(queue->queueLock), NULL);

  return queue;
}

void queue_destroy(queue_t q){
  free(q);
}

void enqueue(queue_t q, void *data){

  pthread_mutex_lock(&(q->queueLock));
  while(q->currentSize == q->maxCapacity && q->shutdownFlag == false){
    //Queue Full so must wait
    pthread_cond_wait(&(q->queueNotFull), &(q->queueLock));
  }
  if(q->shutdownFlag == true){
    pthread_mutex_unlock(&(q->queueLock));
    exit(0); //Not sure about this
  }
  q[q->currentSize] = *(queue_t)data;  //heap buffer overflow problem here, not sure how to add the data get some help with this.
  q->currentSize++;
  pthread_mutex_unlock(&(q->queueLock));
}

void *dequeue(queue_t q){
  pthread_mutex_lock(&(q->queueLock));
  while(q->currentSize == 0 && q->shutdownFlag == false){
    //queue empty so wait for producer to produce items
    pthread_cond_wait(&(q->queueNotEmpty), &(q->queueLock));
  }
  if(q->shutdownFlag == true && q->currentSize == 0){
    pthread_mutex_unlock(&(q->queueLock));
    exit(0);
  }
  int i = 0;
  for(i = 0; i < q->currentSize - 1; i++){
    q[i] = q[i+1];
  }
  q[i] = *(queue_t)NULL;
  q->currentSize--;
  pthread_mutex_unlock(&(q->queueLock));
  return q;
}

void queue_shutdown(queue_t q){
  pthread_mutex_lock(&(q->queueLock));
  q->shutdownFlag = true;
  pthread_mutex_unlock(&(q->queueLock));
}

bool is_empty(queue_t q){
  bool empty;
  pthread_mutex_lock(&(q->queueLock));
  if(q->currentSize == 0){
    empty = true;
  }
  else {
    empty = false;
  }
  pthread_mutex_unlock(&(q->queueLock));
  return empty;
}

bool is_shutdown(queue_t q){
  bool shutdown;
  pthread_mutex_lock(&(q->queueLock));
  if(q->shutdownFlag == true){
    shutdown = true;
  }
  else {
    shutdown = false;
  }
  pthread_mutex_unlock(&(q->queueLock));
  return shutdown;
}
