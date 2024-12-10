#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 256
#define NUM_RULES 1176
#define NUM_UPDATES 202

int linear_search(int *array, int length, int target);
void free_rules(int **rules);
void read_rules(FILE *fp, int **rules);
void read_updates(FILE *fp, int **rules);

int main(int argc, char **argv)
{
    int i;
    char buffer[LINE_BUFFER_SIZE];
    FILE *fp = fopen("input.txt", "r");
    int **rules = malloc(sizeof(int *) * NUM_RULES);

    for (i = 0; i < NUM_RULES; i++)
    {
        rules[i] = malloc(sizeof(int) * 2);
    }

    read_rules(fp, rules);
    fgets(buffer, LINE_BUFFER_SIZE, fp);
    read_updates(fp, rules);

    fclose(fp);
    free_rules(rules);

    return 0;
}

int linear_search(int *array, int length, int target)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if (array[i] == target)
        {
            return i;
        }
    }
    return -1;
}

void free_rules(int **rules)
{
    int i;
    for (i = 0; i < NUM_RULES; i++)
    {
        free(rules[i]);
    }
    free(rules);
}

void read_rules(FILE *fp, int **rules)
{
    char buffer[LINE_BUFFER_SIZE];
    int i;

    for (i = 0; i < NUM_RULES; i++)
    {
        fgets(buffer, LINE_BUFFER_SIZE, fp);
        rules[i][0] = atoi(strtok(buffer, "|"));
        rules[i][1] = atoi(strtok(NULL, "|"));
    }
}

void read_updates(FILE *fp, int **rules)
{
    int i, sum = 0;
    char buffer[LINE_BUFFER_SIZE];
    int numbers[NUM_UPDATES];

    for (i = 0; i < NUM_UPDATES; i++)
    {
        int j, length = 1;
        char *number;
        int valid = 1;

        fgets(buffer, LINE_BUFFER_SIZE, fp);
        numbers[0] = atoi(strtok(buffer, ","));

        while ((number = strtok(NULL, ",")))
        {
            numbers[length++] = atoi(number);
        }

        for (j = 0; j < NUM_RULES; j++)
        {
            int index1 = linear_search(numbers, length, rules[j][0]);
            int index2 = linear_search(numbers, length, rules[j][1]);
            
            if (index1 != -1 && index2 != -1)
            {
                if (index1 > index2)
                {
                    valid = 0;
                    break;
                }
            }
        }

        if (valid)
        {
            sum += numbers[length/2];
        }
    }

    printf("Sum: %d\n", sum);
}
