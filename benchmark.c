/*By Order of the Peaky Blinders*/
#include "types.h"
#include "user.h"

#define num_pro 10

int main(int argc, char *argv[])
{
    for (int pNo = 0, pid = 0; pNo < num_pro; pNo++)
    {
        if ((pid = fork()) < 0)
        {
            printf(1, "F for fork\n");
            continue;
        }
        if (pid == 0)
        {
            int total = 0;
            if (pNo % 4 == 0)
            {
                // CPU
                for (int i = 0; i < 1e9; i++)
                {
                    total += i;
                }
            }
            if (pNo % 4 == 1)
            {
                // IO
                for (int i = 0; i < 10; i++)
                {
                    sleep(70);
                    total += i;
                }
            }
            if (pNo % 4 == 2)
            {
                // IO then CPU
                sleep(500);
                for (int i = 0; i < 5; i++)
                {
                    total += i;
                    for (int j = 0; j < 1e8; j++)
                    {
                        total += j;
                    }
                }
            }
            if (pNo % 4 == 3)
            {
                for (int i = 0; i < 5; i++)
                {
                    total += i;
                    for (int j = 0; j < 1e8; j++)
                        total += j;
                }
                sleep(500);
            }
            printf(1, "Benchmark: %d Exited, Category : %d, Total : %d\n", pNo, pNo % 4, total);
            exit();
        }
        else
            set_priority(100 - (20 + pNo) % 2, pid);
    }

    for (int j = 0; j < num_pro + 5; j++)
        wait();

    exit();
}