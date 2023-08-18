#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i;
    do
    {
        i = get_int("How many blocks high should the pyramid be? ");
        if (i > 0 && i < 9) // Accepte les valeurs de 1 à 8
        {
            for (int x = i - 1; x >= 0; x--) // Nombre de ligne
            {
                for (int z = x - 1; z >= 0; z--) // Nombre d'espace
                {
                    printf(" ");
                }
                for (int y = x; y < i; y++) // Nombre de #
                {
                    printf("#");
                }
                printf("\n");
            }
        }
    }
    while (i <= 0 || i > 8); // Si la valeur n'est pas entre 1 et 8: recommence
}