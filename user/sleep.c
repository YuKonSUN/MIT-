#include "kernel/types.h"

#include "user.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "usage :sleep , wrong argc!\n");
        exit(1);
    }
    sleep(atoi(argv[1]));

    exit(0);
}