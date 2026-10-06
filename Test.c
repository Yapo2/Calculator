
///Function to detect negative numbers in the start of the number or if the element is a number
Token gettoken(char fullop[], int *i, Token tokens[], int tindex)
 {
    Token t = initToken();

    if (fullop[*i] == '-' && (tindex == 0 || tokens[tindex - 1].type != t_Number))
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
    ///Exit the calculator
    else if (fullop[*i] == 'q')
    {
        t.type = t_Exit;
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

///Function to detect a negative parenthesis
void isnegparenthesis(Token tokens[], int tindex)
{
    Token t = initToken();

    t.type = t_Number;
    t.number = -1;
    addToken(tokens, &tindex, t);

    t.type = t_Operator;
    t.op = '*';
    addToken(tokens, &tindex, t);
    return;
}
