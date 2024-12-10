#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_SIZE 3520
#define MAX_FORMATTED_LINE_SIZE 256

void reformat_input(FILE *read_fp, FILE *write_fp);

int main(int argc, char **argv)
{
    FILE *input_fp = fopen("input.txt", "r");
    FILE *format_fp = fopen("formatted.txt", "w+");
    char buffer[MAX_FORMATTED_LINE_SIZE];
    int sum = 0;
    int enabled = 1;

    reformat_input(input_fp, format_fp);
    fflush(format_fp);
    rewind(format_fp);

    while (fgets(buffer, MAX_FORMATTED_LINE_SIZE, format_fp))
    {
        regex_t regex_buffer;
        int value;
        
        if (strcmp(buffer, "do()\n") == 0)
        {
            enabled = 1;
            continue;
        }
        else if (strcmp(buffer, "don't()\n") == 0)
        {
            enabled = 0;
            continue;
        }

        if (enabled == 0)
        {
            continue;
        }

        buffer[strlen(buffer)-1] = '\0';

        if (regcomp(&regex_buffer, "^mul\\([0-9]{1,3},[0-9]{1,3}\\)$", REG_EXTENDED) != 0)
        {
            fprintf(stderr, "Failed to compile the regex\n");
            return 1;
        }

        if ((value = regexec(&regex_buffer, buffer, 0, NULL, 0)) == 0)
        {
            int number1 = atoi(&(buffer[4]));
            int number2 = atoi(strchr(buffer, ',')+1);

            sum += number1 * number2;
        }

        regfree(&regex_buffer);
    }

    fclose(format_fp);
    fclose(input_fp);

    printf("Sum: %d\n", sum);

    return 0;
}

void reformat_input(FILE *read_fp, FILE *write_fp)
{
    char buffer[MAX_LINE_SIZE];

    while (fgets(buffer, MAX_LINE_SIZE, read_fp))
    {
        int i;
        for (i = 0; i < strlen(buffer); i++)
        {
            if (buffer[i] == ')')
            {
                fprintf(write_fp, "%c\n", buffer[i]);
            }
            else if (buffer[i] == 'm')
            {
                fprintf(write_fp, "\n%c", buffer[i]);
            }
            else if (buffer[i] == 'd')
            {
                fprintf(write_fp, "\n%c", buffer[i]);
            }
            else
            {
                fprintf(write_fp, "%c", buffer[i]);
            }
        }
    }
}
