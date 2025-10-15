#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

typedef struct
{
    Token current;
    Token previous;

    bool had_err;
} Parser;

Parser parser;

static void error_at(Token *token, const char *message)
{
    fprintf(stderr, "[line %d] Error", token->line);

    if (token->type == TOKEN_EOF)
    {
        fprintf(stderr, " at end");
    }
    else if (token->type == TOKEN_ERROR)
    {
        // n/a
    }
    else
    {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }

    fprintf(stderr, ": %s\n", message);
    parser.had_err = true;
}

static void error(const char *message)
{
    error_at(&parser.previous, message);
}

static void error_at_current(const char *message)
{
    error_at(&parser.current, message);
}

static void advance()
{
    parser.previous = parser.current;

    for (;;)
    {
        parser.current = scanToken();
        if (parser.current.type != TOKEN_ERROR)
            break;

        errorAtCurrent(parser.current.start);
    }
}

bool compile(const char *src, Chunk *chunk)
{
    init_scanner(src);

    advance();
    expression();
    consume(TOKEN_EOF, "Expect EOE //");

    int line = -1;
    for (;;)
    {
        Token token = scan_token();
        if (token.line != line)
        {
            printf("%4d", token.line);
            line = token.line;
        }
        else
        {
            printf("   |");
        }

        printf("%2d '%.*s'\n", token.type, token.length, token.start);

        if (token.type == TOKEN_EOF)
            break;
    }
}
