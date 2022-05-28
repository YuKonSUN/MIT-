#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *p_path, char *c_path)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(p_path, 0)) < 0)
    {
        fprintf(2, "can not entry path! \n");
        exit(1);
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "ls: cannot stat %s\n", p_path);
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_FILE:
        fprintf(2, "it's not a directory!\n");
        exit(1);
        break;
    case T_DIR:
        if (strlen(p_path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("ls: path too long\n");
            break;
        }
        strcpy(buf, p_path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if (stat(buf, &st) < 0)
            {
                printf("ls: cannot stat %s\n", buf);
                continue;
            }
            if (st.type == T_DIR && strcmp(p, ".") != 0 && strcmp(p, "..") != 0)
            {
                find(buf, c_path);
            }
            else if (strcmp(p, c_path) == 0)
            {
                printf("%s\n", buf);
            }
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(2, "wrong input format!\n");
        exit(1);
    }
    find(argv[1], argv[2]);

    exit(0);
}