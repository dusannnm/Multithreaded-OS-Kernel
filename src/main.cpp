#include "../h/TCB.hpp"
#include "../test/printing.hpp"
#include "../h/Riscv.hpp"
#include "../h/syscall_cpp.hpp"
#include "../lib/console.h"

extern void userMain();
void userMainWrapper(void* arg) {
    userMain();
    ((Semaphore*)arg)->signal();
}

int main() {

    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);

    printString("Main started\n");

    Semaphore userSem(0);
    TCB* threads[2];
    printString("Threads create\n");
    thread_create(&threads[0], nullptr, nullptr); //main je vec u scheduleru
    TCB::running = threads[0];

    thread_create(&threads[1], userMainWrapper, &userSem);

    printString("UserMain started\n");

    userSem.wait();
    return 0;
}
