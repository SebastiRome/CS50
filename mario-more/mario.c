#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i;
    do
    {
        i = get_int("height: ");
        if (i > 0 && i < 9)
        {
            for (int x = 0; x < i; x++)
            {
                for (int c = x + 1; c < i; c++)
                {
                    printf(" ");
                }
                for (int b = x; b >= 0; b--)
                {
                    printf("#");
                }
                for (int z = 0; z < 2; z++)
                {
                    printf(" ");
                }
                for (int y = x; y >= 0; y--)
                {
                    printf("#");
                }
                printf("\n");
            }
        }
    }
    while (i <= 0 || i > 8);
}