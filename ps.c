// By Order of the Peaky Blinders - I wrote file ok.

#include "types.h"
#include "fcntl.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        printf(2, "error in number of arguments\n");
        exit();
    }

    procdump();
    exit();
}
