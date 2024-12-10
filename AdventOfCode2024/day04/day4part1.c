#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 140
#define CHARS_PER_LINE 142

void free_input_array(char **array);
int check(char **array, int i, int j);

int main(int argc, char **argv)
{
    FILE *fp = fopen("input.txt", "r");
    int i, j, count = 0;
    char **array = malloc(sizeof(char *) * NUM_LINES);

    for (i = 0; i < NUM_LINES; i++)
    {
        array[i] = malloc(sizeof(char) * CHARS_PER_LINE + 1);
        
        fgets(array[i], CHARS_PER_LINE, fp);
        array[i][strlen(array[i])-1] = '\0';
    }
    fclose(fp);

    for (i = 0; i < NUM_LINES; i++)
    {
        for (j = 0; j < strlen(array[i]); j++)
        {
            if (array[i][j] == 'X')
            {
                count += check(array, i, j);
            }
        }
    }

    printf("Count: %d\n", count);

    free_input_array(array);
    return 0;
}

void free_input_array(char **array)
{
    int i;
    for (i = 0; i < NUM_LINES; i++)
    {
        free(array[i]);
    }
    free(array);
}

/* Just a bunch of if statements */
int check(char **array, int i, int j)
{
    int count = 0;

    if (j >= 3)
    {
        if (array[i][j] == 'X' && array[i][j-1] == 'M' && array[i][j-2] == 'A' && array[i][j-3] == 'S')
        {
            count++;
        }
    }

    if (j <= strlen(array[i]) - 4)
    {
        if (array[i][j] == 'X' && array[i][j+1] == 'M' && array[i][j+2] == 'A' && array[i][j+3] == 'S')
        {
            count++;
        }
    }

    if (i >= 3)
    {
        if (array[i][j] == 'X' && array[i-1][j] == 'M' && array[i-2][j] == 'A' && array[i-3][j] == 'S')
        {
            count++;
        }

        if (j <= strlen(array[i]) - 4)
        {
            if (array[i][j] == 'X' && array[i-1][j+1] == 'M' && array[i-2][j+2] == 'A' && array[i-3][j+3] == 'S')
            {
                count++;
            }
        }

        if (j >= 3)
        {
            if (array[i][j] == 'X' && array[i-1][j-1] == 'M' && array[i-2][j-2] == 'A' && array[i-3][j-3] == 'S')
            {
                count++;
            }
        }
    }

    if (i <= NUM_LINES - 4)
    {
        if (array[i][j] == 'X' && array[i+1][j] == 'M' && array[i+2][j] == 'A' && array[i+3][j] == 'S')
        {
            count++;
        }

        if (j <= strlen(array[i]) - 4)
        {
            if (array[i][j] == 'X' \
                && array[i+1][j+1] == 'M' \
                && array[i+2][j+2] == 'A' \
                && array[i+3][j+3] == 'S')
            {
                count++;
            }
        }

        if (j >= 3)
        {
            if (array[i][j] == 'X' && array[i+1][j-1] == 'M' && array[i+2][j-2] == 'A' && array[i+3][j-3] == 'S')
            {
                count++;
            }
        }
    }

    return count;
}
