//P&C(T&S)
/*
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define SIZE 3

int buffer[SIZE];
int in=0, out=0;

sem_t emptySlots;
sem_t fullSlots;
pthread_mutex_t lockBuffer;

void* producer(void* arg){
    while (true){
        int item = rand() % 100;
        sleep(rand() % 3);
        sem_wait(&emptySlots);
        pthread_mutex_lock(&lockBuffer);
        buffer[in] = item;
        cout << "Producer produced " << item << " at " << in << endl;
        in=(in+1)%SIZE;
        pthread_mutex_unlock(&lockBuffer);
        sem_post(&fullSlots);
    }
}

void* consumer(void* arg){
    while (true){
        sleep(rand() % 3);
        sem_wait(&fullSlots);
        pthread_mutex_lock(&lockBuffer);
        int item = buffer[out];
        cout << "Consumer consumed " << item << " from " << out << endl;
        out=(out+1)%SIZE;
        pthread_mutex_unlock(&lockBuffer);
        sem_post(&emptySlots);
    }
}

int main(){
    int numP=2, numC=3;
    pthread_t producers[numP], consumers[numC];
    sem_init(&emptySlots, 0, SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&lockBuffer,NULL);
    for(int i=0;i<numP;i++)
        pthread_create(&producers[i], NULL, producer, NULL);
    for(int i=0;i<numC;i++)
        pthread_create(&consumers[i], NULL, consumer, NULL);
    for(int i=0;i<numP;i++)
        pthread_join(producers[i], NULL);
    for(int i=0;i<numC;i++)
        pthread_join(consumers[i], NULL);
    return 0;
}
*/

//P&C(T&M)
/*
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define SIZE 3

int buffer[SIZE];
int in=0, out=0;
int count=0;

pthread_mutex_t mutexLock;
pthread_cond_t notFull;
pthread_cond_t notEmpty;

void* producer(void* arg){
    while (true){
        int item = rand() % 100;
        sleep(rand() % 3);
        pthread_mutex_lock(&mutexLock);
        while (count == SIZE)
            pthread_cond_wait(&notFull, &mutexLock);
        buffer[in] = item;
        cout << "Producer produced " << item << " at " << in << endl;
        in=(in+1)%SIZE;
        count++;
        pthread_cond_signal(&notEmpty);
        pthread_mutex_unlock(&mutexLock);
    }
}

void* consumer(void* arg){
    while (true){
        sleep(rand() % 3);
        pthread_mutex_lock(&mutexLock);
        while (count == 0)
            pthread_cond_wait(&notEmpty, &mutexLock);
        int item = buffer[out];
        cout << "Consumer consumed " << item << " from " << out << endl;
        out=(out+1)%SIZE;
        count--;
        pthread_cond_signal(&notFull);
        pthread_mutex_unlock(&mutexLock);
    }
}

int main(){
    int numP=2, numC=3;
    pthread_t producers[numP], consumers[numC];
    pthread_mutex_init(&mutexLock,NULL);
    pthread_cond_init(&notFull,NULL);
    pthread_cond_init(&notEmpty,NULL);
    for(int i=0;i<numP;i++)
        pthread_create(&producers[i],NULL,producer,NULL);
    for(int i=0;i<numC;i++)
        pthread_create(&consumers[i],NULL,consumer,NULL);
    for(int i=0;i<numP;i++)
        pthread_join(producers[i],NULL);
    for(int i=0;i<numC;i++)
        pthread_join(consumers[i],NULL);
    return 0;
}
*/

//R&W(T&S)
/*
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
using namespace std;

#define READERS 3
#define WRITERS 1

int hh=23,mm=59,ss=55;
int readCount=0;

sem_t mutex;
sem_t writeLock;

void* reader(void* arg){
    int id = * (int*)arg;
    while (1){
        sem_wait(&mutex);
        readCount++;
        if (readCount == 0)
            sem_wait(&writeLock);
        sem_post(&mutex);
        printf("Reader %d reads time: %02d:%02d:%02d\n",id,hh,mm,ss);
        sem_wait(&mutex);
        readCount--;
        if (readCount == 1)
            sem_post(&writeLock);
        sem_post(&mutex);
        sleep(1);
    }
}

void* writer(void* arg){
    int id = * (int*)arg;
    while(1){
        sem_wait(&writeLock);
        ss++;
        if (ss==60) { ss=0; mm++; }
        if (mm==60) { mm=0; hh++; }
        if (hh==24) { hh=0; }
        printf("Writer %d updated time: %02d:%02d:%02d\n",id,hh,mm,ss);
        sem_post(&writeLock);
        sleep(1);
    }
}

int main() {
    pthread_t r[READERS], w[WRITERS];
    int rid[READERS], wid[WRITERS];
    sem_init(&mutex, 0, 1);
    sem_init(&writeLock, 0, 1);
    for (int i = 0; i < READERS; i++) {
        rid[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &rid[i]);
    }
    for (int i = 0; i < WRITERS; i++) {
        wid[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &wid[i]);
    }
    for (int i = 0; i < READERS; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < WRITERS; i++)
        pthread_join(w[i], NULL);
    return 0;
}
*/

//R&W(T&M)
/*
#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define READERS 3
#define WRITERS 1

int hh = 23, mm = 59, ss = 55;
int readCount = 0;
int isWriting = 0;

pthread_mutex_t mutex;
pthread_cond_t canRead;
pthread_cond_t canWrite;

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (isWriting)
            pthread_cond_wait(&canRead, &mutex);
        readCount++;
        pthread_mutex_unlock(&mutex);
        printf("Reader %d reads time: %02d:%02d:%02d\n", id, hh, mm, ss);
        pthread_mutex_lock(&mutex);
        readCount--;
        if (readCount == 0)
            pthread_cond_signal(&canWrite);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_mutex_lock(&mutex);
        while (readCount > 0 || isWriting)
            pthread_cond_wait(&canWrite, &mutex);
        isWriting = 1;
        pthread_mutex_unlock(&mutex);
        ss++;
        if (ss == 60) { ss = 0; mm++; }
        if (mm == 60) { mm = 0; hh++; }
        if (hh == 24) { hh = 0; }
        printf("Writer updated time: %02d:%02d:%02d\n", hh, mm, ss);
        pthread_mutex_lock(&mutex);
        isWriting = 0;
        pthread_cond_broadcast(&canRead);
        pthread_cond_signal(&canWrite);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main() {
    pthread_t r[READERS], w[WRITERS];
    int rid[READERS], wid[WRITERS];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&canRead, NULL);
    pthread_cond_init(&canWrite, NULL);
    for (int i = 0; i < READERS; i++) {
        rid[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &rid[i]);
    }
    for (int i = 0; i < WRITERS; i++) {
        wid[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &wid[i]);
    }
    for (int i = 0; i < READERS; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < WRITERS; i++)
        pthread_join(w[i], NULL);
    return 0;
}
*/

//FCFS
/*
#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int pid[n], at[n], bt[n], ft[n], tat[n], wt[n];
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i];
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(pid[i], pid[j]);
            }
        }
    }
    ft[0] = at[0] + bt[0];
    for (int i = 1; i < n; i++) {
        if (ft[i - 1] > at[i])
            ft[i] = ft[i - 1] + bt[i];
        else
            ft[i] = at[i] + bt[i];
    }
    for (int i = 0; i < n; i++) {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    cout << "\nPID\tAT\tBT\tFT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t"
             << bt[i] << "\t" << ft[i] << "\t"
             << tat[i] << "\t" << wt[i] << endl;
    }
    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < bt[i]; j++)
            cout << "-";
    }
    cout << "|\n ";
    for (int i = 0; i < n; i++) {
        cout << "|P" << pid[i];
        for (int j = 0; j < bt[i] - 2; j++)
            cout << " ";
    }
    cout << "|\n ";
    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < bt[i]; j++)
            cout << "-";
    }
    cout << "|\n";
    cout << at[0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[i]; j++)
            cout << " ";
        cout << ft[i];
    }
    return 0;
}
*/

//SJF(NP)
/*
#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int pid[n], at[n], bt[n], ft[n], tat[n], wt[n];
    bool done[n] = {0};
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i];
    }
    int time = 0, completed = 0;
    int order[n], idx = 0;
    while (completed < n) {
        int minBT = 1e9;
        int sel = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && bt[i] < minBT) {
                minBT = bt[i];
                sel = i;
            }
        }
        if (sel == -1) {
            time++;
            continue;
        }
        time += bt[sel];
        ft[sel] = time;
        done[sel] = true;
        order[idx++] = sel;
        completed++;
    }
    for (int i = 0; i < n; i++) {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    cout << "\nPID\tAT\tBT\tFT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t"
             << bt[i] << "\t" << ft[i] << "\t"
             << tat[i] << "\t" << wt[i] << endl;
    }
    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < bt[order[i]]; j++)
            cout << "-";
    }
    cout << "|\n ";
    for (int i = 0; i < n; i++) {
        cout << "|P" << pid[order[i]];
        for (int j = 0; j < bt[order[i]] - 2; j++)
            cout << " ";
    }
    cout << "|\n ";
    for (int i = 0; i < n; i++) {
        cout << "|";
        for (int j = 0; j < bt[order[i]]; j++)
            cout << "-";
    }
    cout << "|\n";
    cout << at[order[0]];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bt[order[i]]; j++)
            cout << " ";
        cout << ft[order[i]];
    }
    return 0;
}
*/

//SJF(P)
/*
#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int pid[n], at[n], bt[n], rt[n], ft[n], tat[n], wt[n];
    bool done[n] = {0};
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
        ft[i] = 0;
    }
    int time = 0, completed = 0;
    int gantt[1000], g = 0;
    while (completed < n) {
        int idx = -1;
        int minRT = 1e9;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < minRT) {
                minRT = rt[i];
                idx = i;
            }
        }
        if (idx == -1) {
            gantt[g++] = -1;
            time++;
            continue;
        }
        gantt[g++] = pid[idx];
        rt[idx]--;
        time++;
        if (rt[idx] == 0) {
            ft[idx] = time;
            completed++;
        }
    }
    for (int i = 0; i < n; i++) {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    cout << "\nPID\tAT\tBT\tFT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t"
             << bt[i] << "\t" << ft[i] << "\t"
             << tat[i] << "\t" << wt[i] << endl;
    }
    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < g; i++) cout << "|--";
    cout << "|\n ";
    for (int i = 0; i < g; i++) {
        if (gantt[i] == -1) cout << "|ID";
        else cout << "|P" << gantt[i];
    }
    cout << "|\n ";
    for (int i = 0; i < g; i++) cout << "|--";
    cout << "|\n 0";
    for (int i = 1; i <= g; i++) cout << "  " << i;
    return 0;
}
*/

//RR
/*
#include <iostream>
using namespace std;
int main() {
    int n, tq;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter Time Quantum: ";
    cin >> tq;
    int pid[n], at[n], bt[n], rt[n], ft[n];
    bool done[n] = {0};
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time and Burst Time for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i];
        rt[i] = bt[i];
        ft[i] = 0;
    }
    int time = 0, completed = 0;
    int ganttPid[200], ganttTime[200], g = 0;
    while (completed < n) {
        bool executed = false;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                executed = true;
                int exec = min(tq, rt[i]);
                ganttPid[g] = pid[i];
                ganttTime[g] = exec;
                g++;
                rt[i] -= exec;
                time += exec;
                if (rt[i] == 0) {
                    ft[i] = time;
                    completed++;
                }
            }
        }
        if (!executed) {
            time++;
        }
    }
    cout << "\nPID\tAT\tBT\tFT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        int tat = ft[i] - at[i];
        int wt = tat - bt[i];
        cout << "P" << pid[i] << "\t" << at[i] << "\t"
             << bt[i] << "\t" << ft[i] << "\t"
             << tat << "\t" << wt << endl;
    }
    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < g; i++) {
        cout << "|";
        for (int j = 0; j < ganttTime[i]; j++) cout << "--";
    }
    cout << "|\n ";
    for (int i = 0; i < g; i++) {
        cout << "|P" << ganttPid[i];
        for (int j = 0; j < ganttTime[i] - 1; j++) cout << " ";
    }
    cout << "|\n ";
    for (int i = 0; i < g; i++) {
        cout << "|";
        for (int j = 0; j < ganttTime[i]; j++) cout << "--";
    }
    cout << "|\n 0";
    int t = 0;
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < ganttTime[i]; j++) cout << "  ";
        t += ganttTime[i];
        cout << t;
    }
    return 0;
}
*/

//PRIO(NP)
/*
#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int pid[n], at[n], bt[n], pr[n], ft[n], tat[n], wt[n];
    bool done[n] = {0};
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time, Burst Time, Priority for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
        ft[i] = 0;
    }
    int time = 0, completed = 0;
    int ganttPid[n], ganttBt[n], g = 0;
    while (completed < n) {
        int idx = -1;
        int bestPr = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (pr[i] < bestPr) {
                    bestPr = pr[i];
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        ganttPid[g] = pid[idx];
        ganttBt[g] = bt[idx];
        g++;
        time += bt[idx];
        ft[idx] = time;
        done[idx] = true;
        completed++;
    }
    for (int i = 0; i < n; i++) {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    cout << "\nPID\tAT\tBT\tPR\tFT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t"
             << bt[i] << "\t" << pr[i] << "\t"
             << ft[i] << "\t" << tat[i] << "\t"
             << wt[i] << endl;
    }
    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < g; i++) {
        cout << "|";
        for (int j = 0; j < ganttBt[i]; j++) cout << "-";
    }
    cout << "|\n ";
    for (int i = 0; i < g; i++) {
        cout << "|P" << ganttPid[i];
        for (int j = 0; j < ganttBt[i] - 2; j++) cout << " ";
    }
    cout << "|\n ";
    for (int i = 0; i < g; i++) {
        cout << "|";
        for (int j = 0; j < ganttBt[i]; j++) cout << "-";
    }
    cout << "|\n 0";
    int t = 0;
    for (int i = 0; i < g; i++) {
        for (int j = 0; j < ganttBt[i]; j++) cout << " ";
        t += ganttBt[i];
        cout << t;
    }
    return 0;
}
*/

//PRIO(P)
/*
#include <iostream>
using namespace std;
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    int pid[n], at[n], bt[n], pr[n], rt[n], ft[n], tat[n], wt[n];
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "Enter Arrival Time, Burst Time, Priority for P" << pid[i] << ": ";
        cin >> at[i] >> bt[i] >> pr[i];
        rt[i] = bt[i];
        ft[i] = 0;
    }
    int time = 0, completed = 0;
    int ganttPID[1000], g = 0;
    while (completed < n) {
        int idx = -1;
        int bestPr = 1e9;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (pr[i] < bestPr) {
                    bestPr = pr[i];
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            ganttPID[g++] = -1;
            time++;
            continue;
        }
        ganttPID[g++] = pid[idx];
        rt[idx]--;
        time++;
        if (rt[idx] == 0) {
            ft[idx] = time;
            completed++;
        }
    }
    for (int i = 0; i < n; i++) {
        tat[i] = ft[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }
    cout << "\nPID\tAT\tBT\tPR\tFT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at[i] << "\t"
             << bt[i] << "\t" << pr[i] << "\t"
             << ft[i] << "\t" << tat[i] << "\t"
             << wt[i] << endl;
    }
    cout << "\nGantt Chart:\n ";
    for (int i = 0; i < g; i++) cout << "|--";
    cout << "|\n ";
    for (int i = 0; i < g; i++) {
        if (ganttPID[i] == -1) cout << "|ID";
        else cout << "|P" << ganttPID[i];
    }
    cout << "|\n ";
    for (int i = 0; i < g; i++) cout << "|--";
    cout << "|\n 0";
    for (int i = 1; i <= g; i++) cout << "  " << i;
    return 0;
}
*/

//BANK(V1)
/*
#include <iostream>
using namespace std;
int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;
    int existing[m], alloc[n][m], need[n][m];
    int avail[m];
    cout << "Enter Existing Resources:\n";
    for (int j = 0; j < m; j++)
        cin >> existing[j];
    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];
    cout << "Enter Need Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> need[i][j];
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++)
            sum += alloc[i][j];
        avail[j] = existing[j] - sum;
    }
    bool finish[n] = {false};
    int safeSeq[n], count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }
    if (count == n) {
        cout << "\nSystem is SAFE\nSafe Sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << " ";
    } else {
        cout << "\nSystem is NOT SAFE";
    }
    return 0;
}
*/

//BANK(V2)
/*
#include <iostream>
using namespace std;
int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;
    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];
    cout << "Enter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];
    cout << "Enter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];
    cout << "Enter Available Resources:\n";
    for (int j = 0; j < m; j++)
        cin >> avail[j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    bool finish[n] = {false};
    int safeSeq[n], count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }
    if (count == n) {
        cout << "\nSystem is SAFE\nSafe Sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << " ";
    } else {
        cout << "\nSystem is NOT SAFE";
    }
    return 0;
}
*/

//LRU
/*
#include <iostream>
using namespace std;
int main() {
    int n, f;
    cout << "Enter number of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++)
        cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> f;
    int frames[f], table[f][n], time[f];
    char result[n];
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }
    int t = 0;
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = true;
                time[j] = ++t;
                break;
            }
        }
        if (hit) {
            result[i] = 'H';
        } else {
            int lru = 0;
            for (int j = 1; j < f; j++)
                if (time[j] < time[lru])
                    lru = j;
            frames[lru] = pages[i];
            time[lru] = ++t;
            result[i] = 'P';
        }
        for (int j = 0; j < f; j++)
            table[j][i] = frames[j];
    }
    cout << "\nPages : ";
    for (int i = 0; i < n; i++) cout << pages[i] << " ";
    cout << endl;
    for (int i = 0; i < f; i++) {
        cout << "F" << i + 1 << "    : ";
        for (int j = 0; j < n; j++) {
            if (table[i][j] == -1) cout << "- ";
            else cout << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Result: ";
    for (int i = 0; i < n; i++) cout << result[i] << " ";
    return 0;
}
*/

//FIFO
/*
#include <iostream>
using namespace std;
int main() {
    int n, f;
    cout << "Enter number of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++)
        cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> f;
    int frames[f], table[f][n];
    char result[n];
    for (int i = 0; i < f; i++) frames[i] = -1;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = true;
                break;
            }
        }
        if (hit) {
            result[i] = 'H';
        } else {
            frames[idx] = pages[i];
            idx = (idx + 1) % f;
            result[i] = 'P';
        }
        for (int j = 0; j < f; j++)
            table[j][i] = frames[j];
    }
    cout << "\nPages : ";
    for (int i = 0; i < n; i++) cout << pages[i] << " ";
    cout << endl;
    for (int i = 0; i < f; i++) {
        cout << "F" << i + 1 << "    : ";
        for (int j = 0; j < n; j++) {
            if (table[i][j] == -1) cout << "- ";
            else cout << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Result: ";
    for (int i = 0; i < n; i++) cout << result[i] << " ";
    return 0;
}
*/

//OPT
/*
#include <iostream>
using namespace std;
int main() {
    int n, f;
    cout << "Enter number of pages: ";
    cin >> n;
    int pages[n];
    cout << "Enter page reference string:\n";
    for (int i = 0; i < n; i++)
        cin >> pages[i];
    cout << "Enter number of frames: ";
    cin >> f;
    int frames[f], table[f][n];
    char result[n];
    for (int i = 0; i < f; i++) frames[i] = -1;
    for (int i = 0; i < n; i++) {
        bool hit = false;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = true;
                break;
            }
        }
        if (hit) {
            result[i] = 'H';
        } else {
            int idx = -1, farthest = i + 1;
            for (int j = 0; j < f; j++) {
                int k;
                for (k = i + 1; k < n; k++)
                    if (frames[j] == pages[k]) break;
                if (k == n) {
                    idx = j;
                    break;
                }
                if (k > farthest) {
                    farthest = k;
                    idx = j;
                }
            }
            if (idx == -1) idx = 0;
            frames[idx] = pages[i];
            result[i] = 'P';
        }
        for (int j = 0; j < f; j++)
            table[j][i] = frames[j];
    }
    cout << "\nPages : ";
    for (int i = 0; i < n; i++) cout << pages[i] << " ";
    cout << endl;
    for (int i = 0; i < f; i++) {
        cout << "F" << i + 1 << "    : ";
        for (int j = 0; j < n; j++) {
            if (table[i][j] == -1) cout << "- ";
            else cout << table[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Result: ";
    for (int i = 0; i < n; i++) cout << result[i] << " ";
    return 0;
}
*/

//EDF
/*
#include <iostream>
using namespace std;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
int main() {
    int n;
    cout << "Enter number of tasks: ";
    cin >> n;
    int pid[n], bt[n], period[n], deadline[n];
    int rem[n], next[n], absDL[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Burst, Period, Deadline: ";
        cin >> pid[i] >> bt[i] >> period[i] >> deadline[i];
        rem[i] = 0;
        next[i] = 0;
        absDL[i] = 0;
    }
    int hyper = period[0];
    for (int i = 1; i < n; i++)
        hyper = lcm(hyper, period[i]);
    cout << "\nTime\tTask\n";
    for (int t = 0; t < hyper; t++) {
        for (int i = 0; i < n; i++) {
            if (t == next[i]) {
                rem[i] = bt[i];
                absDL[i] = t + deadline[i];
                next[i] += period[i];
            }
        }
        int sel = -1;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                if (sel == -1 || absDL[i] < absDL[sel])
                    sel = i;
            }
        }
        if (sel == -1)
            cout << t << "\tIDLE\n";
        else {
            cout << t << "\tT" << pid[sel] << "\n";
            rem[sel]--;
        }
    }
    return 0;
}
*/

//RMS
/*
#include <iostream>
using namespace std;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
int main() {
    int n;
    cout << "Enter number of tasks: ";
    cin >> n;
    int pid[n], bt[n], period[n], rem[n], next[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Burst, Period: ";
        cin >> pid[i] >> bt[i] >> period[i];
        rem[i] = 0;
        next[i] = 0;
    }
    int hyper = period[0];
    for (int i = 1; i < n; i++)
        hyper = lcm(hyper, period[i]);
    cout << "\nTime\tTask\n";
    for (int t = 0; t < hyper; t++) {
        for (int i = 0; i < n; i++) {
            if (t == next[i]) {
                rem[i] = bt[i];
                next[i] += period[i];
            }
        }
        int sel = -1;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                if (sel == -1 || period[i] < period[sel])
                    sel = i;
            }
        }
        if (sel == -1)
            cout << t << "\tIDLE\n";
        else {
            cout << t << "\tT" << pid[sel] << "\n";
            rem[sel]--;
        }
    }
    return 0;
}
*/

//LLF
/*
#include <iostream>
using namespace std;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}
int main() {
    int n;
    cout << "Enter number of tasks: ";
    cin >> n;
    int pid[n], bt[n], period[n], deadline[n];
    int rem[n], next[n], absDL[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter PID, Burst, Period, Deadline: ";
        cin >> pid[i] >> bt[i] >> period[i] >> deadline[i];
        rem[i] = 0;
        next[i] = 0;
        absDL[i] = 0;
    }
    int hyper = period[0];
    for (int i = 1; i < n; i++)
        hyper = lcm(hyper, period[i]);
    cout << "\nTime\tTask\n";
    for (int t = 0; t < hyper; t++) {
        for (int i = 0; i < n; i++) {
            if (t == next[i]) {
                rem[i] = bt[i];
                absDL[i] = t + deadline[i];
                next[i] += period[i];
            }
        }
        int sel = -1;
        int minLax = 1e9;
        for (int i = 0; i < n; i++) {
            if (rem[i] > 0) {
                int laxity = absDL[i] - rem[i] - t;
                if (laxity < minLax) {
                    minLax = laxity;
                    sel = i;
                }
            }
        }
        if (sel == -1)
            cout << t << "\tIDLE\n";
        else {
            cout << t << "\tT" << pid[sel] << "\n";
            rem[sel]--;
        }
    }
    return 0;
}
*/
