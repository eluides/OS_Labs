#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createAndWaitProcess() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("������ fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        printf("�������� ������� ������� ������� � ���������� ������...\n");
        while (1) {
            sleep(1); // ����� �� 1 �������
        }

        exit(EXIT_SUCCESS);
    }
    else {
        int status;
        pid_t childPid = waitpid(pid, &status, 0);

        if (childPid == -1) {
            perror("������ �������� ���������� ��������� ��������");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("�������� ������� ���������� � �����: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("�������� ������� ���������� ��-�� �������: %d\n", WTERMSIG(status));
        }
        exit(EXIT_SUCCESS);
    }
}

int main() {
    createAndWaitProcess();
    return 0;
}
