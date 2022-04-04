#include "helpers.h"
#include <math.h>

int return_lesser(int max, int test);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through rows & pxs
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find average px val -> R + G + B / 3 rounded to nearest int
            int gray_num = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = gray_num;
            image[i][j].rgbtGreen = gray_num;
            image[i][j].rgbtBlue = gray_num;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate rows/pxs
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Apply sepia filter, rounding to nearest int, & !> 255
            int sepia_red = return_lesser(255, 
                                          round(0.393 * image[i][j].rgbtRed +
                                                0.769 * image[i][j].rgbtGreen +
                                                0.189 * image[i][j].rgbtBlue));

            int sepia_green = return_lesser(255, round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 *
                                            image[i][j].rgbtBlue));

            int sepia_blue = return_lesser(255, round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 *
                                           image[i][j].rgbtBlue));

            image[i][j].rgbtRed = sepia_red;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtBlue = sepia_blue;
        }
    }
    return;
}

// Return lesser of 2 ints so never > 255 for pxs
int return_lesser(int max, int test)
{
    return test > max ? max : test;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate rows/pxs
    for (int i = 0; i < height; i++)
    {
        // Swap pxs on opposite sides horizontally
        // Iterate before half of width (if odd, mid doesn't swap)
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pxs
            RGBTRIPLE swap = image[i][j];
            image [i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy over pxs to retain OG vals
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate rows/pxs
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Add all surrounding px vals & count # of vals in grid
            int num_sqrs = 0, total_red = 0, total_green = 0, total_blue = 0;
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    // Only add if valid grid value
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        total_red += copy[k][l].rgbtRed;
                        total_green += copy[k][l].rgbtGreen;
                        total_blue += copy[k][l].rgbtBlue;
                        num_sqrs++;
                    }
                }
            }

            image[i][j].rgbtRed = round(total_red / (float) num_sqrs);
            image[i][j].rgbtGreen = round(total_green / (float) num_sqrs);
            image[i][j].rgbtBlue = round(total_blue / (float) num_sqrs);
        }
    }
    return;
}
