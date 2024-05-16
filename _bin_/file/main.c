#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <fcntl.h>
#include "get_next_line.h"

#define R "\x1b[1;31m"
#define G "\x1b[1;32m"
#define B "\x1b[1;36m"
#define Y "\x1b[1;33m"
#define M "\x1b[1;35m"
#define BOLD "\x1b[1m"
#define N "\x1b[0m"

#ifdef __APPLE__
   #define checker "checker_mac"
#else
    #define checker "checker_linux"
#endif

static void step1()
{
    printf(M BOLD"\nStep1.\tError Management\n\n" N);

    printf(B "1. ./push_swap 1 e\n" Y);
    printf(G "   Error\t=>\t" Y);
    fflush(stdout);
    system("./push_swap 1 e");

    printf(B "2. ./push_swap 10 9 2 3 8 9 11\n" N);
    printf(G "   Error\t=>\t" Y);
    fflush(stdout);
    system("./push_swap 10 9 2 3 8 9 11");

    printf(B "3. ./push_swap 2147483648\n" N);
    printf(G "   Error\t=>\t" Y);
    fflush(stdout);
    system("./push_swap 2147483648");

    printf(B "4. ./push_swap -2147483649\n" N);
    printf(G "   Error\t=>\t" Y);
    fflush(stdout);
    system("./push_swap -2147483649");

    printf(B "5. ./push_swap\n" N);
    printf(G "   \\n\t\t=>\t" Y "\\n");
    fflush(stdout);
    system("./push_swap");
    printf(N "\n");

    printf(B "6. ./push_swap 999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999\n" N);
    printf(G "   Error\t=>\t" Y);
    fflush(stdout);
    system("./push_swap 999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
    printf(N "\n\n");
}

static void step2()
{
    printf(M BOLD"\nStep2.\tPush_swap - Identity test\n\n" N);

    printf(B "1. ./push_swap 42\n" Y);
    printf(G "   \\n\t\t=>\t" Y "\\n");
    fflush(stdout);
    system("./push_swap 42");
    printf(N "\n");

    printf(B "2. ./push_swap 2 3\n" Y);
    printf(G "   \\n\t\t=>\t" Y "\\n");
    fflush(stdout);
    system("./push_swap 2 3");
    printf(N "\n");

    printf(B "3. ./push_swap 0 1 2 3\n" Y);
    printf(G "   \\n\t\t=>\t" Y "\\n");
    fflush(stdout);
    system("./push_swap 0 1 2 3");
    printf(N "\n");

    printf(B "4. ./push_swap 0 1 2 3 4 5 6 7 8\n" Y);
    printf(G "   \\n\t\t=>\t" Y "\\n");
    fflush(stdout);
    system("./push_swap 0 1 2 3 4 5 6 7 8");
    printf(N "\n");

    printf(B "4. ./push_swap 2 4 5 7 8\n" Y);
    printf(G "   \\n\t\t=>\t" Y "\\n");
    fflush(stdout);
    system("./push_swap 2 4 5 7 8");
    printf(N "\n\n");
}

static void step3()
{
    printf(M BOLD"\nStep3.\tPush_swap - Simple version\n\n" N);

    printf(B "1. ARG=\"2 1 0\"; ./push_swap $ARG | ./" checker " $ARG\n" Y);
    printf(G "   OK\t=>\t" Y);
    fflush(stdout);
    system("ARG=\"2 1 0\"; ./push_swap $ARG | _bin_/push_swap/checker_OS/" checker " $ARG");

    printf(B "2. ARG=\"10 9 2\"; ./push_swap $ARG | ./" checker " $ARG\n" Y);
    printf(G "   OK\t=>\t" Y);
    fflush(stdout);
    system("ARG=\"10 9 2\"; ./push_swap $ARG | ./_bin_/push_swap/checker_OS/" checker " $ARG");

    printf(B "3. ARG=\"2 11 -15\"; ./push_swap $ARG | ./" checker " $ARG\n" Y);
    printf(G "   OK\t=>\t" Y);
    fflush(stdout);
    system("ARG=\"2 11 -15\"; ./push_swap $ARG | ./_bin_/push_swap/checker_OS/" checker " $ARG");
    printf(N "\n");
}

static void step4()
{
    printf(M BOLD"\nStep4.\tAnother simple version\n\n" N);

    printf(B "1. ARG=\"1 5 2 4 3\"; ./push_swap $ARG | " checker " $ARG\n" Y);
    printf(G "   OK\t=>\t" Y);
    fflush(stdout);
    system("ARG=\"1 5 2 4 3\"; ./push_swap $ARG | ./_bin_/push_swap/checker_OS/" checker " $ARG");

    printf(B "2. ARG=\"1 -23 2 1111 3\"; ./push_swap $ARG | " checker " $ARG\n" Y);
    printf(G "   OK\t=>\t" Y);
    fflush(stdout);
    system("ARG=\"1 -23 2 1111 3\"; ./push_swap $ARG | ./_bin_/push_swap/checker_OS/" checker " $ARG");
    printf(N "\n");

}

static void step5()
{
    FILE *cmd_output;
    int fd;
    char *line;
    char command[100000];
    int count = 0;
    int total = 0;
    char filepath[50];

    printf(M BOLD"\nStep5.\tPush_swap - Middle version\n\n" N);
    printf(R "  _bin_/push_swap/100/*\n" N);
    for (int i = 1; i <= 10; i++)
    {
        snprintf(filepath, sizeof(filepath), "_bin_/push_swap/100/%d", i);
        printf(B "FILENAME: %s\n" N, filepath);
        fd = open(filepath, O_RDONLY);
        line = get_next_line(fd);
        close(fd);
        line[strcspn(line, "\n")] = '\0';
        memset(command, 0, 100000);
        snprintf(command, sizeof(command), "./push_swap %s | wc -l", line);
        cmd_output = popen(command, "r");
        fscanf(cmd_output, "%d", &count);
        pclose(cmd_output);
        total += count;
        snprintf(command, sizeof(command), "ARG=\"%s\"; ./push_swap $ARG | _bin_/push_swap/checker_OS/" checker " $ARG", line);
        printf( G "%d.\t" Y, i);
        fflush(stdout);
        system(command);
        free(line);
    }
    
    printf(G "\nTOTAL:\t\t" Y "%d\n", total);
    printf(G "MOYENNE:\t" Y "%d\n", total/10);
    printf(N "\n");
}

static void step6()
{
    FILE *cmd_output;
    int fd;
    char *line;
    char command[1000000];
    int count = 0;
    int total = 0;
    char filepath[50];

    printf(M BOLD"\nStep6.\tPush_swap - Advanced version\n\n" N);
    printf(R "  _bin_/push_swap/500/*\n" N);
    for (int i = 1; i <= 10; i++)
    {
        snprintf(filepath, sizeof(filepath), "_bin_/push_swap/500/%d", i);
        printf(B "FILENAME: %s\n" N, filepath);
        fd = open(filepath, O_RDONLY);
        line = get_next_line(fd);
        close(fd);
        line[strcspn(line, "\n")] = '\0';
        memset(command, 0, 100000);
        snprintf(command, sizeof(command), "./push_swap %s | wc -l", line);
        cmd_output = popen(command, "r");
        fscanf(cmd_output, "%d", &count);
        pclose(cmd_output);
        total += count;
        snprintf(command, sizeof(command), "ARG=\"%s\"; ./push_swap $ARG | _bin_/push_swap/checker_OS/" checker " $ARG", line);
        printf( G "%d.\t" Y, i);
        fflush(stdout);
        system(command);
        free(line);
    }
    
    printf(G "\nTOTAL:\t\t" Y "%d\n", total);
    printf(G "MOYENNE:\t" Y "%d\n", total/10);
    printf(N "\n");
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);

    system("clear");

    if (!strcmp(av[1], "pushswap"))
    {
        step1();
        step2();
        step3();    
        step4();
        step5();
        step6();
    }

    return 0;
}