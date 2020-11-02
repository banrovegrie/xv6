# Enhanced xv6

## Outline

Over the current xv6 (MIT), I have implemented the following:

1. waitx
2. ps
3. Different schedulers namely: FCFS, PBS, RR and MLFQ

Every change has been well-documented in my github.

## Task 1

The `waitx(int *wtime, int *rtime)` system calls builds upon `wait()` this and also returns the runtime and the waiting time of the child process. 

Implemented in `proc.c` with necessary changes in other files (in order to make it a system call).

## Task 2

Used `procdump()` in `ps.c` to implement this.

## Task 3

Implemented `scheduler_rr.c`, `scheduler_pbs.c`, `scheduler_mlfq.c`, `scheduler_fcfs.c` respectively.

For PBS, `setPriority(int, int)` has also been implemented.

Also, as required for MLFQ:

<img src="https://cdn.discordapp.com/attachments/700032924241625108/772882537801580584/unknown.png">

<img src="https://cdn.discordapp.com/attachments/702963059764887656/772884621917552740/unknown.png">