#include <stdio.h>
#include <stdlib.h>
#include "Mylib.h"
#include <stdbool.h>

int main()
{
    printf("==========================================\n");
    printf("               CALCULATOR                 \n");
    printf("==========================================\n\n");

    char fullop[50];
    Token e = initToken();

    while (e.type != t_Exit)
    {
        ///Get the string
        printf("Expression : ");
        fgets(fullop, 50, stdin);
        e = (calculator(fullop));
        if (e.type == t_Error)
        {synterror(e);}
    }
    return 0;
}
