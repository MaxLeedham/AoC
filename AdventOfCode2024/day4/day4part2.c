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

    for (i = 0; i < NUM_LINES - 2; i++)
    {
        for (j = 0; j < strlen(array[i]) - 2; j++)
        {
            count += check(array, i, j);
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

int check(char **array, int i, int j)
{
    int a, b;
    char subsection[3][3];

    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            subsection[a][b] = array[i+a][j+b];
        }
    }

    if (subsection[1][1] != 'A')
    {
        return 0;
    }

    if ((subsection[0][0] == 'M' && subsection[2][2] == 'S') || (subsection[0][0] == 'S' && subsection[2][2] == 'M'))
    {
        if ((subsection[2][0] == 'M' && subsection[0][2] == 'S') || (subsection[2][0] == 'S' && subsection[0][2] == 'M'))
        {
            return 1;
        }
    }
    
    return 0;
}
