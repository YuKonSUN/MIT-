#include "kernel/types.h"
#include "user.h"

int prime(int lpipe[])
{
    int base = 0;
    int flag = 0;
    close(lpipe[1]);
    if (read(lpipe[0], &base, sizeof(int)) == 0)
    {
        exit(0);
    }

    if (fork() == 0)
    {
        int p[2];
        int i = 0;

        pipe(p);

        while (read(lpipe[0], &i, sizeof(int)))
        {
            if (i % base != 0)
            {
                write(p[1], &i, sizeof(int));
            }
        }

        close(lpipe[0]);
        prime(p);
    }
    else
    {
        printf("prime: %d\n", base);
    }

    wait(&flag);
    if (flag)
    {
        fprintf(2, "something was wrong in child process!\n");
    }

    exit(0);
}

int main(int argc, char *argv[])
{
    int p[2];
    pipe(p);
    for (int i = 2; i <= 35; i++)
    {
        write(p[1], &i, sizeof(int));
    }
    prime(p);

    return 0;
}
