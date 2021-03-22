#include "eval.h"

static char ch = -1;
static int pos = -1;
static const char * formula;

int32_t eval( const char * formula )
{
     formula = formula;

     parse();
	
    return 0;
}

void nextChar(void) 
{
    if (++pos < strlen(formula)){
        ch = formula[pos];
    }
    else{
        ch = -1;
    }
}

bool eat(int charToEat) {
    while (ch == ' ') nextChar();
    if (ch == charToEat) {
        nextChar();
        return true;
    }
    return false;
}

char * substring(int startPos, int endPos, const char * str){
    char * subStr;
    int pos = 0;
    for (int i = startPos; i < endPos; i++){
        subStr[pos] = str[i];
        ++pos;
    }
    return subStr;
}

// Grammar:
// expression = term | expression `+` term | expression `-` term
// term = factor | term `*` factor | term `/` factor
// factor = `+` factor | `-` factor | `(` expression `)`
//        | number | functionName factor | factor `^` factor

int parseFactor(void) {
    if (eat('+')) return parseFactor(); // unary plus
    if (eat('-')) return -parseFactor(); // unary minus

    int x;
    int startPos = pos;
    if (eat('(')) 
    { // parentheses
        x = parseExpression();
        eat(')');
    } 
    else if (ch >= '0' && ch <= '9') 
    { // numbers
        while (ch >= '0' && ch <= '9') nextChar();
        x = (int32_t) substring(startPos, pos, formula);
    }
    return x;
}

int parseTerm(void) 
{
    int x = parseFactor();
    for (;;) {
        if      (eat('*')) x *= parseFactor(); // multiplication
        else if (eat('/')) x /= parseFactor(); // division
        else return x;
    }
}

int parseExpression(void) {
    int x = parseTerm();
    for (;;) {
        if      (eat('+')) x += parseTerm(); // addition
        else if (eat('-')) x -= parseTerm(); // subtraction
        else return x;
    }
}

int parse(void) {
    nextChar();
    int x = parseExpression();
    return x;
}
