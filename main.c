/*
nano filename.c
cc -pthread filename.c -o filename
./filename
*/

//P&C(T&S)
/*
define BUFFER_SIZE
initialize buffer[BUFFER_SIZE]
in = 0
out = 0
initialize semaphore empty = BUFFER_SIZE   // empty slots
initialize semaphore full = 0              // filled slots
initialize mutex lock
procedure PRODUCER:
    while true:
        sleep for random time
        item = generate random data
        wait(empty)           // check for empty slot
        lock(mutex)
        buffer[in] = item
        print "Producer produced item at position in"
        in = (in + 1) mod BUFFER_SIZE
        unlock(mutex)
        signal(full)          // increase filled slots
procedure CONSUMER:
    while true:
        sleep for random time
        wait(full)            // check for available item
        lock(mutex)
        item = buffer[out]
        print "Consumer consumed item from position out"
        out = (out + 1) mod BUFFER_SIZE
        unlock(mutex)
        signal(empty)         // increase empty slots
main:
    create producer thread
    create consumer thread
    wait for threads to finish
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 3

int buf[SIZE];
int in = 0, out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item, num;
    while (1) {
        num = rand() % 5;
        sleep(num);
        item = (rand() % 10) * 10;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buf[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    int item, num;
    while (1) {
        num = rand() % 5;
        sleep(num);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buf[out];
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int main() {
    pthread_t pthr, cthr;
    sem_init(&empty, 0, SIZE);  // initially SIZE empty slots
    sem_init(&full, 0, 0);      // initially 0 full slots
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&pthr, NULL, producer, NULL);
    pthread_create(&cthr, NULL, consumer, NULL);
    pthread_join(pthr, NULL);
    pthread_join(cthr, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
*/

//P&C(T&M)
/*
define BUFFER_SIZE
initialize buffer[BUFFER_SIZE]
in = 0
out = 0
count = 0
initialize mutex lock
initialize condition not_full
initialize condition not_empty
procedure PRODUCER:
    while true:
        sleep for random time
        item = generate random data
        lock(mutex)
        while count == BUFFER_SIZE:
            wait(not_full, mutex)
        buffer[in] = item
        print "Producer produced item at position in"
        in = (in + 1) mod BUFFER_SIZE
        count = count + 1
        signal(not_empty)
        unlock(mutex)
procedure CONSUMER:
    while true:
        sleep for random time
        lock(mutex)
        while count == 0:
            wait(not_empty, mutex)
        item = buffer[out]
        print "Consumer consumed item from position out"
        out = (out + 1) mod BUFFER_SIZE
        count = count - 1
        signal(not_full)
        unlock(mutex)
main:
    initialize mutex and condition variables
    create producer thread
    create consumer thread
    wait for threads to finish
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 3

int buf[SIZE];
int in = 0, out = 0;
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t not_full, not_empty;

void *producer(void *arg) {
    int item, num;
    while (1) {
        num = rand() % 5;
        sleep(num);
        item = (rand() % 10) * 10;
        pthread_mutex_lock(&mutex);
        while (count == SIZE)
            pthread_cond_wait(&not_full, &mutex);
        buf[in] = item;
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % SIZE;
        count++;
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg) {
    int item, num;
    while (1) {
        num = rand() % 5;
        sleep(num);
        pthread_mutex_lock(&mutex);
        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);
        item = buf[out];
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % SIZE;
        count--;
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t pthr, cthr;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);
    pthread_create(&pthr, NULL, producer, NULL);
    pthread_create(&cthr, NULL, consumer, NULL);
    pthread_join(pthr, NULL);
    pthread_join(cthr, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    return 0;
}
*/

//R&W(T&S)
/*
initialize shared clock (hrs, min, sec)
read_count = 0
initialize semaphore mutex = 1
initialize semaphore write_lock = 1
procedure READER(reader_id):
    while true:
        wait(mutex)
        read_count = read_count + 1
        if read_count == 1:
            wait(write_lock)
        signal(mutex)
        read shared clock
        print reader_id and clock value
        wait(mutex)
        read_count = read_count - 1
        if read_count == 0:
            signal(write_lock)
        signal(mutex)
        sleep
procedure WRITER:
    while true:
        wait(write_lock)
        update clock time
        print updated clock value
        signal(write_lock)
        sleep
main:
    initialize semaphores
    create multiple reader threads
    create one writer thread
    wait for all threads to finish
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int hrs = 23, min = 59, sec = 55;
int rc = 0;

sem_t mutex;
sem_t wrt;
void *reader(void *arg) {
    int reader_number = (int)(long)arg;
    while (1) {
        sem_wait(&mutex);
        rc++;
        if (rc == 1) sem_wait(&wrt);
        sem_post(&mutex);
        printf("Reader %d reading clock: %02d:%02d:%02d\n", reader_number, hrs, min, sec);
        sleep(1);
        sem_wait(&mutex);
        rc--;
        if (rc == 0) sem_post(&wrt);
        sem_post(&mutex);
        sleep(1);
    }
}
void *writer(void *arg) {
    while (1) {
        sem_wait(&wrt);
        sec++;
        if (sec == 60) {
            sec = 0;
            min++;
            if (min == 60) {
                min = 0;
                hrs = (hrs + 1) % 24;
            }
        }
        printf("Writer updated clock to: %02d:%02d:%02d\n", hrs, min, sec);
        sem_post(&wrt);
        sleep(1);
    }
}
int main() {
    pthread_t r1, r2, r3, w;
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    pthread_create(&r1, NULL, reader, (void *)1);
    pthread_create(&r2, NULL, reader, (void *)2);
    pthread_create(&r3, NULL, reader, (void *)3);
    pthread_create(&w, NULL, writer, NULL);
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w, NULL);
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
*/

//R&W(T&M)
/*
initialize shared clock (hrs, min, sec)
readers = 0
writers = 0
waiting_writers = 0
initialize mutex
initialize condition can_read
initialize condition can_write
procedure READER(reader_id):
    while true:
        lock(mutex)
        while writers > 0 OR waiting_writers > 0:
            wait(can_read, mutex)
        readers = readers + 1
        unlock(mutex)
        read shared clock
        print reader_id and clock value
        lock(mutex)
        readers = readers - 1
        if readers == 0:
            signal(can_write)
        unlock(mutex)
        sleep
procedure WRITER:
    while true:
        lock(mutex)
        waiting_writers = waiting_writers + 1
        while readers > 0 OR writers > 0:
            wait(can_write, mutex)
        waiting_writers = waiting_writers - 1
        writers = writers + 1
        unlock(mutex)
        update shared clock
        print updated clock value
        lock(mutex)
        writers = writers - 1
        if waiting_writers > 0:
            signal(can_write)
        else:
            broadcast(can_read)
        unlock(mutex)
        sleep
main:
    initialize mutex and condition variables
    create multiple reader threads
    create one writer thread
    wait for all threads to finish
*/
/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int hrs = 23, min = 59, sec = 55;
int readers = 0, writers = 0, waiting_writers = 0;

pthread_mutex_t mutex;
pthread_cond_t can_read, can_write;

void *reader(void *arg) {
    int id = (int)(long)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (writers > 0 || waiting_writers > 0)
            pthread_cond_wait(&can_read, &mutex);
        readers++;
        pthread_mutex_unlock(&mutex);
        printf("Reader %d reading clock: %02d:%02d:%02d\n", id, hrs, min, sec);
        sleep(1);
        pthread_mutex_lock(&mutex);
        readers--;
        if (readers == 0) pthread_cond_signal(&can_write);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
void *writer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        waiting_writers++;
        while (readers > 0 || writers > 0)
            pthread_cond_wait(&can_write, &mutex);
        waiting_writers--;
        writers++;
        pthread_mutex_unlock(&mutex);
        sec++;
        if (sec == 60) {
            sec = 0;
            min++;
            if (min == 60) {
                min = 0;
                hrs = (hrs + 1) % 24;
            }
        }
        printf("Writer updated clock to: %02d:%02d:%02d\n", hrs, min, sec);
        sleep(1);
        pthread_mutex_lock(&mutex);
        writers--;
        if (waiting_writers > 0)
            pthread_cond_signal(&can_write);
        else
            pthread_cond_broadcast(&can_read);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
int main() {
    pthread_t r1, r2, r3, w;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&can_read, NULL);
    pthread_cond_init(&can_write, NULL);
    pthread_create(&r1, NULL, reader, (void *)1);
    pthread_create(&r2, NULL, reader, (void *)2);
    pthread_create(&r3, NULL, reader, (void *)3);
    pthread_create(&w, NULL, writer, NULL);
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(r3, NULL);
    pthread_join(w, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&can_read);
    pthread_cond_destroy(&can_write);
    return 0;
}
*/

