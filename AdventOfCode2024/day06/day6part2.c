/*
This is INCREDIBLY INCREDIBLY slow code

It took 4 and a half hours on my laptop for it to finish on the input file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOOP_COUNT 100000

#define NUM_LINES 130
#define LINE_SIZE 150

typedef struct position {
    int x;
    int y;
    char type;
} position;

void free_map(char **map);
void read_input(FILE *fp, char **map);
position find_position(char **map);
int loop(char **map, int x, int y);
int count_loops(char **map);
char **copy_map(char **map);

int main(int argc, char **argv)
{
    int i, count;
    FILE *fp = fopen("input.txt", "r");
    char **map = malloc(sizeof(char *) * NUM_LINES);

    for (i = 0; i < NUM_LINES; i++)
    {
        map[i] = malloc(sizeof(char) * LINE_SIZE);
    }

    read_input(fp, map);

    count = count_loops(map);
    printf("%d Number of loops\n", count);

    free_map(map);
    fclose(fp);

    return 0;
}

void free_map(char **map)
{
    int i;
    for (i = 0; i < NUM_LINES; i++)
    {
        free(map[i]);
    }
    free(map);
}

void read_input(FILE *fp, char **map)
{
    int i;

    for (i = 0; i < NUM_LINES; i++)
    {
        fgets(map[i], LINE_SIZE, fp);
        map[i][strlen(map[i])-1] = '\0';
    }
}

position find_position(char **map)
{
    position found = {-1, -1};
    int i, j;

    for (i = 0; i < NUM_LINES; i++)
    {
        for (j = 0; j < strlen(map[i]); j++)
        {
            switch (map[i][j])
            {
                case '^':
                    found.y = i;
                    found.x = j;
                    found.type = '^';
                    return found;
                case '>':
                    found.y = i;
                    found.x = j;
                    found.type = '>';
                    return found;
                case '<':
                    found.y = i;
                    found.x = j;
                    found.type = '<';
                    return found;
                case 'v':
                    found.y = i;
                    found.x = j;
                    found.type = 'v';
                    return found;
            }
        }
    }

    return found;
}

int loop(char **map, int x, int y)
{
    position location = find_position(map);
    int count = 0;
    int full_count = 0;

    while (location.x != -1 || location.y != -1)
    {
        if (full_count == LOOP_COUNT)
        {
            return full_count;
        }

        switch (location.type)
        {
            case '^':
                if (location.y != 0)
                {
                    if (map[location.y - 1][location.x] == '#')
                    {
                        map[location.y][location.x] = '>';
                        location.type = '>';
                    }
                    else
                    {

                        if (map[location.y - 1][location.x] != 'X')
                        {
                            count++;
                        }
                        map[location.y][location.x] = 'X';
                        map[location.y - 1][location.x] = '^';
                        location.y--;
                    }

                    full_count++;
                    continue;
                }
                else
                {
                    return count + 1;
                }
            case '>':
                if (location.x != strlen(map[location.y]) - 1)
                {
                    if (map[location.y][location.x + 1] == '#')
                    {
                        map[location.y][location.x] = 'v';
                        location.type = 'v';
                    }
                    else
                    {
                        if (map[location.y][location.x + 1] != 'X')
                        {
                            count++;
                        }
                        map[location.y][location.x] = 'X';
                        map[location.y][location.x + 1] = '>';
                        location.x++;
                    }

                    full_count++;
                    continue;
                }
                else
                {
                    return count + 1;
                }
            case 'v':
                if (location.y != NUM_LINES - 1)
                {
                    if (map[location.y + 1][location.x] == '#')
                    {
                        map[location.y][location.x] = '<';
                        location.type = '<';
                    }
                    else
                    {
                        if (map[location.y + 1][location.x] != 'X')
                        {
                            count++;
                        }
                        map[location.y][location.x] = 'X';
                        map[location.y + 1][location.x] = 'v';
                        location.y++;
                    }

                    full_count++;
                    continue;
                }
                else
                {
                    return count + 1;
                }

            case '<':
                if (location.x != 0)
                {
                    if (map[location.y][location.x - 1] == '#')
                    {
                        map[location.y][location.x] = '^';
                        location.type = '^';
                    }
                    else
                    {
                        if (map[location.y][location.x - 1] != 'X')
                        {
                            count++;
                        }
                        map[location.y][location.x] = 'X';
                        map[location.y][location.x - 1] = '<';
                        location.x--;
                    }

                    full_count++;
                    continue;
                }
                else
                {
                    return count + 1;
                }
        }
    }

    return count;
}

int count_loops(char **map)
{
    int loops = 0;
    int i, j;
    char **copy = copy_map(map);

    for (i = 0; i < NUM_LINES; i++)
    {
        for (j = 0; j < strlen(map[i]); j++)
        {
            int moves = 0;
            char **copy;

            if (map[i][j] == '#' || map[i][j] == '^' || map[i][j] == '>' || map[i][j] == 'v' || map[i][j] == '<')
            {
                continue;
            }

            copy = copy_map(map);
            copy[i][j] = '#';

            moves = loop(copy, i, j);

            free_map(copy);

            if (moves == LOOP_COUNT)
            {
                loops++;
            }
        }
    }

    free_map(copy);
    return loops;
}

char **copy_map(char **map)
{
    int i;
    char **copy = malloc(sizeof(char *) * NUM_LINES);

    for (i = 0; i < NUM_LINES; i++)
    {
        copy[i] = malloc(sizeof(char) * strlen(map[i]) + 1);
        strcpy(copy[i], map[i]);
    }

    return copy;
}
