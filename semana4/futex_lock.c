#include <stdio.h>
#include <pthread.h>
#include<linux/futex.h>
#include<sys/syscall.h>
#include <sys/types.h>

volatile int i;

int futex_address = 0;

int futex_wait(void *addr, int value1){
  return syscall(SYS_futex, addr, FUTEX_WAIT, value1, NULL, NULL, 0);
}

int futex_wake(void *addr, int value2){
  return syscall(SYS_futex, addr, FUTEX_WAKE, value2, NULL, NULL, 0);
}

  
void* fthread_0(void *v) {
  futex_address = 0;
  futex_wait(&futex_address, 0);
  printf("thread0\n");
	return NULL;
}

void* fthread_1(void *v) {
  printf("thread1.1\n");
  sleep(10);
  futex_wake(&futex_address, 0);
  printf("thread1.2\n");
	return NULL;
}

int main() {
  pthread_t thread_0;
  pthread_t thread_1;
  pthread_create(&thread_0,NULL,fthread_0, NULL);	
	pthread_create(&thread_1,NULL,fthread_1, NULL);

	pthread_join(thread_0,NULL);
	pthread_join(thread_1,NULL);

	pthread_exit(NULL);
}


