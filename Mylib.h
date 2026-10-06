#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED
#include <stdbool.h>
#define MAX_TOKENS 100

///TOKEN TYPE DECLARATION //////////////////////////////////////////////////////////////////////

typedef enum
{
    t_Number,
    t_Operator,
    t_Parenthesis,
    t_Error,
    t_Exit,
    t_Default
}type;

///Token
typedef struct
{
    int type;
    float number;
    char op;
    bool negative;
}Token;

///MAIN FUNCTION////////////////////////////////////////////////////////////////////////////////

Token calculator(char *fullop);

///TOKEN INITIALIZATION/////////////////////////////////////////////////////////////////////////

///Function to initialize a Token (defaul) and the array
Token initToken();

void addToken(Token tokens[], int *tindex, Token t);

///SUBFUNCTIONS/////////////////////////////////////////////////////////////////////////////////

///Function to exit the calculator
Token exitcalculator(char fullop[], int *i);

///Function to ignore the spaces in the operation
void spaceignore(char fullop[], int *i);

///Function to get the numbers
Token getNumbers(char fullop[], int *i, bool negative);

///Function to print the result
void print_result(Token result);

///SUBFUNCTION TO GET NUMBERS///////////////////////////////////////////////////////////////////

///Function to detect negative numbers in the start of the number or if the element is a number
Token gettoken(char fullop[], int *i, Token tokens[], int *tindex);

///Function to count the numbers
void numbers(char fullop[], int *i, Token *t, int *decimal, int *count);

///Function to count the number of points
void decnumbers(char fullop[], int *i,int *decimal);

///Function to print a Syntax error
void synterror(Token r);

///Function to detect a negative parenthesis
void isnegparenthesis(Token tokens[], int *tindex);

///SUBFUNCTION TO MAKE EASY THE CONDITIONS//////////////////////////////////////////////////////

///Function to know if the char is a number
bool isdigit(char c);

///Function to know if the char is a operator
bool isoperator(char c);

///Function to know if the char is a point of decimal numbers
bool isdecimal(char c);

///Function to know if the char is the end of the string or /0
bool isnottheend(char c);

///Function to know if the char is a parenthesis
bool isparenthesis(char c);

///function to check if the expression is properly parenthesized
bool valid_parenthesis(Token tokens[], int tindex);

///SUBFUNCTION TO THE SHUTINGYARD ALGORITHMS ///////////////////////////////////////////////////

///Function to know the operator priority
int priority(Token t);

///Function to make the shuting yard metod
int shutingyard(Token tokens[], Token output[], int Token_Max_Index);

///Function to return the result of the operation
Token result(Token a, Token t, Token b);

///function to handle the post-fixed stack
Token post_exp(Token output[], int outindex);

///SUBFUNCTION TO PUSH/POP/PEEK AN STACK ///////////////////////////////////////////////////////

///Function to look the first element of the stack
Token peek(Token stack[], int i);

///Function to take the first element of the stack
Token pop(Token stack[], int *i);

///Function to put a element in the stack
void push(Token stack[], int *i, Token t);

#endif // MYLIB_H_INCLUDED
