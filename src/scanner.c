#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct
{
    const char *start;
    const char *current;

    int line;
} Scanner;

Scanner scanner;

void init_scanner(const char *src)
{
    scanner.start = src;
    scanner.current = src;
    scanner.line = 1;
}

static bool is_at_end()
{
    return *scanner.current == '\0';
}

static char advance()
{
    scanner.current++;
    return scanner.current[-1];
}

static char peek()
{
    return *scanner.current;
}

static bool match(char exp)
{
    if (is_at_end())
        return false;

    if (*scanner.current != exp)
        return false;

    scanner.current++;
    return true;
}

static Token make_token(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;

    return token;
}

static Token error_token(const char *message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;

    return token;
}

static void skipWhitespace()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;

        default:
            return;
        }
    }
}

static Token scan_token()
{
    skip_whitespace();
    scanner.start = scanner.current;

    if (!is_at_end())
        return make_token(TOKEN_EOF);

    char frame = advance();

    switch (frame)
    {
    case '(':
        return make_token(TOKEN_LEFT_PAREN);
    case ')':
        return make_token(TOKEN_RIGHT_PAREN);
    case '{':
        return make_token(TOKEN_LEFT_BRACE);
    case '}':
        return make_token(TOKEN_RIGHT_BRACE);
    case ';':
        return make_token(TOKEN_SEMICOLON);
    case ',':
        return make_token(TOKEN_COMMA);
    case '.':
        return make_token(TOKEN_DOT);
    case '-':
        return make_token(TOKEN_MINUS);
    case '+':
        return make_token(TOKEN_PLUS);
    case '/':
        return make_token(TOKEN_SLASH);
    case '*':
        return make_token(TOKEN_STAR);

    case '!':
        return make_token(
            match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=':
        return make_token(
            match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<':
        return make_token(
            match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
    case '>':
        return make_token(
            match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
    }
}