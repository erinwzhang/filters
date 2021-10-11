#include "helpers.h"
#include <math.h>
#include <string.h>

int limit(int RGB);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00;
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int start = 0;
        int end = width - 1;
        while (start < end)
        {
            RGBTRIPLE temp = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = temp;
            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float count = 0.0;
            int red = 0;
            int green = 0;
            int blue = 0;

            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k != -1 && i + k != height && j + l != -1 && j + l != width)
                    {
                        red += temp[i + k][j + l].rgbtRed;
                        green += temp[i + k][j + l].rgbtGreen;
                        blue += temp[i + k][j + l].rgbtBlue;
                        count ++;
                    }
                    else continue;
                }
            }

            image[i][j].rgbtRed = round(red / count);
            image[i][j].rgbtGreen = round(green / count);
            image[i][j].rgbtBlue = round(blue / count);
        }
    }
    return;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int x[3][3] = { {-1, -2, -1} , {0, 0, 0} , {1, 2, 1} };
    int y[3][3] = { {-1, 0, 1} , {-2, 0, 2} , {-1, 0, 1} };

    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxRed = 0.0;
            float gyRed = 0.0;
            float gxGreen = 0.0;
            float gyGreen = 0.0;
            float gxBlue = 0.0;
            float gyBlue = 0.0;

            for (int k = 0; k <= 2; k++)
            {
                for (int l = 0; l <= 2; l++)
                {
                    if (i + k != 0 && i + k != height + 1 && j + l != 0 && j + l != width + 1)
                    {
                        gxRed += temp[i + k - 1][j + l - 1].rgbtRed * x[k][l];
                        gxGreen += temp[i + k - 1][j + l - 1].rgbtGreen * x[k][l];
                        gxBlue += temp[i + k - 1][j + l - 1].rgbtBlue * x[k][l];

                        gyRed += temp[i + k - 1][j + l - 1].rgbtRed * y[k][l];
                        gyGreen += temp[i + k - 1][j + l - 1].rgbtGreen * y[k][l];
                        gyBlue += temp[i + k - 1][j + l - 1].rgbtBlue * y[k][l];
                    }
                }
            }

            image[i][j].rgbtRed = limit(round(sqrt((gxRed * gxRed) + (gyRed * gyRed))));
            image[i][j].rgbtGreen = limit(round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen))));
            image[i][j].rgbtBlue = limit(round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue))));
        }
    }
    return;
}

int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}