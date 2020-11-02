/*By Order of the Peaky Blinders*/
#include "types.h"
#include "user.h"

#define num_pro 10

int main(int argc, char *argv[])
{
    for (int p_roll = 0, pid = 0; p_roll < num_pro; p_roll++)
    {
        if ((pid = fork()) < 0)
        {
            printf(1, "F for fork\n");
            continue;
        }
        if (pid == 0)
        {
            int total = 0;
            if (p_roll % 4 == 0)
            {
                for (int i = 0; i < 1e9; i++)
                    total += i;
            }
            else if (p_roll % 4 == 1)
            {
                for (int i = 0; i < 10; i++)
                    sleep(70), total += i;
            }
            else if (p_roll % 4 == 2)
            {
                sleep(500);
                for (int i = 0; i < 5; i++)
                {
                    total += i;
                    for (int j = 0; j < 1e8; j++)
                        total += j;
                }
            }
            else
            {
                for (int i = 0; i < 5; i++)
                {
                    total += i;
                    for (int j = 0; j < 1e8; j++)
                        total += j;
                }
                sleep(500);
            }
            printf(1, "Benchmark: %d Exited, Category : %d, Total : %d\n", p_roll, p_roll % 4, total);
            exit();
        }
        else
            set_priority(100 - (20 + p_roll) % 2, pid);
    }

    for (int j = 0; j < num_pro + 5; j++)
        wait();

    exit();
}