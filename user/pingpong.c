#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    int p[2];

    pipe(p);
    if (fork() == 0)
    {
        char s[5];

        read(p[0], s, 4);
        printf("%d: received %s\n", getpid(), s);
        write(p[1], "pong", 4);
    }
    else
    {
        char s[5];
        int flag = 0;

        write(p[1], "ping", 4);
        wait(&flag);
        if (flag != 0)
        {
            fprintf(2, "someting wrong in child process!\n");
        }

        read(p[0], s, 4);
        printf("%d: received %s\n", getpid(), s);
    }
    exit(0);
}