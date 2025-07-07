#include "../kernel/types.h"
#include "../kernel/param.h"
#include "../kernel/memlayout.h"
#include "../kernel/riscv.h"
#include "../kernel/spinlock.h"
#include "../kernel/proc.h"
#include "../user/user.h"

#define STACK_SIZE 100
volatile int prlock = 0;

// A simple lock implementation using atomic operations.
static inline void
u_acquire(volatile int *lock)
{
    while(__sync_lock_test_and_set(lock, 1) != 0) ;
}
static inline void
u_release(volatile int *lock)
{
    __sync_lock_release(lock);
}


void *my_thread(void *arg) {
    uint64 number = (uint64)arg;
    for (int i = 0; i < 100; i++) {
        number++;
        u_acquire(&prlock);                 // Acquire the lock
        printf("thread: %lu\n", number);
        u_release(&prlock);                 // Release the lock
    }
    return (void *) number;
}

int main(int argc, char *argv[]) {
    int sp1[STACK_SIZE], sp2[STACK_SIZE], sp3[STACK_SIZE];

    u_acquire(&prlock);
    int ta = thread(my_thread, sp1 + STACK_SIZE, (void *)100);
    printf("NEW THREAD CREATED %d\n", ta);
    u_release(&prlock);

    u_acquire(&prlock);
    int tb = thread(my_thread, sp2 + STACK_SIZE, (void *)200);
    printf("NEW THREAD CREATED %d\n", tb);
    u_release(&prlock);

    u_acquire(&prlock);
    int tc = thread(my_thread, sp3 + STACK_SIZE, (void *)300);
    printf("NEW THREAD CREATED %d\n", tc);
    u_release(&prlock);

    jointhread(ta);
    jointhread(tb);
    jointhread(tc);

    u_acquire(&prlock);
    printf("DONE\n");
    u_release(&prlock);

    return 0;
}
