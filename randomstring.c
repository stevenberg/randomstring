#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage(const char *);

int main(int argc, char **argv)
{
    int (*isvalid)(int) = isalnum;
    long length = -1;
    int c;
    while ((c = getopt(argc, argv, ":l:s")) != -1) {
        switch (c) {
        case 'l':
            length = strtol(optarg, NULL, 10);
            break;
        case 's':
            isvalid = isprint;
            break;
        case ':':
        case '?':
            usage(argv[0]);
        }
    }

    if (length < 1)
        usage(argv[0]);

    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Error opening /dev/urandom");
        exit(EXIT_FAILURE);
    }

    while (length) {
        int c = getc(fp);
        if (isvalid(c)) {
            putchar(c);
            length--;
        }
    }
    putchar('\n');

    fclose(fp);
}

void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s -l LENGTH [-s]\n", progname);
    exit(EXIT_FAILURE);
}
