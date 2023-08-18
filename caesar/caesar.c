                                                                                                    #include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2 || only_digits(argv[1]) != true)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        string ptxt = get_string("plaintext:  ");
        int a = atoi(argv[1]);
        printf("cyphertext: ");
        for (int i = 0, n = strlen(ptxt); i < n; i++)
        {
            printf("%c", rotate(ptxt[i], a));
        }
    }
    printf("\n");
}

bool only_digits(string s)
{
    int x = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isdigit(s[i]))
        {
            x = x + 0;
        }
        else
        {
            x = x + 1;
        }
    }
    if (x >= 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

char rotate(char c, int n)
{
    if ((islower(c) && n > 26) || (isupper(c) && n > 26))
    {
        return c + (n % 26);
    }
    else if ((islower(c) && n < 26) || (isupper(c) && n < 26))
    {
        return c + n;
    }
    else
    {
        return c;
    }
}