#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define STRINGIFY(x) #x


//Tests
#define TEST_EQUAL(value, expected)                                      \
{                                                                          \
    printf("%-50s","Testing "  STRINGIFY(value) " ");                      \
    int32_t v = value;                                                     \
    if( v != expected )                                                    \
    {                                                                      \
        printf( "Test failed! "         \
               " Expected: %i, got %i\n", expected, v);                    \
        returnCode = 1;                                                    \
    }                                                                      \
    else                                                                   \
    {                                                                      \
        printf(": "  "Passed"  "\n"); \
    }                                                                      \
}
//--------------------------------------------------------------------------



/*----------------------------------------------------
 * Realising infix notation calc with using two stacks:
 * One stack is for Operands and Second is for Operators
 -----------------------------------------------------*/


//-----------------------------------------------------
struct Stack { //Struct for Operators
    char c;
    struct Stack *next;
};

struct Stackk { //Struct for Operands
    float c;
    struct Stackk *next;
};
//-----------------------------------------------------

//Push
static void push(struct Stack **TOP, char a) { //Pushing Operand
    struct Stack *pointer;
    if ((pointer = malloc(sizeof(struct Stack))) == NULL)
        exit(-1);
    pointer->c = a;
    pointer->next = *TOP;
    *TOP = pointer;
}

static void pushh(struct Stackk **TOP, int64_t a) { //Pushing Operator
    struct Stackk *pointer;
    if ((pointer = malloc(sizeof(struct Stackk))) == NULL)
        exit(-1);
    pointer->c = a;
    pointer->next = *TOP;
    *TOP = pointer;
}
//-------------------------------------------------------


//Delete
static char Delete(struct Stack **TOP) { //Delete Operand
    struct Stack *pointer;
    char a;
    pointer = *TOP;
    a = pointer->c;
    *TOP = pointer->next;
    free(pointer);
    return a;
}

static int64_t Deletee(struct Stackk **TOP) { //Delete Operator
    struct Stackk *pointer;
    int64_t a;
    pointer = *TOP;
    a = pointer->c;
    *TOP = pointer->next;
    free(pointer);
    return a;
}
//--------------------------------------------------------


//Priority
static int Priority(char a) {
    switch (a) {
        case '*':
        case '/':
            return 3;
        case '-':
        case '+':
            return 2;
        case '(':
            return 1;
    }
}
//---------------------------------------------------------


static void POPOP(struct Stackk **OPERANDS, struct Stack **OPERATORS) {
    int64_t B = (Deletee(OPERANDS));
    int64_t A = (Deletee(OPERANDS));
    switch (Delete(OPERATORS)) {
        case '+':
            pushh(OPERANDS, A + B);
            break;
        case '-':
            pushh(OPERANDS, A - B);
            break;
        case '*':
            pushh(OPERANDS, A * B);
            break;
        case '/':
            pushh(OPERANDS, A / B);
            break;
    }
}


//Evaluating function
int32_t eval(const char *formula) {
    int counter = 0;
    char g[strlen(formula)];
    struct Stack *OPERATORS = NULL;
    struct Stackk *OPERANDS = NULL;
    for (int i = 0; i < strlen(formula); i++) {
        if (formula[i] == ' ') {

        } else if ((formula[i] == '+' || formula[i] == '-') && (formula[i - 1] < '0' || formula[i - 1] > '9') &&
                   (formula[i - 1]) != ')' && (formula[i - 1]) != ' ') {
            push(&OPERATORS, formula[i]);
            pushh(&OPERANDS, 0);
        } else {
            if (formula[i] >= '0' && formula[i] <= '9') {
                g[counter++] = formula[i];
                if (formula[i + 1] < '0' || formula[i + 1] > '9') {
                    pushh(&OPERANDS, atoi(g));
                    for (int j = 0; j < counter; j++) {
                        g[j] = '\0';
                    }
                    counter = 0;
                }
            } else if (formula[i] == ')') {
                if (OPERATORS == NULL)
                    exit(-1);
                while ((OPERATORS->c) != '(')
                    POPOP(&OPERANDS, &OPERATORS);
                Delete(&OPERATORS);
            } else if ((OPERATORS == NULL) || (Priority(formula[i]) > (Priority(OPERATORS->c)) || formula[i] == '('))
                push(&OPERATORS, formula[i]);
            else {
                while (OPERATORS != NULL && Priority(formula[i]) <= Priority(OPERATORS->c))
                    POPOP(&OPERANDS, &OPERATORS);
                push(&OPERATORS, formula[i]);
            }
        }
    }
    while (OPERATORS != NULL)
        POPOP(&OPERANDS, &OPERATORS);
    int answer = Deletee(&OPERANDS);
    return answer;
}
//--------------------------------------------------------------

int main(void) {
    int returnCode = 0;

    printf("Starting tests on eval...\n\n");

    // sanity checks
    TEST_EQUAL(eval("1+2"), 3);
    TEST_EQUAL(eval("2+1"), 3);
    TEST_EQUAL(eval("1"), 1);
    TEST_EQUAL(eval("5*5"), 25);
    TEST_EQUAL(eval("10/3"), 3);
    TEST_EQUAL(eval("3-2"), 1);

    // make sure that division is integral
    TEST_EQUAL(eval("1/2"), 0);

    // checking unary minus
    TEST_EQUAL(eval("(-2)"), -2);
    TEST_EQUAL(eval("3-(-2)"), 5);
    TEST_EQUAL(eval("3*(-5)"), -15);
    TEST_EQUAL(eval("3/(-2)"), -1);
    TEST_EQUAL(eval("(-2)*(-2)"), 4);
    TEST_EQUAL(eval("(-2)+(-2)"), -4);

    // tests from the assignment
    TEST_EQUAL(eval("(1+2)"), 3);
    TEST_EQUAL(eval("((0*2)-14)"), -14);
    TEST_EQUAL(eval("(100 - (9/1))"), 91);
    TEST_EQUAL(eval("1+(-1)"), 0);

    // having fun around zero
    TEST_EQUAL(eval("(0)"), 0);
    TEST_EQUAL(eval("(-0)"), 0);
    TEST_EQUAL(eval("0-(-0)"), 0);
    TEST_EQUAL(eval("(0-0)"), 0);
    TEST_EQUAL(eval("(0-1)"), -1);
    TEST_EQUAL(eval("(0+1)"), 1);
    TEST_EQUAL(eval("(1*0)"), 0);
    TEST_EQUAL(eval("(-1)"), -1);
    TEST_EQUAL(eval("((-1)*(-1))"), 1);
    TEST_EQUAL(eval("( 1 * 0) "), 0);

    // more realistic examples
    TEST_EQUAL(eval("(((10/3)*5)-10)+(9*3)"), 32);
    TEST_EQUAL(eval("3-2"), 1);

    // corner cases :3
    TEST_EQUAL(eval("((((100/1)*1)/1)*1)/1"), 100);


    TEST_EQUAL(eval("((-1)*((-1)*(-2147483648)))"), INT_MIN);
    TEST_EQUAL(eval("(((-2)*(-2147483648)))/(-2)"), INT_MIN);

    TEST_EQUAL(eval("(-(-(-(-1))))"), 1);
    TEST_EQUAL(eval("(((((((((((((((((((((((((((((10)))))))))))))))))))))))))))))"), 10);

}




