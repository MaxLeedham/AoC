#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 60
#define NUM_ROWS 57
#define NUM_COLUMNS 57

void read_input(FILE *fp, int **grid);
void free_grid(int **grid);
int find_score(int **grid, int y, int x);

int main(int argc, char **argv)
{
    int i, j, sum=0;
    FILE *fp = fopen("input.txt", "r");
    int **grid = malloc(sizeof(int *) * NUM_ROWS);

    for (i = 0; i < NUM_ROWS; i++)
    {
        grid[i] = malloc(sizeof(int) * NUM_COLUMNS);
    }

    read_input(fp, grid);
    fclose(fp);

    for (i = 0; i < NUM_ROWS; i++)
    {
        for (j = 0; j < NUM_COLUMNS; j++)
        {
            if (grid[i][j] != 0)
            {
                continue;
            }

            sum += find_score(grid, i, j);
        }
    }

    printf("Score: %d\n", sum);

    free_grid(grid);
    return 0;
}

void read_input(FILE *fp, int **grid)
{
    int i, j;
    char buffer[LINE_BUFFER_SIZE];

    for (i = 0; i < NUM_ROWS; i++)
    {
        fgets(buffer, LINE_BUFFER_SIZE, fp);
        buffer[strlen(buffer)-1] = '\0';
        
        for (j = 0; j < strlen(buffer); j++)
        {
            grid[i][j] = buffer[j] - '0';
        }
    }
}

void free_grid(int **grid)
{
    int i;
    for (i = 0; i < NUM_ROWS; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

int find_score(int **grid, int y, int x)
{
    int up = 0, right = 0, down = 0, left = 0;
    
    if (grid[y][x] == 9)
    {
        return 1;
    }

    if (y > 0)
    {
        if (grid[y-1][x] == grid[y][x] + 1)
        {
            up = find_score(grid, y - 1, x);
        }
    }
    if (x < NUM_COLUMNS - 1)
    {
        if (grid[y][x+1] == grid[y][x] + 1)
        {
            right = find_score(grid, y, x + 1);
        }
    }
    if (y < NUM_ROWS - 1)
    {
        if (grid[y+1][x] == grid[y][x] + 1)
        {
            down = find_score(grid, y + 1, x);
        }
    }
    if (x > 0)
    {
        if (grid[y][x-1] == grid[y][x] + 1)
        {
            left = find_score(grid, y, x - 1);
        }
    }

    return up + right + down + left;
}
