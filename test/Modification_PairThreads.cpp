//
// Created by os on 9/24/25.
//

#include "Modification_PairThreads.hpp"
#include "printing.hpp"
#include "../h/syscall_cpp.hpp"


class modificationPair: public Thread {
    void modificationPairBody(void* arg);
    public:
    modificationPair():Thread() {}

    void run() override {
        modificationPairBody(nullptr);
    }
};

void modificationPair::modificationPairBody(void *arg) {
    for (int i = 0; i<3 ; i++)
    {
        int id = getThreadId();

        printString("Thread id = "); printInt(id);
        printString(" iteration number "); printInt(i); printString(" before sync\n");

        this->sync();

        printString("Thread id = "); printInt(id);
        printString(" iteration number "); printInt(i); printString(" after sync\n");
    }
}

void Modification_PairThreads_test()
{
    Thread* threads[2];

    for(int i = 0; i < 2; i++) {
        threads[i] = new modificationPair();
    }

    for(auto & thread : threads) {
        thread->start();
    }

    Thread::pair(threads[0],threads[1]);

    for(auto & thread : threads) {
        thread->join();
    }
}
