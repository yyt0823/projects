#include "helpers.h"
#include <stdio.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float temp = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.00;
            int grey = round(temp);
            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp[i][j];
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
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float count = 0.00;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (i + x > height - 1 || i + x < 0 || j + y > width - 1 || j + y < 0)
                    {
                        continue;
                    }
                    sumRed += image[i + x][j + y].rgbtRed;
                    sumGreen += image[i + x][j + y].rgbtGreen;
                    sumBlue += image[i + x][j + y].rgbtBlue;
                    count++;
                }
            }
            temp[i][j].rgbtRed = round(sumRed / count);
            temp[i][j].rgbtGreen = round(sumGreen / count);
            temp[i][j].rgbtBlue = round(sumBlue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxRed = 0, GyRed = 0, GxGreen = 0, GyGreen = 0, GxBlue = 0, GyBlue = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int GxMultiplier = Gx[x + 1][y + 1];
                    int GyMultiplier = Gy[x + 1][y + 1];
                    if (i + x > height - 1 || i + x < 0 || j + y > width - 1 || j + y < 0)
                    {
                        continue;
                    }
                    GxRed += image[i + x][j + y].rgbtRed * GxMultiplier;
                    GxGreen += image[i + x][j + y].rgbtGreen * GxMultiplier;
                    GxBlue += image[i + x][j + y].rgbtBlue * GxMultiplier;

                    GyRed += image[i + x][j + y].rgbtRed * GyMultiplier;
                    GyGreen += image[i + x][j + y].rgbtGreen * GyMultiplier;
                    GyBlue += image[i + x][j + y].rgbtBlue * GyMultiplier;
                }
            }
            temp[i][j].rgbtRed = round(sqrt(GxRed * GxRed + GyRed * GyRed)) > 255 ? 255 : round(sqrt(GxRed * GxRed + GyRed * GyRed));
            temp[i][j].rgbtGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen)) > 255 ? 255 : round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            temp[i][j].rgbtBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue)) > 255 ? 255 : round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
