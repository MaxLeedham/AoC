#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LINES 50
#define LINE_LENGTH 60
#define CHARS_PER_LINE 50

void read_input(FILE *fp, char **lines);
void free_lines(char **lines);
int find_antinodes(char **lines, char **antinodes);

int main(int argc, char **argv)
{
    int i, count;
    FILE *fp = fopen("input.txt", "r");
    char **lines = malloc(sizeof(char *) * NUM_LINES);
    char **antinodes = malloc(sizeof(char *) * NUM_LINES);

    for (i = 0; i < NUM_LINES; i++)
    {
        lines[i] = malloc(sizeof(char) * LINE_LENGTH);
        antinodes[i] = malloc(sizeof(char *) * LINE_LENGTH);
        memset(antinodes[i], '.', CHARS_PER_LINE);
        antinodes[i][50] = '\0';
    }

    read_input(fp, lines);
    fclose(fp);

    count = find_antinodes(lines, antinodes);
    printf("Found %d antinodes\n", count);

    free_lines(lines);
    free_lines(antinodes);
    return 0;
}

void read_input(FILE *fp, char **lines)
{
    int i;
    for (i = 0; i < NUM_LINES; i++)
    {
        fgets(lines[i], LINE_LENGTH, fp);
        lines[i][strlen(lines[i])-1] = '\0';
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

int find_antinodes(char **lines, char **antinodes)
{
    int i, x, y;
    int count = 0;

    for (i = '0'; i <= 'z'; i++)
    {
        if ((i > '9' && i < 'A') || (i > 'Z' && i < 'a'))
        {
            continue;
        }

        for (y = 0; y < NUM_LINES; y++)
        {
            for (x = 0; x < strlen(lines[y]); x++)
            {
                int x2, y2;

                if (lines[y][x] == '.')
                {
                    continue;
                }

                for (y2 = 0; y2 < NUM_LINES; y2++)
                {
                    for (x2 = 0; x2 < strlen(lines[y2]); x2++)
                    {
                        if (y == y2 && x == x2)
                        {
                            continue;
                        }

                        if (lines[y][x] == lines[y2][x2])
                        {
                            int y_difference = y2 - y;
                            int x_difference = x2 - x;
                            int repeat;

                            for (repeat = 0; repeat < 50; repeat++)
                            {

                                if (x2 + (repeat * x_difference) < 0 || x2 + (repeat * x_difference) >= strlen(lines[y]))
                                {
                                    break;
                                }
                                if (y2 + (repeat * y_difference) < 0 || y2 + (repeat * y_difference) >= NUM_LINES)
                                {
                                    break;
                                }

                                if (antinodes[y2 + (repeat * y_difference)][x2 + (repeat * x_difference)] != '#')
                                {
                                    antinodes[y2 + (repeat * y_difference)][x2 + (repeat * x_difference)] = '#';
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return count;
}
