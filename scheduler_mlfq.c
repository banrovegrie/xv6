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

void scheduler(void)
{
    struct proc *p;
    struct cpu *c = mycpu();
    c->proc = 0;
    while (1)
    {
        sti();

        acquire(&ptable.lock);
        for (int i = 1; i < 5; i++)
            split(&queues[i], &queues[i - 1], 30);

        p = 0;
        for (int i = 0; i < 5; i++)
        {
            if (length(queues[i]) == 0)
                continue;

            p = queues[i]->p;
            queues[i] = pop(queues[i]);
            break;
        }

        if (p == 0 || p->state != RUNNABLE)
        {
            release(&ptable.lock);
            continue;
        }

        p->cur_timeslices++;
        p->number_of_runs++;

        c->proc = p;
        switchuvm(p);
        p->state = RUNNING;

        swtch(&(c->scheduler), p->context);
        switchkvm();

        c->proc = 0;

        if (p != 0 && p->state == RUNNABLE)
        {
            if (p->punish == 0)
            {
                p->cur_timeslices = 0, p->age_time = ticks;
                queues[p->cur_queue] = push(queues[p->cur_queue], p);
            }
            else
            {

                p->cur_timeslices = 0, p->punish = 0, p->age_time = ticks;

                if (p->cur_queue != 4)
                    p->cur_queue++;

                cprintf("MLFQ: process %d promoted to queue %d at ticks: %d\n", p->pid, p->cur_queue, ticks);
                queues[p->cur_queue] = push(queues[p->cur_queue], p);
            }
        }

        release(&ptable.lock);
    }
}