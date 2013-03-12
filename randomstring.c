#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc < 2 || !isdigit(argv[1][0])) {
        fprintf(stderr, "usage: %s LENGTH [-s]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *all =
        "~`!@#$%^&*()-_=+[{}]\\|,<.>/?"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
    char *characters;
    if (argc > 2 && !strcmp(argv[2], "-s"))
        characters = all;
    else
        characters = strchr(all, 'a');
    int length = strlen(characters);
    int counter = atoi(argv[1]);
    unsigned int indexes[counter];
    FILE *fp = fopen("/dev/urandom", "r");
    fread(&indexes, sizeof(*indexes), counter, fp);
    fclose(fp);
    while (counter--) putchar(characters[indexes[counter] % length]);
    putchar('\n');
}
