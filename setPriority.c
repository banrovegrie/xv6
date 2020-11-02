/*By Order of the Peaky Blinders*/
#include "types.h"
#include "fcntl.h"
#include "stat.h"
#include "user.h"

int myAtoi(char *str)
{
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
            res = res * 10 + str[i] - '0';
        else
            return -1;
    }

    return res;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf(2, "error: invalid number of arguments\n");
        exit();
    }

    int priority = myAtoi(((char *)argv[1])), pid = myAtoi((char *)argv[2]);

    if (priority < 0 || pid < 0)
    {
        printf(2, "error: please enter correct arguments\n");
        exit();
    }
    else
    {
        int result = set_priority(priority, pid);

        if (result < 0)
            printf(2, "error in set_priority\n");
        else
            procdump();
    }
    exit();
}