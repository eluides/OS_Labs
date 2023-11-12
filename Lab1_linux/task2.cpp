#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <string>
#include <signal.h>

pthread_t randomThread, inputThread;
pthread_mutex_t mutex;
bool isRunning = true;

void* randomNumberWriter(void* arg) {
    while (isRunning) {
        double randomValue = (double)rand() / RAND_MAX;
        pthread_mutex_lock(&mutex);
        std::cout << "Случайное число: " << randomValue << std::endl;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* inputAndReverseThread(void* arg) {
    while (isRunning) {
        std::string input;
        std::getline(std::cin, input);
        pthread_mutex_lock(&mutex);
        std::reverse(input.begin(), input.end());
        std::cout << "Инвертированная строка: " << input << std::endl;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void sigintHandler(int signum) {
    pthread_mutex_lock(&mutex);
    std::cout << "Получен сигнал SIGINT. Завершение работы." << std::endl;
    isRunning = false;
    pthread_mutex_unlock(&mutex);
}

int main() {
    srand(time(NULL));
    signal(SIGINT, sigintHandler);

    pthread_mutex_init(&mutex, NULL);

    int result = pthread_create(&randomThread, NULL, randomNumberWriter, NULL);
    if (result != 0) {
        std::cerr << "Ошибка при создании потока для случайных чисел: " << strerror(result) << std::endl;
        return 1;
    }

    result = pthread_create(&inputThread, NULL, inputAndReverseThread, NULL);
    if (result != 0) {
        std::cerr << "Ошибка при создании потока для ввода и инвертирования: " << strerror(result) << std::endl;
        return 1;
    }

    pthread_join(randomThread, NULL);
    pthread_join(inputThread, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
