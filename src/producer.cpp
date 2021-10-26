/*
    Derron Ward
    Producer Process
    10/19/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <iostream>

int main() {

    srand(time(nullptr));

    // Allocate the shared memory
    int tbl = shm_open("table", O_CREAT | O_RDWR, 0666);
    if (tbl == -1) {
        std::cerr << "shm_open() error, exiting." << std::endl;
        exit(1);
    }

    if (ftruncate(tbl, sizeof(int)) == -1) {
        std::cerr << "ftruncate() error, exiting." << std::endl;
        exit(1);
    }

    int *table = static_cast<int *>(mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tbl, 0));
    if (table == MAP_FAILED) {
        std::cerr << "mmap() error, exiting." << std::endl;
        exit(1);
    }

    // Allocate the semaphore used for mutual exclusion
    sem_t *mutex = sem_open("mutex", O_CREAT, 0666, 1);
    if (mutex == SEM_FAILED) {
        std::cerr << "sem_open() error, exiting." << std::endl;
        exit(1);
    }

    int loop = 10;
    std::cout << "Producer ready to create " << loop << " items." << std::endl;

    for (int i = 0; i < loop; ++i) {

        // Check if the table if full every second until
        // there is an open space
        bool fullMsg = false;
        while (*table == 2){
            if (!fullMsg) {
                std::cout << "==== TABLE FULL - PRODUCER WAITING ====" << std::endl;
                fullMsg = true;
            }
            sleep(1);
        }

        // Produce the item
        int wait = rand() % 5 + 1;
        sleep(wait);

        // Increment the number of items on the table
        sem_wait(mutex);
        ++(*table);
        sem_post(mutex);

        std::cout << "Item produced in " << wait << " seconds, there are now " << *table << " item(s) on the table." << std::endl;
    }

    // Close and unlink the mutal exclusion semaphore
    sem_close(mutex);
    sem_unlink("mutex");

    // Deallocate the shared memry
    munmap(table, sizeof(int));
    close(tbl);
    shm_unlink("table");

    std::cout << "Producer cleaned up!" << std::endl;
}