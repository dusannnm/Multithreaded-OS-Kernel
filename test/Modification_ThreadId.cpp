//
// Created by os on 9/24/25.
//

#include "Modification_ThreadId.hpp"
#include "printing.hpp"
#include "../h/syscall_cpp.hpp"

class Mod: public Thread {
    void modBody(void* arg);
public:
    Mod():Thread() {}

    void run() override {
        modBody(nullptr);
    }
};

void Mod::modBody(void *arg) {

    int id = getThreadId();

    for (int i = 0; i<10 ; i++)
    {
        int id = getThreadId();
        printString("This is thread number "); printInt(id); printString("\n");
        for (int j = 0; j < 5000000; j++) {}
    }
    printString("Thread id = "); printInt(id); printString(" finished!\n");
}

void Modification_ThreadID_test()
{
    Thread* threads[3];

    for(int i = 0; i < 3; i++) {
        threads[i] = new Mod();
    }

    for(auto & thread : threads) {
        thread->start();
    }

    for(auto & thread : threads) {
        thread->join();
    }

}