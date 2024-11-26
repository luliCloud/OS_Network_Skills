#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h> // getopt
#include <string.h>
#include <fcntl.h> // handle the file opened, set file descriptor, permission, status...
#include <sys/mman.h> // mem mapping
#include <sys/socket.h>
#include <sys/un.h>
#include <bits/getopt_core.h> // getopt_core.h 
#include <sys/select.h> // for select()timing out

// define the dir for socket path and shared memory
#define SOCKET_DIR "/tmp/socket" 
#define SHARED_MEM_DIR "/shared_mem" // should be in mem, not file path. can only start with /. not child dir
#define SHARED_MEM_SIZE 1024

// global var for semaphore
/** sem_mutex: ensure only producer or consumer write in the critical section
sem_full and sem_empty: not corresponding to producer and consumer respectively
producer: wait for sem_empty, when write to the queue with queue depth, signal full
consumer: wait for sem_full, when consume all message, signal sem_empty
 */
sem_t *sem_empty, *sem_full, *sem_mutex; // noting need to link to -pthread when compile

// prototype for producer function (unix socket). verbose indicate we should print msg
void producer_socket(const char *msg, int queue_depth, int verbose);

// prtotype for consumer func (unix socket)
void consumer_socket(int verbose);

// protoytpe for producer function (shared mem)
void producer_shared_mem(const char *msg, int queue_depth, int verbose);

// prtotype for consumer func (shared mem)
void consumer_shared_mem(int verbose);

int main(int argc, char** argv) {
    int is_producer = -1; // not producer: 0
    int verbose = 0;
    int queue_depth = 0;
    char *msg = NULL;
    int use_unix_socket = 0; // not use
    int opt;
    // read arg using getopt (<unistd.h>)
    /** getopt scan all param. if found any start with -, like -p, return its ASCII
     * if the param include a 2nd val, like -m msg, getopt store 2nd val in optarg
     */
    while ((opt = getopt(argc, argv, "pcm:q:use")) != -1) {
        switch (opt) {
            case 'p': is_producer = 1; break;
            case 'c': is_producer = 0; break;
            case 'm': msg = optarg; break;
            case 'q': queue_depth = atoi(optarg); break;
            case 'u': use_unix_socket = 1; break;
            case 's': use_unix_socket = 0; break;
            case 'e': verbose = 1; break;
            default: 
                fprintf(stderr, "Usage: %s -p|-c -m message -q queue_depth -u|-s -e\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // conflict check
    if (is_producer == -1) {
        fprintf(stderr, "please indicate producer or consumer\n");
        exit(EXIT_FAILURE);
    }

    if (is_producer == 1 && msg == NULL) {
        fprintf(stderr, "-p requires -m a message.\n");
        exit(EXIT_FAILURE);
    }

    if (is_producer == 1 && queue_depth <= 0) { // to do, check whether only producer need queue_dep
        fprintf(stderr, "-q requires a positive integer value\n");
        exit(EXIT_FAILURE);
    }

    if (is_producer == 0 && msg != NULL) {
        fprintf(stderr, "-c cannot be used with -m [message].\n");
        exit(EXIT_FAILURE);
    }

    if (is_producer) {
        // initialize sem_mutex, sem_full, sem_empty. should only put in producer mode. not in consumer, otherwise clean these var
        sem_unlink("/sem_empty");
        sem_unlink("/sem_full");
        sem_unlink("/sem_mutex");

        sem_empty = sem_open("/sem_empty", O_CREAT, 0666, queue_depth);
        sem_full = sem_open("/sem_full", O_CREAT, 0666, 0); // start from 0, when val == queue_depth, signal full
        sem_mutex = sem_open("/sem_mutex", O_CREAT, 0666, 1);
    } else { // consumer only open the var, not create it 
        sem_empty = sem_open("/sem_empty", 0); 
        sem_full = sem_open("/sem_full", 0);
        sem_mutex = sem_open("/sem_mutex", 0);
    }
    

    if (sem_empty == SEM_FAILED || sem_full == SEM_FAILED || sem_mutex == SEM_FAILED) {
        perror("Semaphore initialization failed.");
        exit(EXIT_FAILURE);
    }

    // int empty_val, full_val, mutex_val;
    // sem_getvalue(sem_empty, &empty_val);
    // sem_getvalue(sem_full, &full_val);
    // sem_getvalue(sem_mutex, &mutex_val);
    // printf("sem_empty: %d, sem_full: %d, sem_mutex: %d\n", empty_val, full_val, mutex_val);

    if (is_producer) {
        if (use_unix_socket) {
            producer_socket(msg, queue_depth, verbose);
        } else {
            producer_shared_mem(msg, queue_depth, verbose);
        }
    } else {
        if (use_unix_socket) {
            consumer_socket(verbose);
        } else {
            consumer_shared_mem(verbose);
        }
    }

    // close semaphores
    sem_close(sem_mutex);
    sem_close(sem_full);
    sem_close(sem_empty);
    sem_unlink("/sem_mutex");
    sem_unlink("/sem_full");
    sem_unlink("/sem_empty");

    return 0;
}

// prototype for producer function (unix socket). verbose indicate we should print msg
void producer_socket(const char *msg, int queue_depth, int verbose) {
    unlink(SOCKET_DIR); // delete left socket file
    // socket descriptor, similar to file descriptor. all socket related op need it.
    int server_fd, client_fd;

    // a struct in UNIX SOCKET to maintain all info about this socket, defined in un.h
    struct sockaddr_un server_addr;
    // create socket: AF indicate is a socket cluster. for local IPC (same machine)
    // sock_stream, stream of socket, similar to TCP, order, reliable, connected
    // 0 protocol param. if connect success, return non-neg int
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Unsseccesful socket creation in producer end.");
        exit(EXIT_FAILURE);
    }
    // configure server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    // copy string. copy path of socket (not content) to sun_path of server_addr
    // -1 ensure that the SOCKET_DIR not exceed the maximum size of sun_path. -1 is 
    // left for \0
    strncpy(server_addr.sun_path, SOCKET_DIR, sizeof(server_addr.sun_path) - 1);

    // find the socket
    unlink(SOCKET_DIR); // remove existing socket (maybe another address)
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Cannot bind to socket.");
        exit(EXIT_FAILURE);
    }

    // listen with a queue depth
    if (listen(server_fd, queue_depth) == -1) {
        perror("Cannot listen via socket.");
        exit(EXIT_FAILURE);
    }

    printf("Socket is created, bound, and listened by producer. Waiting for the next consumer.\n");

    struct timeval timeout;
    timeout.tv_sec = 10; // time out time is 2 sec
    timeout.tv_usec = 0;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(server_fd, &fds);

    // waiting for connect
    int ret = select(server_fd + 1, &fds, NULL, NULL, &timeout);
    if (ret == -1) {
        perror("Select failed");
        exit(EXIT_FAILURE);
    } else if (ret == 0) {
        fprintf(stderr, "No consumer connect within timeout.\n");
        close(server_fd);
        unlink(SOCKET_DIR);
        exit(EXIT_FAILURE);
    }

    // accept consumer connection
    if ((client_fd = accept(server_fd, NULL, NULL)) == -1) {
        perror("Cannot accept customer via socket.");
        exit(EXIT_FAILURE);
    }
    printf("Consumer connected successfully!\n");

    // produce message
    while (1) {
        sem_wait(sem_empty);
        sem_wait(sem_mutex);

        if (verbose) {
            printf("Message produced by producer: %s\n", msg);
            fflush(stdout); 
        }
        ssize_t bytes_written = write(client_fd, msg, strlen(msg) + 1);
        if (bytes_written == -1) {
            perror("Producer: Write to socket failed");
        } 
        fsync(client_fd);

        sem_post(sem_mutex);
        sem_post(sem_full);

        sleep(1);
    }
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_DIR);
}

// prtotype for consumer func (unix socket)
void consumer_socket(int verbose) {
    int client_fd;
    struct sockaddr_un server_addr;
    char buffer[1024];
    int queue_depth;
    sem_getvalue(sem_empty, &queue_depth); 

    // create socket
    if ((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("Socket created failed in consumer end.");
        exit(EXIT_FAILURE);
    }

    // configure server addr
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_DIR, sizeof(server_addr.sun_path) - 1);

    // connect to the producer
    int count = 5;
    while (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connect failed from consumer end.");
        sleep(1);
        count--;
    }
    printf("Consumer connected to producer successfully!\n");

    if (count == 0) {
        fprintf(stderr, "Failed to connect to producer");
        exit(EXIT_FAILURE);
    }
    while (1) {
        sem_wait(sem_full);
        sem_wait(sem_mutex);

        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0';
            if (verbose) {
                printf("Consumed: %s\n", buffer);
            } 
        } else {
            perror("Read failed");
        }

        sem_post(sem_mutex);
        sem_post(sem_empty);
    }
    close(client_fd);
}

// protoytpe for producer function (shared mem)
void producer_shared_mem(const char *msg, int queue_depth, int verbose) {
    int shm_fd;
    char* shared_mem;

    // create shared meme
    // success: return a file descriptor, failed return -1 and set errono
    shm_fd = shm_open(SHARED_MEM_DIR, O_CREAT | O_RDWR, 0666); // oepn as read/write mode
    if (shm_fd == -1) {
        perror("Shared mnemory creation failed in producer end.");
        exit(EXIT_FAILURE);
    }

    // configure shared memory size
    ftruncate(shm_fd, SHARED_MEM_SIZE);

    // map shared memory
    shared_mem = mmap(0, SHARED_MEM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("Map failed in producer end.");
        exit(EXIT_FAILURE);
    }

    while (1) {
        sem_wait(sem_empty);
        sem_wait(sem_mutex);

        strncpy(shared_mem, msg, SHARED_MEM_SIZE);
        if (verbose) {
            printf("Producing: %s\n", msg);
        }

        sem_post(sem_full);
        sem_post(sem_mutex);

        sleep(1);
    }

    munmap(shared_mem, SHARED_MEM_SIZE);
    shm_unlink(SHARED_MEM_DIR);
}

// prtotype for consumer func (shared mem)
void consumer_shared_mem(int verbose) {
    int shm_fd;
    char* shared_mem;

    int queue_depth;
    sem_getvalue(sem_empty, &queue_depth); 

    shm_fd = shm_open(SHARED_MEM_DIR, O_RDONLY, 0666);
    if (shm_fd == -1) {
        perror("Shared memory open failed from consumer end.");
        exit(EXIT_FAILURE);
    }

    shared_mem = mmap(0, SHARED_MEM_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("Shared memory mapping failed.");
        exit(EXIT_FAILURE);
    }

    while (1) {
        sem_wait(sem_full);
        sem_wait(sem_mutex);

        if (verbose) {
            printf("Consumming: %s\n", shared_mem);
        }
        sem_post(sem_mutex);
        sem_post(sem_empty);
        sleep(1);
    }

    munmap(shared_mem, SHARED_MEM_SIZE);
    close(shm_fd);
}

/**
 * compilation:
 * gcc producer-consumer.c -o producer-consumer -lrt -pthread
 * 
 * test
 * 
 * to ensure shared mem be created, we must run producer first.
 * for UNIX socket
 * ./producer-consumer -p -m "Hello" -q 5 -u -e
 * ./producer-consumer -c -u -e
 * 
 * for shared mem
 * ./producer-consumer -p -m "Hello" -q 5 -s -e
 * ./producer-consumer -c -s -e
 */