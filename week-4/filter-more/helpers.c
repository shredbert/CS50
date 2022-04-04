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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            // Create vars for gx/gy vals for current grid
            int gx_red = 0, gx_green = 0, gx_blue = 0, gx_factor,
                gy_red = 0, gy_green = 0, gy_blue = 0, gy_factor;
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    // TODO: Assign px val based on vals or leave at 0 if edge
                    /*
                        Gx:
                        -1  0  1
                        -2  0  2
                        -1  0  1
                        Gy:
                        -1 -2 -1
                         0  0  0
                         1  2  1
                    */
                    // TODO: Figure out factor
                    switch (k):
                    {
                        case 1:
                            break;
                        default:
                            gx_factor = 0;
                            gy_factor = 0;
                            break;
                    }
                    // TODO: Implement factor
                }
            }
            // TODO: Calculate square root of Gx^2 + Gy^2, assign, & ensure ! >
            // 255 & rounded to nearest int
        }
    }
    return;
}

// Return lesser of 2 ints so never > 255 for pxs
int return_lesser(int max, int test)
{
    return test > max ? max : test;
}
