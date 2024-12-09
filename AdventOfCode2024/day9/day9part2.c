#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 19999

long make_disk_map(char *input, long **disk_map);
long linear_search(long *list, long size, long target, int start);
long reverse_linear_search_kinda(long *list, long size, int less_than);
void defragment(long **disk_map, long size);
long checksum(long *disk_map, long size);
int check_concurrent_value(long *disk_map, long size, long index, int multiplier);

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

long linear_search(long *list, long size, long target, int start)
{
    long i;

    for (i = start; i < size; i++)
    {
        if (list[i] == target)
        {
            return i;
        }
    }

    return -1;
}

long reverse_linear_search_kinda(long *list, long size, int less_than)
{
    long i;

    for (i = size - 1; i >= 0; i--)
    {
        if (list[i] != -1 && list[i] < less_than)
        {
            return i;
        }
    }

    return -1;
}

void defragment(long **disk_map, long size)
{
    long front = linear_search(*disk_map, size, -1, 0);
    long back = reverse_linear_search_kinda(*disk_map, size, disk_map[0][size-1] + 1);
    int front_length = check_concurrent_value(*disk_map, size, front, 1);
    int back_length = check_concurrent_value(*disk_map, size, back, -1);
    int i;

    while (front < back)
    {
        int old_back = disk_map[0][back];
        front = linear_search(*disk_map, size, -1, 0);
        front_length = check_concurrent_value(*disk_map, size, front, 1);

        while (front != -1 && front < back)
        {
            if (front_length >= back_length)
            {
                for (i = 0; i < back_length; i++)
                {
                    disk_map[0][front+i] = disk_map[0][back-i];
                    disk_map[0][back-i] = -1;
                }

                break;
            }
            else
            {
                front = linear_search(*disk_map, size, -1, front + front_length);
                front_length = check_concurrent_value(*disk_map, size, front, 1);
            }
        }

        front = linear_search(*disk_map, size, -1, 0);
        back = reverse_linear_search_kinda(*disk_map, size, old_back);

        front_length = check_concurrent_value(*disk_map, size, front, 1);
        back_length = check_concurrent_value(*disk_map, size, back, -1);
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
            continue;
        }

        sum += i * disk_map[i];
    }

    return sum;
}

int check_concurrent_value(long *disk_map, long size, long index, int multiplier)
{
    int i;
    int count = 0;

    for (i = index; i < size && i >= 0; i += multiplier)
    {
        if (disk_map[i] != disk_map[index])
        {
            return count;
        }

        count++;
    }

    return count;
}
