#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createAndWaitProcess() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Ошибка fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("Дочерний процесс ожидает сигнала о завершении работы...\n");
        while (1) {
            sleep(1); // Пауза на 1 секунду
        }

        exit(EXIT_SUCCESS);
    }
    else {
        int status;
        pid_t childPid = waitpid(pid, &status, 0);

        if (childPid == -1) {
            perror("Ошибка ожидания завершения дочернего процесса");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Дочерний процесс завершился с кодом: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("Дочерний процесс завершился из-за сигнала: %d\n", WTERMSIG(status));
        }
        exit(EXIT_SUCCESS);
    }
}

int main() {
    createAndWaitProcess();
    return 0;
}
