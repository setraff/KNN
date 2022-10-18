#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
// type definitions
typedef struct
{
    int row;
    int col;
}
INDEX;
// function declarations
bool isEligible(int r, int c, int height, int width);
int findDenomination(int r, int c, int height, int width);
INDEX *findIndexes(int r, int c, int height, int width);
BYTE blurPixel(int r, int c, int height, int width, RGBTRIPLE copy[height][width], int option);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg_rgb;
    float sum_rgb;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            // calculate average
            sum_rgb = image[r][c].rgbtRed + image[r][c].rgbtGreen + image[r][c].rgbtBlue;
            avg_rgb = sum_rgb / 3.0;
            avg_rgb = (BYTE) round(avg_rgb);
            if (avg_rgb > 255)
            {
                image[r][c].rgbtRed = 255;
                image[r][c].rgbtGreen = 255;
                image[r][c].rgbtBlue = 255;
            }
            else
            {
                image[r][c].rgbtRed = avg_rgb;
                image[r][c].rgbtGreen = avg_rgb;
                image[r][c].rgbtBlue = avg_rgb;
            }
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed;
    float sepiaGreen;
    float sepiaBlue;
    // sepiaRed = (.393 * originalRed) + (.769 * originalGreen) + (.189 * originalBlue)
    // sepiaGreen = (.349 * originalRed) + (.686 * originalGreen) + (.168 * originalBlue)
    // sepiaBlue = (.272 * originalRed) + (.534 * originalGreen) + (.131 * originalBlue)
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            sepiaRed = (.393 * image[r][c].rgbtRed) + (.769 * image[r][c].rgbtGreen) + (.189 * image[r][c].rgbtBlue);
            if (sepiaRed >= 255)
            {
                sepiaRed = 255;
            }
            else if (sepiaRed <= 0)
            {
                sepiaRed = 0;
            }
            sepiaGreen = (.349 * image[r][c].rgbtRed) + (.686 * image[r][c].rgbtGreen) + (.168 * image[r][c].rgbtBlue);
            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }
            else if (sepiaGreen <= 0)
            {
                sepiaGreen = 0;
            }
            sepiaBlue = (.272 * image[r][c].rgbtRed) + (.534 * image[r][c].rgbtGreen) + (.131 * image[r][c].rgbtBlue);
            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }
            else if (sepiaBlue <= 0)
            {
                sepiaBlue = 0;
            }
            image[r][c].rgbtRed = (BYTE) round(sepiaRed);
            image[r][c].rgbtGreen = (BYTE) round(sepiaGreen);
            image[r][c].rgbtBlue = (BYTE) round(sepiaBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int last = width - 1;
    RGBTRIPLE temparr[width];
    for (int r = 0; r < height; r++)
    {
        // copy row into temparr
        for (int c = 0; c < width; c++)
        {
            temparr[c] = image[r][c];
        }
        // copy temparr into row in reverse
        for (int c = 0; c < width; c++)
        {
            image[r][c] = temparr[last - c];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make copy of image
    RGBTRIPLE copy[height][width];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            copy[r][c] = image[r][c];
        }
    }
    //filter
    for (int r = 0; r < height ; r++)
    {
        for (int c = 0; c < width ; c++)
        {
            image[r][c].rgbtRed = blurPixel(r, c, height, width, copy, 1);
            image[r][c].rgbtGreen = blurPixel(r, c, height, width, copy, 2);
            image[r][c].rgbtBlue = blurPixel(r, c, height, width, copy, 3);
        }
    }
}
// function to see if an index is eligible
bool isEligible(int r, int c, int height, int width)
{
    int hmax = height - 1;
    int wmax = width - 1;
    if (r < 0 || c < 0 || r > hmax || c > wmax)
    {
        return false;
    }
    return true;
}
// function to find denomination count
int findDenomination(int r, int c, int height, int width)
{
    int hmax = height - 1;
    int wmax = width - 1;
    // corners
    if (r == 0 && c == 0)
    {
        // FOO BAR 1
        return 4;
    }
    else if (c == wmax && r == 0)
    {
        // FOO BAR 2
        return 4;
    }
    else if (c == wmax && r == hmax)
    {
        // FOO BAR 4
        return 4;
    }
    else if (r == hmax && c == 0)
    {
        // FOO BAR 69
        return 4;
    }
    // edges
    else if (r - 1 < 0)
    {
        return 6;
    }
    else if (c + 1 > wmax)
    {
        return 6;
    }
    else if (r + 1 > hmax)
    {
        return 6;
    }
    else if (c - 1 < 0)
    {
        return 6;
    }
    else
    {
        return 9;
    }
}
// function to check which indexes are within one row and one column from origin (r, c)
// FOO BAR 1
INDEX *findIndexes(int r, int c, int height, int width)
{
    static INDEX buffer[9];
    // buffer[0].row = r - 1;
    // buffer[0].col = c - 1;
    // buffer[1].row = r - 1;
    // buffer[1].col = c;
    // buffer[2].row = r - 1;
    // buffer[2].col = c + 1;
    // buffer[3].row = r;
    // buffer[3].col = c - 1;
    // buffer[4].row = r;
    // buffer[4].col = c;
    // buffer[5].row = r;
    // buffer[5].col = c + 1;
    // buffer[6].row = r + 1;
    // buffer[6].col = c - 1;
    // buffer[7].row = r + 1;
    // buffer[7].col = c;
    // buffer[8].row = r + 1;
    // buffer[8].col = c + 1;
    static INDEX valid_indexes[9];

    static INDEX test_indexes[9];


    int ctr = 0;
    int boxSizeHalf = 1;
    for(int x = boxSizeHalf * -1; x <= boxSizeHalf; x++)
    {
        for(int y = boxSizeHalf * -1; y <= boxSizeHalf; y++)
        {

            buffer[ctr].row = r + x;
            buffer[ctr].col = c + y;
            ctr++;
        }
    }


    for (int i = 0; i < 9; i++)
    {
        if (isEligible(buffer[i].row, buffer[i].col, height, width))
        {
            valid_indexes[i].row = buffer[i].row;
            valid_indexes[i].col = buffer[i].col;
        }
        else
        {
            valid_indexes[i].row = -1;
            valid_indexes[i].col = -1;
        }
    }
    return valid_indexes;
}

// blur pixel
BYTE blurPixel(int r, int c, int height, int width, RGBTRIPLE copy[height][width], int option)
{
    // find eligible indexes and put them inside an array
    INDEX *eligible_indexes = findIndexes(r, c, height, width);
    float denomination = findDenomination(r, c, height, width);
    float redSum = 0;
    float greenSum = 0;
    float blueSum = 0;
    for (int i = 0; i < 9; i++)
    {
        if (eligible_indexes[i].row != -1 && eligible_indexes[i].col != -1)
        {
            redSum += copy[eligible_indexes[i].row][eligible_indexes[i].col].rgbtRed;
            greenSum += copy[eligible_indexes[i].row][eligible_indexes[i].col].rgbtGreen;
            blueSum += copy[eligible_indexes[i].row][eligible_indexes[i].col].rgbtBlue;
        }
    }
    switch (option)
    {
        // red
        case 1:
            return (BYTE) round(redSum / denomination);
            break;
        // green
        case 2:
            return (BYTE) round(greenSum / denomination);
            break;
        // blue
        case 3:
            return (BYTE) round(blueSum / denomination);
            break;
        default:
            return -1;
    }
}
