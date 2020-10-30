// By Order of the Peaky Blinders - I wrote file ok.

#include "types.h"
#include "fcntl.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv)
{

    if (argc <= 1)
    {
        printf(2, "error in number of arguments\n");
        exit();
    }

    int pid = fork();
    if (pid < 0)
    {
        printf(2, "error in forking\n");
        exit();
    }
    else if (pid == 0)
    {
        if (exec(argv[1], argv + 1) < 0)
        {
            printf(2, "error in exec\n");
            exit();
        }
    }
    else
    {
        int wtime, rtime, wid = waitx(&wtime, &rtime);
        printf(1, "%s\nProcess ID: %d\nWaiting time: %d\nRunning time: %d\n\n", argv[1], wid, wtime, rtime);
        exit();
    }
}
