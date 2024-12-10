#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 19999

long make_disk_map(char *input, long **disk_map);
long linear_search(long *list, long size, long target);
long last_not_one(long *list, long size);
void defragment(long **disk_map, long size);
long checksum(long *disk_map, long size);

int main(int argc, char **argv)
{
    char input[NUM_CHARS + 1];
    FILE *fp = fopen("input.txt", "r");
    long *disk_map = malloc(sizeof(long));
    long size, sum;

    fgets(input, NUM_CHARS + 1, fp);
    fclose(fp);

    size = make_disk_map(input, &disk_map);
    defragment(&disk_map, size);

    sum = checksum(disk_map, size);
    printf("Sum: %ld\n", sum);

    free(disk_map);
    return 0;
}

long make_disk_map(char *input, long **disk_map)
{
    long i, j, size = 0;
    long id = 0;
    long last_index = 0;

    for (i = 0; i < NUM_CHARS; i++)
    {
        size += input[i] - '0';
        *disk_map = realloc(*disk_map, sizeof(long) * size);

        for (j = 0; j < input[i] - '0'; j++)
        {
            if (i % 2 == 0)
            {
                (*disk_map)[last_index] = id;
            }
            else
            {
                (*disk_map)[last_index] = -1;
            }

            last_index++;
        }

        if (i % 2 == 0)
        {
            id++;
        }
    }

    return size;
}

long linear_search(long *list, long size, long target)
{
    long i;

    for (i = 0; i < size; i++)
    {
        if (list[i] == target)
        {
            return i;
        }
    }

    return -1;
}

long last_not_one(long *list, long size)
{
    long i;

    for (i = size - 1; i >= 0; i--)
    {
        if (list[i] != -1)
        {
            return i;
        }
    }

    return -1;
}

void defragment(long **disk_map, long size)
{
    long front = linear_search(*disk_map, size, -1);
    long back = last_not_one(*disk_map, size);

    while (front < back)
    {
        disk_map[0][front] = disk_map[0][back];
        disk_map[0][back] = -1;

        front = linear_search(*disk_map, size, -1);
        back = last_not_one(*disk_map, size);
    }
}

long checksum(long *disk_map, long size)
{
    long i;
    long sum = 0;

    for (i = 0; i < size; i++)
    {
        if (disk_map[i] == -1)
        {
            return sum;
        }

        sum += i * disk_map[i];
    }

    return sum;
}
