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
#include <stdint.h>
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
  void **arr;
  int currentSize;
  int maxCapacity;
  bool shutdownFlag;
  pthread_cond_t queueNotEmpty;
  pthread_cond_t queueNotFull;
  pthread_mutex_t queueLock;
} *queue_t;

queue_t queue_init(int capacity){

  queue_t queue = (queue_t)malloc(sizeof(queue_t) * 100);
  queue->currentSize = 0;
  queue->maxCapacity = capacity;
  queue->shutdownFlag = false;

  queue->arr = malloc(sizeof(void *) * 100);
  

  pthread_cond_init (&(queue->queueNotEmpty), NULL);
  pthread_cond_init (&(queue->queueNotFull), NULL);

  pthread_mutex_init (&(queue->queueLock), NULL);
  // printf("Capacity %d CurrentSize: %d Shutdown Flag: %d Array Indexes: %d %d %d %d %d\n",queue->maxCapacity,queue->currentSize, queue->shutdownFlag, queue->arr[0],queue->arr[1],queue->arr[2],queue->arr[3],queue->arr[4]);

  return queue;
}

void queue_destroy(queue_t q){
  free(q->arr);
  free(q);
}

void enqueue(queue_t q, void *data){

  pthread_mutex_lock(&q->queueLock);
  while(q->currentSize == q->maxCapacity && q->shutdownFlag == false){
    //Queue Full so must wait
    pthread_cond_wait(&q->queueNotFull, &q->queueLock);
  }
  if(q->shutdownFlag == true){
    pthread_mutex_unlock(&q->queueLock);
    exit(0); //Not sure about this
  }
  int index = q->currentSize;
  // printf("Index: %d Data: %p", q->currentSize, data);
  q->arr[index] = data;
  q->currentSize++;
  pthread_mutex_unlock(&q->queueLock);

  pthread_cond_broadcast(&q->queueNotEmpty);
}

void *dequeue(queue_t q){
  void *num;
  pthread_mutex_lock(&q->queueLock);
  printf("Before while\n");
  while(q->currentSize == 0 && q->shutdownFlag == false){
    printf("Inside while for wait\n");
    //queue empty so wait for producer to produce items
    pthread_cond_wait(&q->queueNotEmpty, &q->queueLock); //hang here
    printf("After the wait\n");
  }
  if(q->shutdownFlag == true && q->currentSize == 0){
    printf("Inside if where shutdown\n");
    pthread_mutex_unlock(&q->queueLock);
    return NULL;
  }
  int i = 0;
  num = q->arr[i];
  for(i = 0; i < q->currentSize - 1; i++){
    q->arr[i] = q->arr[i+1];
  }
  q->arr[i] = NULL;
  q->currentSize--;
  pthread_mutex_unlock(&q->queueLock);
  pthread_cond_broadcast(&q->queueNotFull);
  return num;
}

void queue_shutdown(queue_t q){
  pthread_mutex_lock(&q->queueLock);
  q->shutdownFlag = true;
  pthread_cond_broadcast(&q->queueNotFull);
  pthread_mutex_unlock(&q->queueLock);
}

bool is_empty(queue_t q){
  bool empty;
  pthread_mutex_lock(&q->queueLock);
  if(q->currentSize == 0){
    empty = true;
  }
  else {
    empty = false;
  }
  pthread_mutex_unlock(&q->queueLock);
  return empty;
}

bool is_shutdown(queue_t q){
  bool shutdown;
  pthread_mutex_lock(&q->queueLock);
  if(q->shutdownFlag == true){
    shutdown = true;
  }
  else {
    shutdown = false;
  }
  pthread_mutex_unlock(&q->queueLock);
  return shutdown;
}
