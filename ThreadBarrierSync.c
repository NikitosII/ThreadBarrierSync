#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_barrier_t barrier;

void* func1(void* args) {
    int* flag1 = (int*)args;
    while (*flag1 == 0) {
        printf("proc1 completed\n");
        sleep(1);
    }
    pthread_barrier_wait(&barrier);
    pthread_exit((void*)1); // код завершения 1
}

void* func2(void* args) {
    int* flag2 = (int*)args;
    while (*flag2 == 0) {
        printf("proc2 completed\n");
        sleep(1);
    }
    pthread_barrier_wait(&barrier);
    pthread_exit((void*)2); // код завершения 2
}

int main() {
    pthread_t id1, id2;
    void* status;
    int flag1 = 0;
    int flag2 = 0;

    
    pthread_barrier_init(&barrier, NULL, 3);// (2 потока + основной поток)
    pthread_create(&id1, NULL, func1, (void*)&flag1);
    pthread_create(&id2, NULL, func2, (void*)&flag2);

    printf("Press key to stop...\n");
    getchar();
    sleep(0);
    flag1 = 1;
    flag2 = 1;

    pthread_barrier_wait(&barrier);
    pthread_join(id1, &status);
    printf("Thread 1 status %ld\n", (long)status);

    pthread_join(id2, &status);
    printf("Thread 2 status %ld\n", (long)status);

    pthread_barrier_destroy(&barrier);

}