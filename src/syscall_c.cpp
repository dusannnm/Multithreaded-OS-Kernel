//
// Created by os on 8/15/25.
//

#include "../h/syscall_c.hpp"
#include "../lib/mem.h"

void* mem_alloc(size_t size)
{
	size_t blocksNumber = ((size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE);

    __asm__ volatile("mv a1, %0" : : "r"(blocksNumber));
    __asm__ volatile("li a0, 0x01");
    __asm__ volatile("ecall");

    void* returnValue;
    __asm__ volatile("mv %0, a0" : "=r"(returnValue));
    return returnValue;
}


uint32 mem_free(void* ptr)
{
	__asm__ volatile("mv a1, %0" : : "r"(ptr));
	__asm__ volatile("li a0, 0x02");
	__asm__ volatile("ecall");

	uint32 returnValue;
    __asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


<<<<<<< HEAD
size_t mem_get_free_space()
{
	__asm__ volatile("li a0, 0x03");
	__asm__ volatile("ecall");

	size_t returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


size_t mem_get_largest_free_block()
{
	__asm__ volatile("li a0, 0x04");
	__asm__ volatile("ecall");

	size_t returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
uint32 thread_create(thread_t* handle, void(*startRoutine)(void*), void* arg)
{
	uint8* stack = (uint8*) mem_alloc(DEFAULT_STACK_SIZE);
	__asm__ volatile("mv a4, %0" : : "r"(stack));
	__asm__ volatile("mv a3, %0" : : "r"(arg));
	__asm__ volatile("mv a2, %0" : : "r"(startRoutine));
	__asm__ volatile("mv a1, %0" : : "r"(handle));

	__asm__ volatile("li a0, 0x11");
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


uint32 thread_exit()
{
	__asm__ volatile("li a0, 0x12");
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


void thread_dispatch()
{
	__asm__ volatile("li a0, 0x13");
	__asm__ volatile("ecall");
}


void thread_join(thread_t handle)
{
    __asm__ volatile("mv a1, %0" : : "r"(handle));
	__asm__ volatile("li a0, 0x14");
	__asm__ volatile("ecall");
}


<<<<<<< HEAD
int thread_id()
{
	__asm__ volatile("li a0, 0x15");
	__asm__ volatile("ecall");

	int returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


void thread_set_max_threads(int number)
{
	__asm__ volatile("mv a1, %0" : : "r"(number));
	__asm__ volatile("li a0, 0x16");
	__asm__ volatile("ecall");
}


void thread_wait_barrier()
{
	__asm__ volatile("li a0, 0x17");
	__asm__ volatile("ecall");
}


void thread_pair(thread_t thread1, thread_t thread2)
{
	__asm__ volatile("mv a2, %0" : : "r"(thread2));
	__asm__ volatile("mv a1, %0" : : "r"(thread1));
	__asm__ volatile("li a0, 0x18");
	__asm__ volatile("ecall");
}


void thread_sync(thread_t handle)
{
	__asm__ volatile("mv a1, %0" : : "r"(handle));
	__asm__ volatile("li a0, 0x19");
	__asm__ volatile("ecall");
}


=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
uint32 sem_open(sem_t* handle, uint64 init)
{
	__asm__ volatile("mv a2, %0" : : "r"(init));
	__asm__ volatile("mv a1, %0" : : "r"(handle));
	__asm__ volatile("li a0, 0x21");
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


uint32 sem_close(sem_t handle)
{
	__asm__ volatile("mv a1, %0" : : "r"(handle));
	__asm__ volatile("li a0, 0x22");
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


uint32 sem_wait(sem_t id)
{
	__asm__ volatile("mv a1, %0" : : "r"(id));
	__asm__ volatile("li a0, 0x23");
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


uint32 sem_signal(sem_t id)
{
	__asm__ volatile("mv a1, %0" : : "r"(id));
	__asm__ volatile("li a0, 0x24");
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}


uint32 sem_trywait(sem_t id)
{
	__asm__ volatile("mv a1, %0" : : "r"(id));
<<<<<<< HEAD
	__asm__ volatile("li a0, 0x27");
=======
	__asm__ volatile("li a0, 0x26");
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}

uint32 sem_timedwait(sem_t id, time_t time)
{
	return 0;
}

<<<<<<< HEAD
uint32 sem_wait_n(sem_t id, uint64 n)
{
	__asm__ volatile("mv a2, %0" : : "r"(n));
	__asm__ volatile("mv a1, %0" : : "r"(id));
	__asm__ volatile("li a0, 0x25");
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}

uint32 sem_signal_n(sem_t id, uint64 n)
{
	__asm__ volatile("mv a2, %0" : : "r"(n));
	__asm__ volatile("mv a1, %0" : : "r"(id));
	__asm__ volatile("li a0, 0x26");
	__asm__ volatile("ecall");

	uint32 returnValue;
	__asm__ volatile("mv %0, a0" : "=r"(returnValue));
	return returnValue;
}
=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

uint32 time_sleep(time_t time)
{
	return 0;
}


char getc()
{
	__asm__ volatile("li a0, 0x41");
    __asm__ volatile ("ecall");

    char c;
    __asm__ volatile("mv %0, a0" : "=r"(c));
    return c;
}


void putc(char c)
{
	__asm__ volatile("mv a1, %0" : : "r"(c));
	__asm__ volatile("li a0, 0x42");
	__asm__ volatile("ecall");
}