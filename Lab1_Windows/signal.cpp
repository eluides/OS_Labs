#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signal) {
    printf("������� ������� ������: %d\n", signal);
    exit(0);
}

int main() {
    setlocale(LC_ALL, "Russian");
    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        perror("������ ��������� ����������� �������");
        return 1;
    }

    printf("��������� ������� ������� � ���������� ������...\n");

    while (1) {
        sleep(1); 
    }

    return 0;
}
