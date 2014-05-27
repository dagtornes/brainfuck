#include <stdio.h>
#include <string.h>

int scan(int ip, int dir, char skip, char stop, const char *program, int limit)
{
    int start_ip = ip;
    while (program[ip] != stop) {
        ip += dir;
        if (program[ip] == skip)
            ip = scan(ip + dir, dir, skip, stop, program, limit) + dir;

        if (ip == limit) {
            printf("Mismatched %c at %d\n", stop, start_ip);
            return -1;
        }
    }
    return ip;
}

int scan_back(int ip, const char *program)
{
    return scan(ip, -1, ']', '[', program, -1);
}

int scan_fwd(int ip, const char *program)
{
    return scan(ip, 1, '[', ']', program, strlen(program));
}

