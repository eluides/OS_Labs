#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <signal.h>

volatile sig_atomic_t g_stop = 0;

void* printRandomNumber(void* arg) {
    int delay = *((int*)arg);

    while (!g_stop) {
        double randomValue = (double)rand() / RAND_MAX;
        std::cout << "Случайное число: " << randomValue << std::endl;
    }

    return NULL;
}


void sigintHandler(int signum) {
    std::cout << "Процесс получил сигнал SIGINT. Завершение работы..." << std::endl;
    g_stop = 1;
}

int main() {
    signal(SIGINT, sigintHandler);
    srand(time(NULL));
    pthread_t thread;
    int delaySeconds = 2; 

    if (pthread_create(&thread, NULL, printRandomNumber, &delaySeconds) != 0) {
        std::cerr << "Ошибка создания потока." << std::endl;
        return 1;
    }

    std::string input;
    while (!g_stop) {
        std::cin >> input;
        std::string invertedInput(input.rbegin(), input.rend());
        std::cout << "Инвертированная строка: " << invertedInput << std::endl;
    }

    pthread_join(thread, NULL);

    return 0;
}
