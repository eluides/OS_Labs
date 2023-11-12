#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <signal.h>

volatile sig_atomic_t g_stop = 0;

void* printRandomNumber(void* arg) {
    int delay = *((int*)arg);

    while (!g_stop) {
        double randomValue = (double)rand() / RAND_MAX;
        std::cout << "��������� �����: " << randomValue << std::endl;
    }

    return NULL;
}


void sigintHandler(int signum) {
    std::cout << "������� ������� ������ SIGINT. ���������� ������..." << std::endl;
    g_stop = 1;
}

int main() {
    signal(SIGINT, sigintHandler);
    srand(time(NULL));
    pthread_t thread;
    int delaySeconds = 2; 

    if (pthread_create(&thread, NULL, printRandomNumber, &delaySeconds) != 0) {
        std::cerr << "������ �������� ������." << std::endl;
        return 1;
    }

    std::string input;
    while (!g_stop) {
        std::cin >> input;
        std::string invertedInput(input.rbegin(), input.rend());
        std::cout << "��������������� ������: " << invertedInput << std::endl;
    }

    pthread_join(thread, NULL);

    return 0;
}
