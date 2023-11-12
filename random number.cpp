#include <iostream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>
#include <unistd.h>

void* randomNumberWriter(void* arg) {
    while (true) {
        double randomValue = (double)rand() / RAND_MAX;
        std::cout << "Случайное число: " << randomValue << std::endl;
        usleep(500000); 
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t thread;
    int result = pthread_create(&thread, NULL, randomNumberWriter, NULL);

    if (result != 0) {
        std::cerr << "Ошибка при создании потока: " << strerror(result) << std::endl;
        return 1;
    }
    pthread_join(thread, NULL);

    return 0;
}
