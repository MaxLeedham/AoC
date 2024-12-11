#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STARTING_STONES 8
#define ITERATIONS 25

void print_stones(long *stones, int length);
int blink(long stone, int iterations);

int main(int argc, char **argv)
{
    FILE *fp = fopen("input.txt", "r");
    int i, result;
    char line[40];
    
    fgets(line, 40, fp);
    fclose(fp);

    result = blink(atoi(strtok(line, " ")), ITERATIONS);

    for (i = 1; i < STARTING_STONES; i++)
    {
        result += blink(atoi(strtok(NULL, " ")), ITERATIONS);
    }

    printf("Number of stones: %d\n", result);

    return 0;
}

void print_stones(long *stones, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%ld ", stones[i]);
    }
    printf("\n");
}

int blink(long stone, int iterations)
{
    int num_digits;

    if (iterations <= 0)
    {
        return 1;
    }

    if (stone == 0)
    {
        return blink(1, iterations-1);
    }

    num_digits = log10(stone) + 1;
    if (num_digits < 0)
    {
        num_digits = 1;
    }

    else if (num_digits % 2 == 0)
    {
        long left_half = stone / (int) pow(10, num_digits / 2);
        long right_half = stone - (left_half * (int) pow(10, num_digits / 2));
    
        return blink(left_half, iterations-1) + blink(right_half, iterations-1);
    }

    return blink(stone * 2024, iterations-1);
}
