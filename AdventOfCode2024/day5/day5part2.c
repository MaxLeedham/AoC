#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LINE_BUFFER_SIZE 256
#define NUM_RULES 1176
#define NUM_UPDATES 202

int linear_search(int *array, int length, int target);
void free_rules(int **rules);
void read_rules(FILE *fp, int **rules);
void read_updates(FILE *fp, int **rules);
int check_update(int *update, int update_length, int **rules);
void sort(int *numbers, int length, int **rules);

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
        int length = 1;
        int j;
        char *number;

        fgets(buffer, LINE_BUFFER_SIZE, fp);
        numbers[0] = atoi(strtok(buffer, ","));

        while ((number = strtok(NULL, ",")))
        {
            numbers[length++] = atoi(number);
        }

        if (check_update(numbers, length, rules))
        {
            continue;
        }

        /* "Sort" the numbers so it follows the rules */
        sort(numbers, length, rules);

        for (j = 0; j < length; j++)
        {
            printf("%d ", numbers[j]);
        }
        printf("\n\n\n\n\n");

        sum += numbers[length/2];
    }

    printf("Sum: %d\n", sum);
}

int check_update(int *update, int update_length, int **rules)
{
    int i;
    for (i = 0; i < NUM_RULES; i++)
    {
        int index1 = linear_search(update, update_length, rules[i][0]);
        int index2 = linear_search(update, update_length, rules[i][1]);
        
        if (index1 != -1 && index2 != -1)
        {
            if (index1 > index2)
            {
                return 0;
            }
        }
    }

    return 1;
}

void sort(int *numbers, int length, int **rules)
{
    int temp, i, j, k;

    for (i = 0; i < length; i++)
    {
        int swap = 0;
        for (j = 0; j < length; j++)
        {
            if (i == j)
            {
                continue;
            }

            for (k = 0; k < NUM_RULES; k++)
            {
                if ((numbers[i] == rules[k][0] && numbers[j] == rules[k][1]))
                {
                    if (j > i)
                    {
                        /* SWAP */
                        swap = 1;

                        temp = numbers[i];
                        numbers[i] = numbers[j];
                        numbers[j] = temp;

                        i--;
                        break;
                    }
                }
                else if (numbers[j] == rules[k][0] && numbers[i] == rules[k][1])
                {
                    if (i > j)
                    {
                        /* SWAP */
                        swap = 1;

                        temp = numbers[i];
                        numbers[i] = numbers[j];
                        numbers[j] = temp;

                        i--;
                        break;
                    }
                }
            }
            if (swap)
            {
                break;
            }
        }
    }
}