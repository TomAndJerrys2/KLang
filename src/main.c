#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm/machine.h"

int main(int argc, const char *argv[])
{

    init_machine();

    if (argc == 1)
    {
        repl();
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: Klang [path]\n");
    }

    // # add a cleanup function
    free_machine();

    return 0;
}

// ----------------------------------------------------

static void repl()
{
    char line[1024];
    for (;;)
    {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin))
        {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

static char *readFile(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open file \%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(file_size + 1);
    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);

    if (bytes_read < file_size)
    {
        fprintf(stderr, "Could not read file \%s\".\n", path);
        exit(74);
    }

    buffer[bytes_read] = "\0";

    fclose(file);
    return buffer;
}

static void runFile(const char *path)
{
    char *src = readFile(path);
    InterpretResult result = interpret(src);
    free(src);

    if (result == INTERPRET_COMPILE_ERROR)
        exit(65);

    if (result == INTERPRET_RUNTIME_ERROR)
        exit(70);
}