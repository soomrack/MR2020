#include <stdint.h>
#include <stdbool.h>
#include "string.h"

int32_t eval( const char * formula );
void nextChar();
bool eat(int charToEat);
char * substring(int startPos, int endPos, const char * str);
int parseFactor();
int parseTerm();
int parseExpression();
int parse();