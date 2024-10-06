#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "forky.h"

void forky_parallel(int num_processes) {
    srand(time(NULL));
    pid_t pids[num_processes];

    for (int i = 0; i < num_processes; ++i) {
        pids[i] = fork();  // Fork a new process

        if (pids[i] < 0) {  // Fork failed
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0) {  // Child process
            printf("Process %d (PID %d) beginning\n", i + 1, getpid());
            sleep(1 + (rand() % 8));  // Simulate work with random sleep
            printf("Process %d (PID %d) exiting\n", i + 1, getpid());
            exit(EXIT_SUCCESS);  // Exit child process
        }
    }

    // Parent waits for all child processes to finish
    for (int i = 0; i < num_processes; ++i) {
        waitpid(pids[i], 0, 0);
    }
}

void forky_sequential(int num_processes) {
    srand(time(NULL));
    pid_t pid;

    for (int i = 0; i < num_processes; ++i) {
        pid = fork();  // Fork a new process

        if (pid == 0) {  // Child process
            printf("Process %d (PID %d) creating Process %d\n", i, getppid(), i + 1);
            printf("Process %d (PID %d) beginning\n", i + 1, getpid());
            sleep(1 + (rand() % 8));  // Simulate work with random sleep
        } else if (pid > 0) {  // Parent process
            waitpid(pid, 0, 0);  // Wait for child to finish before proceeding
            printf("Process %d (PID %d) exiting\n", i, getpid());
            break;  // Exit parent to prevent further forks
        } else {  // Fork failed
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
    }

    // The last child process exits
    if (pid == 0) {
        printf("Process %d (PID %d) exiting\n", num_processes, getpid());
        exit(EXIT_SUCCESS);
    }
}
