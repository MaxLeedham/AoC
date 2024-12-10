#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_LINES 1000
#define BUFFER_SIZE 256

int main(int argc, char **argv)
{
    FILE *fp = fopen("input.txt", "r");
    char buffer[BUFFER_SIZE];
    int numbers[BUFFER_SIZE];
    int count = 0;

    while (fgets(buffer, BUFFER_SIZE, fp))
    {
        char *number;
        int n = 0, i = 0, increasing;

        numbers[n++] = atoi(strtok(buffer, " "));
        while ((number = strtok(NULL, " ")))
        {
            numbers[n++] = atoi(number);
        }

        increasing = numbers[1] > numbers[0];

        for (i = 1; i < n; i++)
        {
            int difference = abs(numbers[i] - numbers[i - 1]);

            if (difference < 1 || difference > 3)
            {
                break;
            }

            if (numbers[i] == numbers[i - 1])
            {
                if (i == n - 1)
                {
                    count++;
                }
            }
            else if (numbers[i] > numbers[i - 1])
            {
                if (!increasing)
                {
                    break;
                }

                if (i == n - 1)
                {
                    count++;
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
                    count++;
                }
            }
        }
    }

    printf("Count: %d\n", count);

    return 0;
}