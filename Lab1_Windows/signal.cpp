#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signal) {
    printf("Процесс получил сигнал: %d\n", signal);
    exit(0);
}

int main() {
    setlocale(LC_ALL, "Russian");
    if (signal(SIGINT, signalHandler) == SIG_ERR) {
        perror("Ошибка установки обработчика сигнала");
        return 1;
    }

    printf("Программа ожидает сигнала о завершении работы...\n");

    while (1) {
        sleep(1); 
    }

    return 0;
}
