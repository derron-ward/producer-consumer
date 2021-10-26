# Producer Consumer

This project provides a solution to the Producer-Consumer Problem

### The Problem
The producer generates items and puts them onto the table. The consumer will pick up the items. The table can only hold 2 items at the same time. When the table if full, the producer will wait. When the table is empty, the consumer will wait. We use semaphores to synchronize producer and consumer. Mutual exclusion should be considered. we use pthreads in producer and consumer programs. Shared memory is used for "table".

# Getting Started

### Prerequisites
* gcc - the following command will installs multiple packages including ```gcc```, ```g++``` and ```make```
```bash
sudo apt install build-essential
```
* pthread library

### Installation
Clone the repository using [git](https://git-scm.com/downloads)
```bash
git clone https://github.com/derron-ward/producer-consumer.git
```
Or download the zip from [github](https://github.com/derron-ward/producer-consumer)
<p align="right"><a href="#top">Back to top</a></p>

# Usage

### Compiling and Running
There are 2 ways to compile and run the project:
1. Using the provided Makefile
    Compile the programs
    ```bash
    make producer
    make consumer
    ```
    Run the programs
    ```bash
    make run
    ```
    Exit the programs with ```ctrl+c```

    Remove executable files when done
    ```bash
    make clean
    ```
2. Manually inputing the commands in the terminal
    Compile the programs
    ```bash
    gcc producer.cpp -pthread -lrt -lstdc++ -o producer.o
    gcc consumer.cpp -pthread -lrt -lstdc++ -o consumer.o
    ```
    Run the programs
    ```bash
    ./producer.o & ./consumer.o &
    ```
    Exit the programs with ```ctrl+c```

    Remove executable files when done
    ```
    rm *.o
    ```

### Output
Sample output:
```bash
user@example:~/producer-consumer/src$ make producer
gcc producer.cpp -pthread -lrt -lstdc++ -o producer.o
user@example:~/producer-consumer/src$ make consumer
gcc consumer.cpp -pthread -lrt -lstdc++ -o consumer.o
user@example:~/producer-consumer/src$ make run
./producer.o & ./consumer.o &
Producer ready to create 10 items.
Consumer ready to receive 10 items.
==== TABLE EMPTY - CONSUMER WAITING ====
Item produced in 1 seconds, there are now 1 item(s) on the table.
Item produced in 1 seconds, there are now 2 item(s) on the table.
==== TABLE FULL - PRODUCER WAITING ====
Item consumed in 1 seconds, there are now 1 item(s) in the table.
Item consumed in 1 seconds, there are now 0 item(s) in the table.
==== TABLE EMPTY - CONSUMER WAITING ====
Item produced in 1 seconds, there are now 1 item(s) on the table.
Item consumed in 1 seconds, there are now 0 item(s) in the table.
==== TABLE EMPTY - CONSUMER WAITING ====
Item produced in 3 seconds, there are now 1 item(s) on the table.
Item produced in 3 seconds, there are now 2 item(s) on the table.
==== TABLE FULL - PRODUCER WAITING ====
Item consumed in 3 seconds, there are now 1 item(s) in the table.
Item consumed in 3 seconds, there are now 0 item(s) in the table.
==== TABLE EMPTY - CONSUMER WAITING ====
Item produced in 3 seconds, there are now 1 item(s) on the table.
Item consumed in 3 seconds, there are now 0 item(s) in the table.
==== TABLE EMPTY - CONSUMER WAITING ====
Item produced in 4 seconds, there are now 1 item(s) on the table.
Item produced in 1 seconds, there are now 2 item(s) on the table.
==== TABLE FULL - PRODUCER WAITING ====
Item consumed in 4 seconds, there are now 1 item(s) in the table.
Item consumed in 1 seconds, there are now 0 item(s) in the table.
==== TABLE EMPTY - CONSUMER WAITING ====
Item produced in 5 seconds, there are now 1 item(s) on the table.
Item produced in 3 seconds, there are now 2 item(s) on the table.
Producer cleaned up!
Item consumed in 5 seconds, there are now 1 item(s) in the table.
Item consumed in 3 seconds, there are now 0 item(s) in the table.
Consumer cleaned up!
^C
make clean
```
<p align="right"><a href="#top">Back to top</a></p>
