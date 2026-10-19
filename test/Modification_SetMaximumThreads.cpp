//
// Created by os on 9/23/25.
//

#include "printing.hpp"
#include "Modification_SetMaximumThreads.hpp"
#include "../h/syscall_cpp.hpp"

class modificationA: public Thread {
    void modificationBodyA(void* arg);
    public:
    modificationA():Thread() {}

    void run() override {
        modificationBodyA(nullptr);
    }
};

void modificationA::modificationBodyA(void *arg) {
    int id = getThreadId();
    printString("Thread id = "); printInt(id); printString(" started!\n");

    for (int i = 0; i<5 ; i++)
    {
        int id = getThreadId();
        printString("Hello!"); printInt(id); printString("\n");
        for (int j = 0; j < 10000*id; j++) {}
    }
    printString("Thread id = "); printInt(id); printString(" finished!\n");
}


void Modification_SetMaximumThreads_test()
{
    Thread* threads[20];
    char input[30];
    int maxThreads;

    printString("Unesite maksimalan broj niti?\n");
    getString(input, 30);
    maxThreads = stringToInt(input);

    //printString("Hejj 1");

    Thread::setMaximumThreads(maxThreads);

    //printString("Hejj 2");


    for(int i = 0; i < 20; i++) {
        threads[i] = new modificationA();
    }

    for(auto & thread : threads) {
        thread->start();
    }

    for(auto & thread : threads) {
        thread->join();
    }

}
#include "Modification_SetMaximumThreads.hpp"