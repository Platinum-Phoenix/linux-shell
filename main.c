#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_prompt1(void)
{
    char hostname[100];
    gethostname(hostname, sizeof(hostname));
    char name[300];
    getlogin_r(name, 300);
    printf("%s@%s%c ", name, hostname, '$');
}

void print_prompt2(void)
{
    fprintf(stderr, "> ");
}

char *read_cmd()
{
    char *line = NULL;
    size_t cap = 0;
    ssize_t len;

    if ((len = getline(&line, &cap, stdin)) < 0)
    {
        // exit on EOF (^D/Ctrl+D)
        if (feof(stdin))
            exit(0);
        exit(1);
    }

    return line;
}

int main(int argc, char **argv)
{
    system("clear");
    char *cmd;

    do
    {
        print_prompt1();

        cmd = read_cmd();

        if (!cmd)
        {
            exit(EXIT_SUCCESS);
        }

        if (cmd[0] == '\0' || strcmp(cmd, "\n") == 0)
        {
            free(cmd);
            continue;
        }

        if (strcmp(cmd, "exit\n") == 0)
        {
            free(cmd);
            break;
        }
        system(cmd);

        free(cmd);
    } while (1);

    return 0;
}
