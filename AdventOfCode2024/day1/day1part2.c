#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_LINES 1000
#define MAX_LINE_SIZE 256

int int_compare(const void *a, const void *b);

int main(int argc, char **argv)
{
    int list1[NUM_LINES];
    int list2[NUM_LINES];
    int i, j, similarity_score = 0;

    FILE *fp = fopen("day1/input.txt", "r");

    for (i = 0; i < NUM_LINES; i++)
    {
        char buffer[MAX_LINE_SIZE];

        fgets(buffer, MAX_LINE_SIZE, fp);

        list1[i] = atoi(strtok(buffer, "   "));
        list2[i] = atoi(strtok(NULL, "   "));
    }
    fclose(fp);

    for (i = 0; i < NUM_LINES; i++)
    {
        int count = 0;
        for (j = 0; j < NUM_LINES; j++)
        {
            if (list1[i] == list2[j])
            {
                count++;
            }
        }

        similarity_score += list1[i] * count;
    }

    printf("%d\n", similarity_score);

    return 0;
}

int int_compare(const void *a, const void *b)
{
    if (*((int *)a) < *((int *)b))
    {
        return -1;
    }
    if (*((int *)a) == *((int *)b))
    {
        return 0;
    }
    if (*((int *)a )> *((int *)b))
    {
        return 1;
    }

    return 0;
}