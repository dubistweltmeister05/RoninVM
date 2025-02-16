#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "rvasmlexer.h"

char *open_file(char *file_path, int *length)
{

    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        fprintf(stderr, "ERROR: File does not exist %s\n", file_path);
        exit(1);
    }
    char *current = {0};

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    fseek(file, 0, SEEK_SET);

    current = malloc(sizeof(char) * *length);
    fread(current, 1, *length, file);
    if (!current)
    {
        fprintf(stderr, "ERROR: Could not read from file %s\n", file_path);
        exit(1);
    }

    fclose(file);

    return current;
}

void print_token(Token token)
{
    switch (token.type)
    {
    case TYPE_NONE:
        printf("none\n");
        break;

    case TYPE_NOP:
        printf("nop\n");
        break;

    case TYPE_PUSH:
        printf("push\n");
        break;

    case TYPE_POP:
        printf("pop\n");
        break;

    case TYPE_ADD:
        printf("add\n");
        break;

    case TYPE_SUB:
        printf("sub\n");
        break;

    case TYPE_MUL:
        printf("mul\n");
        break;

    case TYPE_DUP:
        printf("dup\n");
        break;

    case TYPE_INDUP:
        printf("indup\n");
        break;

    case TYPE_SWAP:
        printf("swap\n");
        break;

    case TYPE_INSWAP:
        printf("inswap\n");
        break;

    case TYPE_DIV:
        printf("div\n");
        break;

    case TYPE_MOD:
        printf("mod\n");
        break;

    case TYPE_CMPE:
        printf("cmpe\n");
        break;

    case TYPE_CMPNE:
        printf("cmpne\n");
        break;

    case TYPE_CMPG:
        printf("cmpg\n");
        break;

    case TYPE_CMPL:
        printf("cmpl\n");
        break;

    case TYPE_CMPGE:
        printf("cmpge\n");
        break;

    case TYPE_CMPLE:
        printf("cmple\n");
        break;

    case TYPE_JMP:
        printf("jmp\n");
        break;

    case TYPE_ZJMP:
        printf("zjmp\n");
        break;

    case TYPE_NZJMP:
        printf("nzjmp\n");
        break;

    case TYPE_PRINT:
        printf("print\n");
        break;

    case TYPE_HALT:
        printf("halt\n");
        break;
    }
    printf("text %s, line %d, character %d \n", token.text, token.line, token.character);
}

Token init_token(TokenType type, char *text, int line, int character)
{
    Token token = {.type = type, .text = text, .line = line, .character = character};
    return token;
}
TokenType check_builtin_keywords(char *name)
{
    if (strcmp(name, "nop") == 0)
    {
        // printf("NOP\n");
        return TYPE_NOP;
    }
    else if (strcmp(name, "push") == 0)
    {
        // printf("PUSH\n");
        return TYPE_PUSH;
    }
    else if (strcmp(name, "pop") == 0)
    {
        // printf("POP\n");
        return TYPE_POP;
    }
    else if (strcmp(name, "add") == 0)
    {
        // printf("ADD\n");
        return TYPE_ADD;
    }
    else if (strcmp(name, "sub") == 0)
    {
        // printf("SUB\n");
        return TYPE_SUB;
    }
    else if (strcmp(name, "mul") == 0)
    {
        // printf("MUL\n");
        return TYPE_MUL;
    }
    else if (strcmp(name, "dup") == 0)
    {
        // printf("DUP\n");
        return TYPE_DUP;
    }
    else if (strcmp(name, "indup") == 0)
    {
        // printf("INDUP\n");
        return TYPE_INDUP;
    }
    else if (strcmp(name, "swap") == 0)
    {
        // printf("SWAP\n");
        return TYPE_SWAP;
    }
    else if (strcmp(name, "inswap") == 0)
    {
        // printf("INSWAP\n");
        return TYPE_INSWAP;
    }
    else if (strcmp(name, "div") == 0)
    {
        // printf("DIV\n");
        return TYPE_DIV;
    }
    else if (strcmp(name, "mod") == 0)
    {
        // printf("MOD\n");
        return TYPE_MOD;
    }
    else if (strcmp(name, "cmpe") == 0)
    {
        // printf("CMPE\n");
        return TYPE_CMPE;
    }
    else if (strcmp(name, "cmpne") == 0)
    {
        // printf("CMPNE\n");
        return TYPE_CMPNE;
    }
    else if (strcmp(name, "cmpg") == 0)
    {
        // printf("CMPG\n");
        return TYPE_CMPG;
    }
    else if (strcmp(name, "cmpl") == 0)
    {
        // printf("CMPL\n");
        return TYPE_CMPL;
    }
    else if (strcmp(name, "cmpge") == 0)
    {
        // printf("CMPGE\n");
        return TYPE_CMPGE;
    }
    else if (strcmp(name, "cmple") == 0)
    {
        // printf("CMPLE\n");
        return TYPE_CMPLE;
    }
    else if (strcmp(name, "jmp") == 0)
    {
        // printf("JMP\n");
        return TYPE_JMP;
    }
    else if (strcmp(name, "zjmp") == 0)
    {
        // printf("ZJMP\n");
        return TYPE_ZJMP;
    }
    else if (strcmp(name, "nzjmp") == 0)
    {
        // printf("NZJMP\n");
        return TYPE_NZJMP;
    }
    else if (strcmp(name, "print") == 0)
    {
        // printf("PRINT\n");
        return TYPE_PRINT;
    }
    else if (strcmp(name, "halt") == 0)
    {
        // printf("HALT\n");
        return TYPE_HALT;
    }

    return -1;
}
Token generate_keyword(char *current, int *current_index, int line, int character)
{
    // printf("HERE_GEN_KEYWORD\n");
    char *keyword_name = malloc(sizeof(char) * 8);
    int keyword_length = 0;
    while (isalpha(current[*current_index]))
    {
        keyword_name[keyword_length] = current[*current_index];
        *current_index += 1;
        keyword_length++;
    }
    keyword_name[keyword_length] = '\0';
    // printf("%s\n", keyword_name);
    TokenType type = check_builtin_keywords(keyword_name);
    assert(type != TYPE_NONE && "Custom Identifiers are not implemented yet\n");
    Token token = init_token(type, keyword_name, line, character);
    return token;
}

int lexer()
{
    int length;
    char *current = open_file("test.rvasm", &length);
    int current_index = 0;

    int line = 1;
    int character = 1;
    while (current_index < length)

    {
        if (current[current_index] == '\n')
        {
            line++;
            character = 0;
        }
        if (isalpha(current[current_index]))
        {
            Token token = generate_keyword(current, &current_index, line, character);
            current_index--;
            print_token(token);
        }

        else if (isdigit(current[current_index]))
        {
            printf("NUMERIC\n");
        }

        current_index++;
        character++;
    }
    return 0;
}
