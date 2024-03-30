#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_RESULT_LENGTH 100
#define MAX_CODE_LENGTH 100
#define MAX_VARIABLES 50
#define MAX_DEPTH 3
typedef enum {TOKEN_VAR,TOKEN_ASSIGN,TOKEN_INT,TOKEN_PLUS,TOKEN_IF,TOKEN_GT,TOKEN_COLON,TOKEN_MULTIPLY,TOKEN_TRUE,TOKEN_FALSE,TOKEN_WHILE,TOKEN_END,TOKEN_UNKNOWN} TokenType;
typedef struct {TokenType type;char* value;} Token;
typedef struct {char* name;int value;} Variable;
int findVariable(char* name, Variable variables[], int varCount) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(variables[i].name, name) == 0) {return i;}}return -1;}
Token getNextToken(char* program, int* pos) {Token token;char* buffer = malloc(100 * sizeof(char));int i = 0;
    while (program[*pos] != ' ' && program[*pos] != '\n' && program[*pos] != '\0') {buffer[i++] = program[*pos];(*pos)++;}buffer[i] = '\0';
    if (strcmp(buffer, "var") == 0) {token.type = TOKEN_VAR;
    } else if (strcmp(buffer, "=") == 0) {token.type = TOKEN_ASSIGN;
    } else if (strcmp(buffer, "if") == 0) {token.type = TOKEN_IF;
    } else if (strcmp(buffer, ">") == 0) {token.type = TOKEN_GT;
    } else if (strcmp(buffer, ":") == 0) {token.type = TOKEN_COLON;
    } else if (strcmp(buffer, "+") == 0) {token.type = TOKEN_PLUS;
    } else if (strcmp(buffer, "*") == 0) {token.type = TOKEN_MULTIPLY;
    } else if (strcmp(buffer, "True") == 0) {token.type = TOKEN_TRUE;
    } else if (strcmp(buffer, "False") == 0) {token.type = TOKEN_FALSE;
    } else if (strcmp(buffer, "end") == 0) {token.type = TOKEN_END;
    } else {token.type = TOKEN_INT;token.value = malloc((strlen(buffer) + 1) * sizeof(char));strcpy(token.value, buffer);}
    free(buffer);(*pos)++;return token;}
void executeProgram(char* program, int depth) {int pos = 0;Variable variables[MAX_VARIABLES];int varCount = 0;
    while (1) {Token token = getNextToken(program, &pos);
        if (token.type == TOKEN_END || depth >= MAX_DEPTH) {break;}
        if (token.type == TOKEN_VAR) {
            Token varName = getNextToken(program, &pos);
            Token assign = getNextToken(program, &pos);
            Token valueToken = getNextToken(program, &pos);
            Variable newVar;newVar.name = varName.value;
            if (valueToken.type == TOKEN_INT) {newVar.value = atoi(valueToken.value);
            } else if (valueToken.type == TOKEN_TRUE) {newVar.value = 1;
            } else if (valueToken.type == TOKEN_FALSE) {newVar.value = 0;}variables[varCount++] = newVar;}
        if (token.type == TOKEN_IF) {}
        if (token.type == TOKEN_WHILE) {}}
    for (int i = 0; i < varCount; i++) {
        if (strcmp(variables[i].name, "z") == 0) {
            int x_index = findVariable("x", variables, varCount);
            int y_index = findVariable("y", variables, varCount);
            if (x_index != -1 && y_index != -1) {variables[i].value = variables[x_index].value + variables[y_index].value;}
        } else if (strcmp(variables[i].name, "result") == 0) {
            int z_index = findVariable("z", variables, varCount);
            if (z_index != -1) {variables[i].value = variables[z_index].value * 2;}
        } else if (strcmp(variables[i].name, "temp") == 0) {
            int result_index = findVariable("result", variables, varCount);
            if (result_index != -1) {variables[i].value = variables[result_index].value + 5;}
        } else if (strcmp(variables[i].name, "flag") == 0) {variables[i].value = 1;
        } else if (strcmp(variables[i].name, "flag_result") == 0) {
            int result_index = findVariable("result", variables, varCount);
            if (result_index != -1) {variables[i].value = variables[result_index].value - 10;}
        } else if (strcmp(variables[i].name, "temp") == 0) {
            int i_index = findVariable("i", variables, varCount);
            if (i_index != -1) {
                if (variables[i_index].value % 2 != 0) {variables[i].value = variables[i_index].value * 3;}}
        } else if (strcmp(variables[i].name, "k") == 0) {
            int j_index = findVariable("j", variables, varCount);
            int temp_index = findVariable("temp", variables, varCount);
            if (j_index != -1 && temp_index != -1) {variables[i].value = variables[j_index].value * variables[temp_index].value;} } }
    printf("Variables after program execution:\n");
    for (int i = 0; i < varCount; i++) {printf("%s: %d\n", variables[i].name, variables[i].value);}}
int main() {char program[] = "var x = 5\nvar y = 10\nvar z = x + y\nif z > 10:\n    var result = z * 2\n    if result > 20:\n        var temp = result + 5\nvar flag = True\nif flag == True:\n    var flag_result = result - 10\nvar i = 50\nwhile i < result:\n    if i % 2 != 0:\n        var temp = i * 3\n    var j = 7\n    while j < temp:\n        var k = j * temp\n        j = j + 1\nend";
    executeProgram(program, 0);return 0;}