//
// Created by os on 8/19/25.
//

#include "../h/syscall_cpp.hpp"
#include "../h/MemoryAllocator.hpp"

//void* operator new(size_t n){
//        return MemoryAllocator::mem_alloc(n);
//}

//void operator delete(void* ptr){
//       MemoryAllocator::mem_free((uint8*)ptr);
//}

//void* operator new[](size_t n){
//        return MemoryAllocator::mem_alloc(n);
//}

//void operator delete[](void* ptr){
//        MemoryAllocator::mem_free((uint8*)ptr);
//}


Thread::Thread (void (*body)(void*), void* arg)
{
        this->body = body;
        this->arg = arg;
        this->myHandle = nullptr;
}


Thread:: ~Thread ()
{
      //if(!myHandle) {
      //        delete this->myHandle;
      //        myHandle = nullptr
      //}
      //else join();
}


int Thread::start ()
{
        thread_wait_barrier();
        return thread_create(&myHandle, body, arg);
}


void Thread::dispatch ()
{
        thread_dispatch();
}


 int Thread::sleep (time_t time)
{
        return time_sleep(time);
}


Thread::Thread ()
{
        this->body = runWrapper;
        this->arg = this;
        this->myHandle = nullptr;
}


void Thread::runWrapper(void* thread)
{
        if(thread) {
                ((Thread*)thread)->run();
        }
}


void Thread::join ()
{
    thread_join(myHandle);
}


int Thread::getThreadId()
{
    return thread_id();
}


void Thread::setMaximumThreads(int number)
{
    thread_set_max_threads(number);
}

void Thread::pair(Thread* t1, Thread* t2)
{
    thread_pair(t1->myHandle,t2->myHandle);
}


void Thread::sync()
{
    thread_sync(myHandle);
}


Semaphore::Semaphore (unsigned init)
{
        sem_open(&myHandle, init);
}

Semaphore::~Semaphore ()
{
        sem_close(myHandle);
}


int Semaphore::wait ()
{
        return sem_wait(myHandle);
}


int Semaphore::signal ()
{
        return sem_signal(myHandle);
}


int Semaphore::timedWait (time_t time)
{
        return sem_timedwait(myHandle, time);
}


int Semaphore::tryWait()
{
        return sem_trywait(myHandle);
}

int Semaphore::waitN(unsigned n)
{
        return sem_wait_n(myHandle, n);
}

int Semaphore::signalN(unsigned n)
{
        return sem_signal_n(myHandle,n);
}

char Console::getc() {
        char c = ::getc();
        return c;
}

void Console::putc(char c) {
        ::putc(c);
}




