#include "Mylib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

///MAIN FUNCTION////////////////////////////////////////////////////////////////////////////////

Token calculator(char *fullop)
{
    int i = 0, tindex = 0;
    Token tokens[MAX_TOKENS], output[MAX_TOKENS];
    Token current = initToken();

    while (isnottheend(fullop[i]))
    {
        ///Function to ignore the spaces in the operation
        spaceignore(fullop, &i);

        ///Exit the calculator
        current = exitcalculator(fullop,&i);
        if (current.type == t_Exit){return current;};

        ///Get the first token
        current = gettoken(fullop, &i, tokens, &tindex);
        if (current.type == t_Error){return current;};

            addToken(tokens,&tindex,current);
            continue;
    }

    ///function to check if the expression is properly parenthesized
    if (valid_parenthesis(tokens,tindex) == false)
        {
            current.type = t_Error;
            return current;
        }

    ///Shutingyard part
    int outindex = shutingyard(tokens,output,tindex);
    current = post_exp(output,outindex);

    if (current.type == t_Error){return current;};///Return Error Token
    print_result(current);
    return current;
}

///TOKEN INITIALIZATION/////////////////////////////////////////////////////////////////////////

///Function to initialize a Token (defaul) and the array
Token initToken()
{
    Token t;
    t.type = t_Default;
    t.number = 0.0;
    t.op = '\0';
    t.negative = false;
    return t;
}

///Function to add a token to the array
void addToken(Token tokens[], int *tindex, Token t)
{
    tokens[*tindex] = t;
    (*tindex)++;
}

///SUBFUNCTIONS/////////////////////////////////////////////////////////////////////////////////

///Function to exit the calculator
Token exitcalculator(char fullop[], int *i)
{
    Token t = initToken();
    if (fullop[*i] == 'q')
    {
        t.type = t_Exit;
        return t;
    }
    return t;
}

///Function to ignore the spaces in the operation
void spaceignore(char fullop[], int *i)
{
    while(fullop[*i] == ' ')
    {
        (*i)++;
    }
}

///Function to get the numbers
Token getNumbers(char fullop[], int *i, bool negative)
{
    int point_count = 0;
    int deccount = 0;
    Token t = initToken();

    while (isnottheend(fullop[*i]) && !(isoperator(fullop[*i])) && !(isparenthesis(fullop[*i])) && fullop[*i] != ' ')
    {
        if (isdigit(fullop[*i]))
        {
        ///Function to put the numbers and count the number of decimals
        numbers(fullop,i,&t,&point_count,&deccount);
        }
        else if (isdecimal(fullop[*i]))
        {
            ///Function to count the number of points
            decnumbers(fullop,i,&point_count);
        }
        else
        {
            t.type = t_Error;
            return t;
        }
    }
        ///Transform the number into decimal number
        while(deccount > 0)
        {
            t.number = t.number / 10.0;
            deccount--;
        }
        ///Turn the number in negative
        if (negative)
        {
            t.number = t.number * -1;
        }

        ///If we have more the one point syntax error of the expression
        if (point_count > 1)
        {
            t.type = t_Error;
            return t;
        }
    t.type = t_Number;
    return t;
}

///Function to print the result
void print_result(Token result)
{
    printf("Result     : %g\n\n",result.number);
    printf("==========================================\n\n");
    return;
}

///SUBFUNCTION TO GET NUMBERS///////////////////////////////////////////////////////////////////

///Function to detect negative numbers in the start of the number or if the element is a number
Token gettoken(char fullop[], int *i, Token tokens[], int *tindex)
 {
    Token t = initToken();

    if (fullop[*i] == '-' && (*tindex == 0 || tokens[*tindex - 1].type != t_Number))
        {
            (*i)++;
            spaceignore(fullop,i);

            if (isdigit(fullop[*i]))
            {
                t.negative = true;
                t = getNumbers(fullop,i,t.negative);
                return t;
            }
            else if(fullop[*i] == '(')
            {
                ///Function to detect a negative parenthesis and transform in "-1 * ( .... )"
                isnegparenthesis(tokens,tindex);
                t.type = t_Parenthesis;
                t.op = '(';
                (*i)++;
                return t;
            }
            else
            {
                t.type = t_Error;
                return t;
            }
        }
    else if (isdigit(fullop[*i]))
        {
            t = getNumbers(fullop,i,t.negative);
            return t;
        }
    else if (isoperator(fullop[*i]))
    {
        t.type = t_Operator;
        t.op = fullop[*i];
        (*i)++;
        return t;
    }
    else if (isparenthesis(fullop[*i]))
    {
        t.type = t_Parenthesis;
        t.op = fullop[*i];
        (*i)++;
        return t;
    }
    else
    {
        t.type = t_Error;
        return t;
    }
}

///Function to put the numbers and count the decimals
void numbers(char fullop[], int *i, Token *t, int *decimal, int *deccount)
{
    t->number = (t->number * 10.0 + (fullop[*i] - '0'));
    (*i)++;
    if ((*decimal) > 0)
    (*deccount)++;
    return;
}

///Function to count the number of points
void decnumbers(char fullop[], int *i,int *decimal)
{
    (*decimal)++;
    (*i)++;
    return;
}

///Function to print a Syntax error
void synterror(Token r)
{
    if ((r.type == t_Error) && (r.op == '/'))
    {
        printf("Division by zero\n\n");
    }
    else if ((r.op == '(' || r.op == ')') && r.type == t_Error)
    {
        printf("Wrong parenthesized expression\n\n");
    }
    else
    {
    printf("Syntax Error \n\n");
    }

}

///Function to detect a negative parenthesis
void isnegparenthesis(Token tokens[], int *tindex)
{
    Token t = initToken();

    t.type = t_Number;
    t.number = -1;
    addToken(tokens, tindex, t);

    t.type = t_Operator;
    t.op = '*';
    addToken(tokens, tindex, t);
    return;
}

///SUBFUNCTION TO MAKE EASY THE CONDITIONS//////////////////////////////////////////////////////

///Function to know if the char is a number
bool isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return true;
    else
        return false;
}

///Function to know if the char is a operator
bool isoperator(char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*' || c == 'v' || c == 'V')
        return true;
    else
        return false;
}

///Function to know if the char is a point of decimal numbers
bool isdecimal(char c)
{
    if (c == ',' || c == '.')
        return true;
    else
        return false;
}

///Function to know if the char is the end of the string or \0
bool isnottheend(char c)
{
    if (c != '\n' && c != '\0')
        return true;
    else
        return false;
}

///Function to know if the char is a parenthesis
bool isparenthesis(char c)
{
    if (c == '(' || c == ')')
        return true;
    else
        return false;
}

///function to check if the expression is properly parenthesized
bool valid_parenthesis(Token tokens[], int tindex)
{
    int count = 0;
    int i = 0;

    while(count >= 0 && i < tindex)
    {
        if (tokens[i].type  == t_Parenthesis)
        {
            if(tokens[i].op == '('){count++;}
            if(tokens[i].op == ')'){count--;}
        }
        i++;
    }
    if (count != 0)
    {
        return false;
    }
    else
        return true;
}

///SUBFUNCTION TO PUSH/POP/PEEK AN STACK ///////////////////////////////////////////////////////

///Function to put a element in the stack
void push(Token stack[], int *i, Token t)
{
    (*i)++;
    stack[*i] = t;
}

///Function to take the first element of the stack
Token pop(Token stack[], int *i)
{
    Token t = stack[*i];
    (*i)--;
    return t;
}

///Function to look the first element of the stack
Token peek(Token stack[], int i)
{
    return stack[i];
}

bool isEmpty(int i)
{
    if (i == -1)
        return true;
    else
        return false;
}

///SUBFUNCTION TO THE SHUTINGYARD ALGORITHMS ///////////////////////////////////////////////////

///Function to know the operator priority
int priority(Token t)
{
    if (t.op == '/' || t.op == '*')
        return 1;
    if (t.op == '+' || t.op == '-')
        return 0;
    else
        return -1;
}

///Function to make the shuting yard metod
int shutingyard(Token tokens[], Token output[], int Token_Max_Index)
{
    //Token stack to apply the shuting yard algorithm
    Token stack[MAX_TOKENS];
    int i = -1;
    //tindex is the token index
    int tindex = 0;
    int Outindex = 0;

    ///If i have more tokens in the array
    while (tindex < Token_Max_Index)
    {
        if (tokens[tindex].type == t_Parenthesis && tokens[tindex].op == '(')
        {
            push(stack,&i,tokens[tindex]);
        }
        else if (tokens[tindex].type == t_Parenthesis && tokens[tindex].op == ')')
        {
            while (!isEmpty(i) && stack[i].op != '(')
            {
                output[Outindex] = pop(stack,&i);
                Outindex++;
            }

            if(!isEmpty(i) && stack[i].op == '(')
            {
                pop(stack,&i);
            }
        }
        else if (tokens[tindex].type == t_Number)
        {
            output[Outindex] = tokens[tindex];
            Outindex++;
        }
        else if (tokens[tindex].type == t_Operator)
        {
            ///If i have more operators in the array
            while(!isEmpty(i) && priority(stack[i]) >= priority(tokens[tindex]))
            {
                output[Outindex] = pop(stack,&i);
                Outindex++;
            }
            push(stack,&i,tokens[tindex]);
        }
        tindex++;
    }

    while (!isEmpty(i))
        {
            if(stack[i].op == '(')
                return -1;

            output[Outindex] = pop(stack, &i);
            Outindex++;
        }
        return Outindex;
}

///function to handle the post-fixed stack
Token post_exp(Token output[], int outindex)
{
    Token stack[MAX_TOKENS];
    int istack = -1;
    int i = 0;
    Token final_result = initToken();
    Token current = initToken();

    ///We have more elements to analice
    while (i < outindex)
    {
        ///Is a number
        if (output[i].type == t_Number)
        {
            push(stack,&istack,output[i]);
        }
        ///Is a sign
        if (output[i].type == t_Operator)
        {
            if (istack < 1)
            {
                current.type = t_Error;
                return current;
            }

            Token a = pop(stack,&istack);
            Token b = pop(stack,&istack);
            current = result(b,output[i],a);
            if(current.type == t_Error){return current;};
            push(stack,&istack,current);
        }
        i++;
    }
    if (istack != 0)
    {
        current.type = t_Error;
        return current;
    }
    final_result = pop(stack,&istack);
    return final_result;
}

///Function to return the result of the operation
Token result(Token a, Token t, Token b)
{
    Token r = initToken();
    r.type = t_Number;

    switch(t.op)
    {
    case '+':
        {
            r.number = a.number + b.number;
            return r;
        }

    case '-':
        {
            r.number = a.number - b.number;
            return r;
        }
    case '*':
        {
            r.number = a.number * b.number;
            return r;
        }
    case '/':
        {
            if (b.number != 0)
            {
            r.number = a.number / b.number;
            return r;
            }
            else
            {
                r.type = t_Error;
                r.op = ('/');
                return r;
            }
        }
        default:
            r.type = t_Error;
            return r;
    }
}
