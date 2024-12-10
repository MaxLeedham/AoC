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
    int i, sum = 0;

    FILE *fp = fopen("day1/input.txt", "r");

    for (i = 0; i < NUM_LINES; i++)
    {
        char buffer[MAX_LINE_SIZE];

        fgets(buffer, MAX_LINE_SIZE, fp);

        list1[i] = atoi(strtok(buffer, "   "));
        list2[i] = atoi(strtok(NULL, "   "));
    }
    fclose(fp);

    qsort(list1, NUM_LINES, sizeof(int), int_compare);
    qsort(list2, NUM_LINES, sizeof(int), int_compare);

    for (i = 0; i < NUM_LINES; i++)
    {
        if (list1[i] > list2[i])
        {
            printf("%d - %d = %d\n", list1[i], list2[i], list1[i] - list2[i]);
            sum += list1[i] - list2[i];
        }
        else
        {
            printf("%d - %d = %d\n", list2[i], list1[i], list2[i] - list1[i]);
            sum += list2[i] - list1[i];
        }
    }

    printf("%d\n", sum);

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