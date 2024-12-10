#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_LINES 1000
#define BUFFER_SIZE 256

int check(int *numbers, int n);

int main(int argc, char **argv)
{
    FILE *fp = fopen("input.txt", "r");
    char buffer[BUFFER_SIZE];
    int numbers[BUFFER_SIZE];
    int one_removed[BUFFER_SIZE];
    int count = 0;

    while (fgets(buffer, BUFFER_SIZE, fp))
    {
        char *number;
        int n = 0, i = 0;

        numbers[n++] = atoi(strtok(buffer, " "));
        while ((number = strtok(NULL, " ")))
        {
            numbers[n++] = atoi(number);
        }

        if (check(numbers, n))
        {
            count++;
            continue;
        }

        for (i = 0; i < n; i++)
        {
            int j;

            for (j = 0; j < i; j++)
            {
                one_removed[j] = numbers[j];
            }

            for (j = i + 1; j < n; j++)
            {
                one_removed[j - 1] = numbers[j];
            }

            if (check(one_removed, n-1))
            {
                count++;
                break;
            }
        }
    }

    printf("Count %d\n", count);

    return 0;
}

int check(int *numbers, int n)
{
    int increasing, i;

    if (numbers[1] != numbers[2])
    {
        increasing = numbers[1] > numbers[0];
    }
    else
    {
        increasing = numbers[2] > numbers[1];
    }

    for (i = 1; i < n; i++)
    {
        int difference = abs(numbers[i] - numbers[i - 1]);

        if (difference < 1 || difference > 3)
        {
            break;
        }
        
        if (numbers[i] > numbers[i - 1])
        {
            if (!increasing)
            {
                break;
            }

            if (i == n - 1)
            {
                return 1;
            }
        }
        else
        {
            if (increasing)
            {
                break;
            }

            if (i == n - 1)
            {
                return 1;
            }
        }
    }

    return 0;
}