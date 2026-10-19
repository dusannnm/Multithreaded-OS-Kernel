//
// Created by os on 8/15/25.
//

#ifndef PROJECT_BASE_SYSCALL_C_HPP
#define PROJECT_BASE_SYSCALL_C_HPP

#include "../lib/hw.h"
#include "../h/TCB.hpp"
#include "../h/Sem.hpp"

    class TCB;
    typedef TCB* thread_t;
    class Sem;
    typedef Sem* sem_t;

    void* mem_alloc(size_t size);
    uint32 mem_free(void* ptr);
<<<<<<< HEAD
    size_t mem_get_free_space();
    size_t mem_get_largest_free_block();
=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

    uint32 thread_create(thread_t* handle, void(*startRoutine)(void*), void* arg);
    uint32 thread_exit();
    void thread_dispatch();
    void thread_join(thread_t handle);
<<<<<<< HEAD
    int thread_id();
    void thread_set_max_threads(int number);
    void thread_wait_barrier();
    void thread_pair(thread_t thread1, thread_t thread2);
    void thread_sync(thread_t handle);
=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

    uint32 sem_open(sem_t* handle, uint64 init);
    uint32 sem_close(sem_t handle);
    uint32 sem_wait(sem_t id);
    uint32 sem_signal(sem_t id);
    uint32 sem_trywait(sem_t id);
    uint32 sem_timedwait(sem_t id, time_t time);
<<<<<<< HEAD
    uint32 sem_signal_n(sem_t id, uint64 n);
    uint32 sem_wait_n(sem_t id, uint64 n);

=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

    uint32 time_sleep(time_t time);

    char getc();
    void putc(char c);






#endif //PROJECT_BASE_SYSCALL_C_HPP