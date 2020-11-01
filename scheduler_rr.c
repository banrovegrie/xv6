/*By Order of the Peaky Blinders*/
#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "traps.h"

// Interrupt descriptor table (shared by all CPUs).
extern struct gatedesc idt[256];
extern uint vectors[]; // in vectors.S: array of 256 entry pointers
extern struct spinlock tickslock;
extern uint ticks;

extern struct
{
    struct spinlock lock;
    struct proc proc[NPROC];
} ptable;

extern int nextpid;
extern void forkret(void);
extern void trapret(void);

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void scheduler(void)
{
    // printf(2, "using rr\n");
    struct proc *p;
    struct cpu *c = mycpu();
    c->proc = 0;

    while (1)
    {
        // Enable interrupts on this processor.
        sti();

        // Loop over process table looking for process to run.
        acquire(&ptable.lock);
        for (p = ptable.proc; p < &ptable.proc[NPROC]; p++)
        {
            if (p->state == RUNNABLE)
            {
                // Switch to chosen process.  It is the process's job
                // to release ptable.lock and then reacquire it
                // before jumping back to us.
                c->proc = p;
                switchuvm(p);
                p->state = RUNNING;
                p->number_of_runs++;

                swtch(&(c->scheduler), p->context);
                switchkvm();

                // Process is done running for now.
                // It should have changed its p->state before coming back.
                c->proc = 0;
            }
        }
        release(&ptable.lock);
    }
}