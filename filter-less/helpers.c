#include "helpers.h"
#include <math.h>

void swap(BYTE *a, BYTE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Each line
    for (int i = 0; i < height; i++)
    {
        // each row
        for (int j = 0; j < width; j++)
        {
            int x = round((image[i][j].rgbtBlue +  image[i][j].rgbtGreen +  image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtRed = x;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Each line
    for (int i = 0; i < height; i++)
    {
        // each row
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Each line
    for (int i = 0; i < height; i++)
    {
        // each row
        for (int j = 0; j < floor(width / 2); j++)
        {
            int tmpb = image[i][j].rgbtBlue;
            int tmpg = image[i][j].rgbtGreen;
            int tmpr = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            image[i][(width - 1) - j].rgbtBlue = tmpb;
            image[i][(width - 1) - j].rgbtGreen = tmpg;
            image[i][(width - 1) - j].rgbtRed = tmpr;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    long blue = 0;
    long green = 0;
    long red = 0;

    // create a copy
    RGBTRIPLE copy_image[height][width];
    for (int i = 0; i < height; i++)
    {
        // each row
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    // Each line
    for (int i = 0; i < height; i++)
    {
        // each row
        for (int j = 0; j < width; j++)
        {
            // square up and left
            if (i == 0 && j == 0)
            {
                // 2 square height
                for (int x = 0; x < 2; x++)
                {
                    // 2 square width
                    for (int y = 0; y < 2; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 4.0);
                image[i][j].rgbtGreen = round(green / 4.0);
                image[i][j].rgbtRed = round(red/ 4.0);
                blue = 0;
                green = 0;
                red = 0;
            }
            // square up and right
            else if (i == 0 && j == (width - 1))
            {
                // 2 square height
                for (int x = 0; x < 2; x++)
                {
                    // 2 square width
                    for (int y = - 1; y < 1; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 4.0);
                image[i][j].rgbtGreen = round(green / 4.0);
                image[i][j].rgbtRed = round(red / 4.0);
                blue = 0;
                green = 0;
                red = 0;
            }
            // square down and left
            else if (i == (height - 1) && j == 0)
            {
                // 2 square height
                for (int x = - 1; x < 1; x++)
                {
                    // 2 square width
                    for (int y = 0; y < 2; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 4.0);
                image[i][j].rgbtGreen = round(green / 4.0);
                image[i][j].rgbtRed = round(red / 4.0);
                blue = 0;
                green = 0;
                red = 0;
            }
            // square down and right
            else if (i == (height - 1) && j == (width - 1))
            {
                // 2 square height
                for (int x = - 1; x < 1; x++)
                {
                    // 2 square width
                    for (int y = - 1; y < 1; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 4.0);
                image[i][j].rgbtGreen = round(green / 4.0);
                image[i][j].rgbtRed = round(red / 4.0);
                blue = 0;
                green = 0;
                red = 0;
            }
            // first line
            else if (i == 0 && (j != 0 || j != (width - 1)))
            {
                // 2 square height: line [i] and [i + 1]
                for (int x = 0; x < 2; x++)
                {
                    // 3 square width: row [j - 1] and [j] and [j + 1]
                    for (int y = - 1; y < 2; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 6.0);
                image[i][j].rgbtGreen = round(green / 6.0);
                image[i][j].rgbtRed = round(red / 6.0);
                blue = 0;
                green = 0;
                red = 0;
            }
            // last line
            else if (i == (height - 1) && (j != 0 || j != (width - 1)))
            {
                // 2 square height: line [i] and [i - 1]
                for (int x = - 1; x < 1; x++)
                {
                    // 3 square width: row [j - 1] and [j] and [j + 1]
                    for (int y = - 1; y < 2; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 6.0);
                image[i][j].rgbtGreen = round(green / 6.0);
                image[i][j].rgbtRed = round(red / 6.0);
                blue = 0;
                green = 0;
                red = 0;
            }
            //  first row
            else if (j == 0 && (i != 0 || i != (height - 1)))
            {
                 // 3 square height: line [i - 1] and [i] and [i + 1]
                for (int x = - 1; x < 2; x++)
                {
                    // 2 square width: row [j] and [j + 1]
                    for (int y = 0; y < 2; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 6.0);
                image[i][j].rgbtGreen = round(green / 6.0);
                image[i][j].rgbtRed = round(red / 6.0);
                blue = 0;
                green = 0;
                red = 0;
            }
            // last row
            else if (j == (width - 1) && (i != 0 || i != (height - 1)))
            {
                // 3 square height: line [i - 1] and [i] and [i + 1]
                for (int x = - 1; x < 2; x++)
                {
                    // 2 square width: row [j] and [j - 1]
                    for (int y = - 1; y < 1; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 6.0);
                image[i][j].rgbtGreen = round(green / 6.0);
                image[i][j].rgbtRed = round(red / 6.0);
                blue = 0;
                green = 0;
                red = 0;
            }
            // Everything that is not on the edge
            else
            {
                // 3 square height: line [i - 1] and [i] and [i + 1]
                for (int x = - 1; x < 2; x++)
                {
                    // 3 square width: row [j - 1] and [j] and [j + 1]
                    for (int y = - 1; y < 2; y++)
                    {
                        blue = blue + copy_image[i + x][j + y].rgbtBlue;
                        green = green + copy_image[i + x][j + y].rgbtGreen;
                        red = red + copy_image[i + x][j + y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue = round(blue / 9.0);
                image[i][j].rgbtGreen = round(green / 9.0);
                image[i][j].rgbtRed = round(red / 9.0);
                blue = 0;
                green = 0;
                red = 0;
            }
        }
    }
}
