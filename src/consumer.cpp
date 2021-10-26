/*
    Derron Ward
    Consumer Process
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
    int shm_fd = shm_open("table", O_RDWR, 0666);

    int *table = static_cast<int *>(mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));

    // Allocate the semaphore used for mutual exclusion
    sem_t *mutex = sem_open("mutex", O_CREAT, 0666, 1);

    int loop = 10;
    std::cout << "Consumer ready to receive " << loop << " items." << std::endl;

    for (int i = 0; i < loop; ++i) {

        // Check if the table if empty every second until
        // there is an open space
        bool emptyMsg = false;
        while (*table == 0) {
            if (!emptyMsg) {
                std::cout << "==== TABLE EMPTY - CONSUMER WAITING ====" << std::endl;
                emptyMsg = true;
            }
            sleep(1);
        }

        // Consume an item
        int wait = rand() % 5 + 1;
        sleep(wait);

        // Decrement the number of items on the table
        sem_wait(mutex);
        --(*table);
        sem_post(mutex);

        std::cout << "Item consumed in " << wait << " seconds, there are now " << *table << " item(s) in the table." << std::endl;
    }

    // Close and unlink the mutal exclusion semaphore
    sem_close(mutex);
    sem_unlink("mutex");

    // Deallocate the shared memory
    munmap(table, sizeof(int));
    close(shm_fd);
    shm_unlink("table");

    std::cout << "Consumer cleaned up!" << std::endl;
}