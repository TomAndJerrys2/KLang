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

static bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

static bool isDigit(char c)
{
    return c >= '0' && c <= '9';
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

static char peekNext()
{
    if (isAtEnd())
        return '\0';

    return scanner.current[1];
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

        case '\n':
            scanner.line++;
            advance();
            break;

        // skips comments
        case '/':
            if (peekNext() == '/')
            {
                // A comment goes until the end of the line.
                while (peek() != '\n' && !isAtEnd())
                    advance();
            }
            else
            {
                return;
            }
            break;

        default:
            return;
        }
    }
}

static TokenType check_keyword(int start, int length,
                               const char *rest, TokenType type)
{
    if (scanner.current - scanner.start == start + length &&
        memcmp(scanner.start + start, rest, length) == 0)
    {
        return type;
    }

    return TOKEN_IDENTIFIER;
}

static TokenType identifier_type()
{
    switch (scanner.start[0])
    {
    case 'a':
        return check_keyword(1, 2, "nd", TOKEN_AND);
    case 'b':
        check_keyword(1, 4, "lass", TOKEN_BOOL);
    case 'c':
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'l':
                return check_keyword(1, 4, "lass", TOKEN_CLASS);
            case 'h':
                return check_keyword(1, 4, "lass", TOKEN_CHAR);
            }
        }
        break;
    case 'd':
        return check_keyword(1, 4, "lass", TOKEN_DOUBLE);
    case 'e':
        return check_keyword(1, 3, "lse", TOKEN_ELSE);
    case 'f':
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'a':
                return checkKeyword(2, 3, "lse", TOKEN_FALSE);
            case 'o':
                return checkKeyword(2, 1, "r", TOKEN_FOR);
            case 'u':
                return checkKeyword(2, 1, "n", TOKEN_FUNCTION);
            case 'l':
                check_keyword(1, 4, "lass", TOKEN_FLOAT);
            }
        }
        break;
    case 'i':
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'f':
                return check_keyword(1, 1, "f", TOKEN_IF);
            case 'n':
                return check_keyword(1, 1, "f", TOKEN_IF);
            }
        }
        break;
    case 'n':
        return check_keyword(1, 2, "il", TOKEN_NULL);
    case 'o':
        return check_keyword(1, 1, "r", TOKEN_OR);
    case 'p':
        return check_keyword(1, 4, "rint", TOKEN_PRINT);
    case 'r':
        return check_keyword(1, 5, "eturn", TOKEN_RETURN);
    case 's':
        return check_keyword(1, 4, "uper", TOKEN_SUPER);
    case 't':
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'h':
                return checkKeyword(2, 2, "is", TOKEN_THIS);
            case 'r':
                return checkKeyword(2, 2, "ue", TOKEN_TRUE);
            }
        }
        break;
    case 'u':
        if (scanner.current - scanner.start > 1)
        {
            switch (scanner.start[1])
            {
            case 'i':
                return checkKeyword(2, 2, "is", TOKEN_UINT);
            case 'c':
                return checkKeyword(2, 2, "ue", TOKEN_UCHAR);
            case 'd':
                return checkKeyword(2, 2, "ue", TOKEN_UDOUBLE);
            case 'f':
                return checkKeyword(2, 2, "ue", TOKEN_UFLOAT);
            }
        }
        break;
    case 'w':
        return check_keyword(1, 4, "hile", TOKEN_WHILE);
    }

    return TOKEN_IDENTIFIER;
}

static Token identifier()
{
    while (isAlpha(peek()) || isDigit(peek()))
        advance();

    return make_token(identifierType());
}

static Token number()
{
    while (isDigit(peek()))
        advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext()))
    {
        // Consume the ".".
        advance();

        while (isDigit(peek()))
            advance();
    }

    return make_token(TOKEN_NUMBER);
}

static Token string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            scanner.line++;
        advance();
    }

    if (isAtEnd())
        return error_token("Unterminated string //");

    // The closing quote.
    advance();
    return make_token(TOKEN_STRING);
}

static Token scan_token()
{
    skip_whitespace();
    scanner.start = scanner.current;

    if (!is_at_end())
        return make_token(TOKEN_EOF);

    char frame = advance();

    if (is_alpha(frame))
        return identifer();

    if (is_digit(frame))
        return number();

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

    case '"':
        return string();
    }
}