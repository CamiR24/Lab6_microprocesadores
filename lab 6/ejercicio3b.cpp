#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define NTHREADS 10

void *say_hello(void *threadNumber) {
	// Declarar la variable local que recibe el parametro
	long tID;
	// Casting del parametro tipo void a la variable local tipo long
	tID = (long)threadNumber;
  printf("Hello thread: %ld\n", tID);
  usleep(9000);
  printf("Bye from thread: %ld\n", tID);
  pthread_exit(NULL);
}

int main() {
  int rc;
  long i;
  
  pthread_t tid[NTHREADS];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (i=0; i < NTHREADS; i++) {
	rc = pthread_create(&tid[i], &attr, say_hello, (void *)i);
	rc = pthread_join(tid[i], NULL);
	
	// La variable rc recibe errores en formato entero
    if (rc) {              
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  // Liberar espacios de memoria utilizados para atributo
  pthread_attr_destroy(&attr);
  pthread_exit(NULL);

}