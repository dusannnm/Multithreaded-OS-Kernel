//
// Created by os on 8/12/25.
//

#include "../h/Riscv.hpp"
#include "../lib/console.h"
#include "../h/TCB.hpp"
#include "../h/Sem.hpp"



void Riscv::popSppSpie() {
    mc_sstatus(SSTATUS_SPP); //tells processor that new thread is working ih user mode, not in supervisor mode
    __asm__ volatile("csrw sepc, ra");
    __asm__ volatile("sret");
}

void Riscv::handleSupervisorTrap()
{
    uint64 scause = r_scause();
    if (scause == 0x8000000000000001UL)
    {
        // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)
        mc_sip(SIP_SSIP); // removing interrupt from pedning queue
        //TCB::timeSliceCounter++;
        //if (TCB::timeSliceCounter >= TCB::running->getTimeSlice())
        //{
        //    uint64 volatile sepc = r_sepc();
        //    uint64 volatile sstatus = r_sstatus();
        //    TCB::timeSliceCounter = 0;
        //    TCB::dispatch();
        //    w_sstatus(sstatus);
        //    w_sepc(sepc);
        //}
    }
    else if (scause == 0x8000000000000009UL)
    {
        // interrupt: yes; cause code: supervisor external interrupt (PLIC; could be keyboard)
        console_handler();
    }
    else if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL)
    {
        //__asm__ volatile("sd a0, %0" : "=m" (arg0));
        //__asm__ volatile("sd a1, %0" : "=m" (arg1));
        //__asm__ volatile("sd a2, %0" : "=m" (arg2));
        //__asm__ volatile("sd a3, %0" : "=m" (arg3));
        //__asm__ volatile("sd a4, %0" : "=m" (arg4));
        //__asm__ volatile("sd a5, %0" : "=m" (arg5));
        //__asm__ volatile("sd a6, %0" : "=m" (arg6));
        //__asm__ volatile("sd a7, %0" : "=m" (arg7));

        // interrupt: no; cause code: environment call from U-mode(8) or S-mode(9)
        uint64 volatile sepc = r_sepc() + 4; //ecall goes back to istelf, not to next instruction
        uint64 volatile sstatus = r_sstatus();
	
        //TCB::timeSliceCounter = 0;
        //TCB::dispatch();
        //w_sstatus(sstatus);
        //w_sepc(sepc);

        uint64 codeOp;
        __asm__ volatile("ld %0, 8*10(fp)" : "=r" (codeOp));

        if(codeOp == 0x01) //mem_alloc(size)
        {
            uint64 arg1; //size_t arg1; => size
        __asm__ volatile("ld %0, 8*11(fp)" : "=r" (arg1));

            void* ret = MemoryAllocator::mem_alloc((uint64)arg1);

            __asm__ volatile("sd %0, 80(fp)" : : "r"(ret));
        }
        else if(codeOp == 0x02) //mem_free(void*)
        {
            void* arg1; //void* ptr;
        __asm__ volatile("ld %0, 8*11(fp)" : "=r" (arg1));

            int ret = MemoryAllocator::mem_free(arg1);

            __asm__ volatile("sd %0, 80(fp)" : : "r"(ret));
        }
        else if(codeOp == 0x11) //thread_create(handle, start_routine, arg, stack)
        {
            uint32 success = 0;
            uint32 fail = -1;
            TCB** handle; //jer je thread_t koju CAPI salje pokazivac na nit
            TCB::Body start_routine;
            void* arguments;
                uint64* stack;
            __asm__ volatile("ld %0, 8*11(fp)" : "=r" (handle));
            __asm__ volatile("ld %0, 8*12(fp)" : "=r" (start_routine));
            __asm__ volatile("ld %0, 8*13(fp)" : "=r" (arguments));
            __asm__ volatile("ld %0, 8*14(fp)" : "=r" (stack));

            *handle = TCB::createThread(start_routine,arguments,stack);

            if(*handle != nullptr) {
                __asm__ volatile("sd %0, 80(fp)" : : "r"(success));
            }
            else {
                __asm__ volatile("sd %0, 80(fp)" : : "r"(fail));
            }
        }
        else if(codeOp == 0x12) //thread_exit()
        {
            TCB::exit();
            __asm__ volatile("sd %0, 80(fp)" : : "r"(-1));
        }
        else if(codeOp == 0x13) //thread_dispatch()
        {
            TCB::dispatch();
        }
        else if(codeOp == 0x14) //thread_join(handle)
        {
            TCB* other;
            __asm__ volatile("ld %0, 8*11(fp)" : "=r" (other));
            other->join();
        }
        else if(codeOp == 0x21) //sem_open(handle,init)
        {
            uint32 success = 0;
            uint32 fail = -1;
            Sem** handle; //jer je sem_t koju CAPI salje pokazivac na semaforsku promenjlivu
            uint64 init;
            __asm__ volatile("ld %0, 8*11(fp)" : "=r" (handle));
            __asm__ volatile("ld %0, 8*12(fp)" : "=r" (init));

            *handle = Sem::createSemaphore(init);

            if(*handle != nullptr) {
                __asm__ volatile("sd %0, 80(fp)" : : "r"(success));
            }
            else {
                __asm__ volatile("sd %0, 80(fp)" : : "r"(fail));
            }
        }
        else if(codeOp == 0x22) //sem_close(handle)
        {
            Sem* handle;
            uint32 fail = -2;

            __asm__ volatile("ld %0, 8*11(fp)" : "=r" (handle));

            if(handle!=nullptr){
                int ret = handle->close();
                __asm__ volatile("sd %0, 80(fp)" : : "r"(ret));
            }
            else {
                __asm__ volatile("sd %0, 80(fp)" : : "r"(fail));
            }
        }
        else if(codeOp == 0x23) //sem_wait(id)
        {
            Sem* id;
            uint32 fail = -2; //proba posto je u Semaphore::wait -1

            __asm__ volatile("ld %0, 8*11(fp)" : "=r" (id));

            if(id!=nullptr){
                int ret = id->wait();
                __asm__ volatile("sd %0, 80(fp)" : : "r"(ret));
            }
            else {
                __asm__ volatile("sd %0, 80(fp)" : : "r"(fail));
            }
        }
        else if(codeOp == 0x24)// sem_signal(id)
        {
            Sem* id;
            uint32 fail = -2;

            __asm__ volatile("ld %0, 8*11(fp)" : "=r" (id));

            if(id!=nullptr){
                int ret = id->signal();
                __asm__ volatile("sd %0, 80(fp)" : : "r"(ret));
            }
            else {
                __asm__ volatile("sd %0, 80(fp)" : : "r"(fail));
            }
        }
        else if(codeOp == 0x25) //sem_timedwait(id, timeout)
        {

        }
        else if(codeOp == 0x26) //sem_trywait(id)
        {
            Sem* id;
            uint32 fail = -2;

            __asm__ volatile("ld %0, 8*11(fp)" : "=r" (id));

            if(id!=nullptr){
                int ret = id->tryWait();
                __asm__ volatile("sd %0, 80(fp)" : : "r"(ret));
            }
            else {
                __asm__ volatile("sd %0, 80(fp)" : : "r"(fail));
            }
        }
        else if(codeOp == 0x31) //time_sleep(time_t)
        {

        }
        else if(codeOp == 0x41) //getc()
        {
			int ret = __getc();

                __asm__ volatile("sd %0, 80(fp)" : : "r"(ret));
        }
        else if(codeOp == 0x42) //putc(char)
        {
			char c;
            __asm__ volatile("ld %0, 8*11(fp)" : "=r" (c));
            __putc(c);
        }

        w_sstatus(sstatus);
        w_sepc(sepc);

    }
    else
    {
        // unexpected trap cause
		__putc('E');
		__putc('R');
		__putc('R');
		__putc('\n');
        while(true);
    }
}

//Izlazni operand = ono što asm izračuna i vrati C++ kodu
//Ulazni operand = ono što C++ kod da asm-u da koristi
