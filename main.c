#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TEMP "temp1daf3dasfadg234r41asacfsd.tmp"

void appendLF(char *src, char *dst);
bool create_copy = false;
bool crlf_2_lf = true;

int main(int argc, char *argv[])
{
    FILE *original_file;
    FILE *new_file;

    // check if strings in argv contains -- or - and increment counter
    int counter = 0;
    for (int i = 1; i < argc; i++)
    {
        if (strncmp(argv[i], "--", 2) == 0 || strncmp(argv[i], "-", 1) == 0)
        {
            counter++;
        }
    }
    // counter --> total special arguments
    // argc-1 - counter --> total filenames

    // arrays to store filenames and special arguments
    char *filenames[argc - 1 - counter];
    char *special_arguments[counter];

    // fill arrays with data
    for (int i = 1, j = 0, k = 0; i < argc; i++)
    {
        if (strncmp(argv[i], "--", 2) == 0 || strncmp(argv[i], "-", 1) == 0)
        {
            special_arguments[j] = argv[i];
            j++;
        }
        else
        {
            filenames[k] = argv[i];
            k++;
        }
    }
    for (int i = 0; i < counter; i++)
    {
        // check for valid special arguments
        // if not valid, print error message and exit
        // valid special arguments: --help, --version, --create-copy, --crlf
        if (strncmp(special_arguments[i], "--help", 6) == 0)
        {
            printf("A command line tool to convert CRLF text files to LF text files.\n\nUsage: ./CRLF2LF [OPTION]... [FILE]...\n\nConvert CRLF text files to LF text files.\n\nOptions:\n--help\t\tdisplay this help and exit\n--version\toutput version information and exit\n--create-copy\tcreate a copy of the original file\n--crlf\t\tconvert LF to CRLF\n");
            exit(0);
        }
        else if (strncmp(special_arguments[i], "--version", 9) == 0)
        {
            printf("CRLF2LF 1.0\n");
            exit(0);
        }
        else if (strncmp(special_arguments[i], "--create-copy", 13) == 0)
        {
            create_copy = true;
        }
        else if (strncmp(special_arguments[i], "--crlf", 6) == 0)
        {
            crlf_2_lf = false;
        }
        else
        {
            printf("Invalid argument: %s\n", special_arguments[i]);
            exit(1);
        }
    }
    // check if there are any filenames
    if (argc - 1 - counter == 0)
    {
        printf("No filenames given\n");
        exit(1);
    }

    // open files and check if they exist
    for (int i = 0; i < argc - 1 - counter; i++)
    {
        original_file = fopen(filenames[i], "r");
        if (original_file == NULL)
        {
            printf("File \"%s\" does not exist\n", filenames[i]);
            exit(1);
        }
        fclose(original_file);
    }

    // if create-copy is true, create new file with appended LF to original file by calling appendLF
    for (int i = 0; i < argc - 1 - counter; i++)
    {
        original_file = fopen(filenames[i], "rb");
        char new_filename[strlen(filenames[i]) + 3];

        if (create_copy)
        {
            appendLF(filenames[i], new_filename);
            new_file = fopen(new_filename, "wb");
        }
        else
            new_file = fopen(TEMP, "wb");

        char buffer = 0;

        // if crlf_2_lf is true, convert CRLF to LF else convert LF to CRLF
        while (true)
        {
            buffer = fgetc(original_file);
            if (buffer == EOF)
            {
                break;
            }
            if (crlf_2_lf)
            {
                if (buffer == '\r')
                    buffer = fgetc(original_file);
                else
                    ;
            }
            else
            {
                if (buffer == '\r')
                {
                    fputc(buffer, new_file);
                    buffer == fgetc(original_file);
                }
                else if (buffer == '\n')
                {
                    fputc('\r', new_file);
                }
                else
                    ;
            }
            fputc(buffer, new_file);
        }
        fclose(original_file);
        fclose(new_file);
        // if !create_copy, delete original file and rename temp.txt to original file name
        if (!create_copy)
        {
            remove(filenames[i]);
            rename(TEMP, filenames[i]);
        }
    }
}

// append LF to filename no extension and append original extension
// if no extension was provided originally, do not append extension
void appendLF(char *source, char *destination)
{
    int i = 0;
    printf("length of source: %d\n", strlen(source));
    printf("length of destination: %d\n", strlen(destination));
    printf("source: %s\n", source);
    printf("destination: %s\n", destination);

    while (source[i] != '.')
    {
        if (i == strlen(source))
        {
            break;
        }
        destination[i] = source[i];
        i++;
    }
    destination[i] = 'C';
    i++;
    destination[i] = 'Z';
    i++;
    // while (i != strlen(source)+3)
    while (source[i - 2] != '\0')
    {
        destination[i] = source[i - 2];
        i++;
    }
    destination[i] = '\0';
}
