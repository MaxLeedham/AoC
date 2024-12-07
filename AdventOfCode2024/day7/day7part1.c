#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NUM_LINES 850
#define LINE_SIZE 50
#define NUMS_IN_LINE 50

void read_input(FILE *fp, char **lines);
void free_lines(char **lines);
int reach_target(long unsigned *numbers, int n, long unsigned target);
long unsigned check_line(char *line);

int main(int argc, char **argv)
{
    int i;
    long unsigned sum = 0;
    FILE *fp = fopen("input.txt", "r");
    char **lines = malloc(sizeof(char *) * NUM_LINES);

    for (i = 0; i < NUM_LINES; i++)
    {
        lines[i] = malloc(sizeof(char) * LINE_SIZE);
    }
    read_input(fp, lines);
    fclose(fp);

    for (i = 0; i < NUM_LINES; i++)
    {
        sum += check_line(lines[i]);
    }

    printf("Count: %lu\n", sum);
    
    free_lines(lines);
    return 0;
}

void read_input(FILE *fp, char **lines)
{
    int i;
    for (i = 0; i < NUM_LINES; i++)
    {
        fgets(lines[i], LINE_SIZE, fp);
        lines[i][strlen(lines[i]) - 1] = '\0';
    }
}

void free_lines(char **lines)
{
    int i;
    for (i = 0; i < NUM_LINES; i++)
    {
        free(lines[i]);
    }
    free(lines);
}

int reach_target(long unsigned *numbers, int n, long unsigned target)
{
    int add, multiply;
    long unsigned new_numbers[NUMS_IN_LINE];

    if (n == 1)
    {
        return numbers[0] == target;
    }

    memcpy(new_numbers, numbers, sizeof(long unsigned) * n);
    new_numbers[1] = numbers[0] + numbers[1];
    add = reach_target(&(new_numbers[1]), n-1, target);

    new_numbers[1] = numbers[0] * numbers[1];
    multiply = reach_target(&(new_numbers[1]), n-1, target);

    return add || multiply;
}

long unsigned check_line(char *line)
{
    int n = 0;
    long unsigned numbers[NUMS_IN_LINE];
    long unsigned target = atol(strtok(line, ": "));
    char *token;

    while ((token = strtok(NULL, " ")))
    {
        numbers[n++] = atol(token);
    }

    if (reach_target(numbers, n, target))
    {
        return target;
    }

    return 0;
}
