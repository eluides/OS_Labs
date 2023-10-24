#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include <cstdlib>

int main() {
    pid_t childPid;
    int status;
    if ((childPid = fork()) == 0) {
        exit(0);
    }
    else if (childPid == -1) {
        std::cerr << "Ошибка при создании дочернего процесса" << std::endl;
        return 1;
    }
    else {
        if (waitpid(childPid, &status, 0) == -1) {
            std::cerr << "Ошибка при ожидании завершения дочернего процесса" << std::endl;
            return 1;
        }

        if (WIFEXITED(status)) {
            std::cout << "Дочерний процесс завершился с кодом: " << WEXITSTATUS(status) << std::endl;
        }
        else if (WIFSIGNALED(status)) {
            std::cout << "Дочерний процесс был завершен с сигналом: " << WTERMSIG(status) << std::endl;
        }
    }

    return 0;
}
