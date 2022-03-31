#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

static volatile bool zezwolenie = false;

static volatile int buf;

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t petla = PTHREAD_COND_INITIALIZER,
                        wyswietl = PTHREAD_COND_INITIALIZER;

void* prod(void *p){
   int i;

   for (i=1;i<100;i++){
        pthread_mutex_lock(&mtx);
        if(zezwolenie)
        {
            pthread_cond_wait(&petla, &mtx);
        }
        buf = i;
        zezwolenie = true;
        pthread_cond_signal(&wyswietl);
        pthread_mutex_unlock(&mtx);
   }
}

void* kons(void *p){
   int i;
        pthread_cond_signal(&petla);
   for (i=1;i<100;i++){
        pthread_mutex_lock(&mtx);
        if(!zezwolenie)
        {
            pthread_cond_wait(&wyswietl, &mtx);
        }
        printf("%d\n", buf);
        zezwolenie = false;
        pthread_cond_signal(&petla);
        pthread_mutex_unlock(&mtx);
   }
}


int main(){
    pthread_t pth1, pth2;
    pthread_create(&pth1, NULL, prod, NULL);
    pthread_create(&pth2, NULL, kons, NULL);
    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);
}