#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    float length = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);
    float a = (100 / words);
    float L = (length * a);
    float S = (sentences * a);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round(index) >= 1 && round(index) <= 15)
    {
        printf("Grade %g\n", round(index));
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_letters(string text)
{
    int z = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] > 64 && text[i] < 123)
        {
            z = z + 1;
        }
        else
        {
            z = z + 0;
        }
    }
    return z;
}

int count_words(string text)
{
    int x = 0;
    for (int i = 0, n = strlen(text) ; i < n; i++)
    {
        if (text[i] == 32)
        {
            x = x + 1;
        }
        else
        {
            x = x + 0;
        }
    }
    return x + 1;
}

int count_sentences(string text)
{
    int y = 0;
    for (int i = 0, n = strlen(text) ; i < n; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            y = y + 1;
        }
        else
        {
            y = y + 0;
        }
    }
    return y;
}
