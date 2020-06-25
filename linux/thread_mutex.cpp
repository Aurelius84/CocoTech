#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_OF_TASKS 5

int money_of_tom = 100;
int money_of_jerry = 100;
int id = 0;

// pthread_mutex_t g_money_lock;

void* transfer(void* notused) {
    pthread_t tid = pthread_self();
    printf("Thread %u is transfering money.\n", id);
    // pthread_mutex_lock(&g_money_lock);
    usleep(rand() % 10);
    money_of_tom += 10;
    usleep(rand() % 10);
    money_of_jerry -= 10;
    id += 1;
    // pthread_mutex_unlock(&g_money_lock);
    printf("Thread %u finish transfering money.\n", id);
    pthread_exit((void*)0);
}

int main() {
  pthread_t threads[NUM_OF_TASKS];
  int rc, t;
//   pthread_mutex_init(&g_money_lock, NULL);
  for (t = 0; t < NUM_OF_TASKS;++t){
    rc = pthread_create(&threads[t], NULL, transfer, NULL);
    if(rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  for (t = 0; t < 100;t++){
    // pthread_mutex_lock(&g_money_lock);
    printf("total money: %d\n", money_of_jerry + money_of_tom);
    // pthread_mutex_unlock(&g_money_lock);
  }

//   pthread_mutex_destroy(&g_money_lock);
  pthread_exit(NULL);
}