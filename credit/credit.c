#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long x;
    int a = 0;
    int b = 0;
    do
    {
        x = get_long("Card Number: ");
        for (int y = 1; y < 17; y++)
        {
            long z = round(pow(10, y));
            long v = round(pow(10, y - 1));
            long w = (x % z) / v;
            if (y % 2 == 0)
            {
                if (w > 4)
                {
                    b = b + (2 * w % 10) + 1;
                }
                else
                {
                    b = b + 2 * w;
                }
            }
            else
            {
                a = a + w;
            }
        }
        int c = a + b;
        if (c % 10 == 0)
        {
            if (x > 339999999999999 && x < 350000000000000)
            {
                printf("AMEX\n");
            }
            else if (x > 369999999999999 && x < 380000000000000)
            {
                printf("AMEX\n");
            }
            else if (x > 5099999999999999 && x < 5600000000000000)
            {
                printf("MASTERCARD\n");
            }
            else if (x > 3999999999999999 && x < 5000000000000000)
            {
                printf("VISA\n");
            }
            else if (x > 3999999999999 && x < 5000000000000)
            {
                printf("VISA\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    while (x < 999999999999 || x > 10000000000000000);
}