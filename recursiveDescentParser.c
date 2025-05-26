#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKEN_SIZE 100

// Define token types
typedef enum {
    T_IF, T_ELSE, T_WHILE, T_LBRACE, T_RBRACE, T_LPAREN, T_RPAREN, T_SEMICOLON,
    T_IDENTIFIER, T_NUMBER, T_REL_OP, T_PLUS, T_MINUS, T_MULT, T_DIV, T_LTD, T_EOF, T_UNKNOWN
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_SIZE];
} Token;

// Global variables for lexer and parser
char *input;   // Input program
int index = 0; // Current position in the input
Token current_token;

// Function prototypes
void lexer();
void parse_program();
void parse_block();
void parse_statement();
void parse_if_statement();
void parse_while_statement();
void parse_expression();
void parse_term();
void parse_factor();
void parse_condition();
void match(TokenType expected);

// Lexer function to tokenize the input
void lexer() {
    while (input[index] != '\0' && isspace(input[index])) {
        index++;
    }

    if (input[index] == '\0') {
        current_token.type = T_EOF;
        current_token.value[0] = '\0';
        return;
    }

    char c = input[index];

    // Handle relational operators
    if (c == '=' && input[index + 1] == '=') {
        current_token.type = T_REL_OP;
        strncpy(current_token.value, "==", 3);
        index += 2;
        return;
    } else if (c == '!' && input[index + 1] == '=') {
        current_token.type = T_REL_OP;
        strncpy(current_token.value, "!=", 3);
        index += 2;
        return;
    } else if (c == '<' && input[index + 1] == '=') {
        current_token.type = T_REL_OP;
        strncpy(current_token.value, "<=", 3);
        index += 2;
        return;
    } else if (c == '>' && input[index + 1] == '=') {
        current_token.type = T_REL_OP;
        strncpy(current_token.value, ">=", 3);
        index += 2;
        return;
    } else if (c == '=' || c == '!' || c == '<' || c == '>') {
        current_token.type = T_REL_OP;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
        return;
    }

    // Handle arithmetic operators
    if (c == '+') {
        current_token.type = T_PLUS;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
        return;
    } else if (c == '-') {
        current_token.type = T_MINUS;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
        return;
    } else if (c == '*') {
        current_token.type = T_MULT;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
        return;
    } else if (c == '/') {
        current_token.type = T_DIV;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
        return;
    }

    // Handle other tokens
    if (c == '{') {
        current_token.type = T_LBRACE;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
    } else if (c == '}') {
        current_token.type = T_RBRACE;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
    } else if (c == '(') {
        current_token.type = T_LPAREN;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
    } else if (c == ')') {
        current_token.type = T_RPAREN;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
    } else if (c == ';') {
        current_token.type = T_SEMICOLON;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
    } else if (isalpha(c)) {
        int start = index;
        while (isalnum(input[index])) {
            index++;
        }
        strncpy(current_token.value, input + start, index - start);
        current_token.value[index - start] = '\0';

        if (strcmp(current_token.value, "if") == 0) {
            current_token.type = T_IF;
        } else if (strcmp(current_token.value, "else") == 0) {
            current_token.type = T_ELSE;
        } else if (strcmp(current_token.value, "while") == 0) {
            current_token.type = T_WHILE;
        } else if (strcmp(current_token.value, "LTD") == 0) {
            current_token.type = T_LTD;
        } else {
            current_token.type = T_IDENTIFIER;
        }
    } else if (isdigit(c)) {
        int start = index;
        while (isdigit(input[index])) {
            index++;
        }
        strncpy(current_token.value, input + start, index - start);
        current_token.value[index - start] = '\0';
        current_token.type = T_NUMBER;
    } else {
        current_token.type = T_UNKNOWN;
        current_token.value[0] = c;
        current_token.value[1] = '\0';
        index++;
    }
}
// Match function to consume tokens
void match(TokenType expected) {
    if (current_token.type == expected) {
        lexer();
    } else {
        printf("Syntax error: Expected token type %d, found %d\n", expected, current_token.type);
        exit(1);
    }
}

// Parser function for the program
void parse_program() {
    lexer();
    parse_block();
}

// Parse a block (statements enclosed in braces)
void parse_block() {
    match(T_LBRACE);
    while (current_token.type != T_RBRACE) {
        parse_statement();
    }
    match(T_RBRACE);
}

// Parse a statement
void parse_statement() {
    if (current_token.type == T_IF) {
        parse_if_statement();
    } else if (current_token.type == T_WHILE) {
        parse_while_statement();
    } else if (current_token.type == T_IDENTIFIER || current_token.type == T_NUMBER || current_token.type == T_LTD) {
        parse_expression();
        match(T_SEMICOLON);
    } else {
        printf("Syntax error: Unexpected token %s\n", current_token.value);
        exit(1);
    }
}

// Parse an if statement
void parse_if_statement() {
    match(T_IF);
    match(T_LPAREN);
    parse_condition();
    match(T_RPAREN);
    parse_block();
    if (current_token.type == T_ELSE) {
        match(T_ELSE);
        parse_block();
    }
}

// Parse a while statement
void parse_while_statement() {
    match(T_WHILE);
    match(T_LPAREN);
    parse_condition();
    match(T_RPAREN);
    parse_block();
}

// Parse an expression
void parse_expression() {
    parse_term();
    while (current_token.type == T_PLUS || current_token.type == T_MINUS) {
        lexer();
        parse_term();
    }
}

// Parse a term
void parse_term() {
    parse_factor();
    while (current_token.type == T_MULT || current_token.type == T_DIV) {
        lexer();
        parse_factor();
    }
}

// Parse a factor
void parse_factor() {
    if (current_token.type == T_NUMBER || current_token.type == T_IDENTIFIER || current_token.type == T_LTD) {
        lexer();
    } else if (current_token.type == T_LPAREN) {
        match(T_LPAREN);
        parse_expression();
        match(T_RPAREN);
    } else {
        printf("Syntax error: Unexpected token %s\n", current_token.value);
        exit(1);
    }
}

// Parse a condition (a comparison)
void parse_condition() {
    parse_expression();
    if (current_token.type == T_REL_OP) {
        lexer();
        parse_expression();
    } else {
        printf("Syntax error: Expected relational operator\n");
        exit(1);
    }
}

// Main function with interactive input
int main() {
    char buffer[1000];
    printf("Enter program code to parse (end with 'exit'):\n");

    while (1) {
        printf("Enter code block:\n");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        // Remove trailing newline
        buffer[strcspn(buffer, "\n")] = '\0';

        // Check for exit condition
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        input = buffer;
        index = 0;
        parse_program();
        printf("Program parsed successfully!\n\n");
    }

    return 0;
}
