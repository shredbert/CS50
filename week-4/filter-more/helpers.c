#include "helpers.h"
#include <math.h>

// Test
#include <stdio.h>

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
                    /*
                        Gy:
                        -1 -2 -1
                         0  0  0
                         1  2  1
                        Gx:
                        -1  0  1
                        -2  0  2
                        -1  0  1
                    */
                    // Determine factor based on above
                    // Positive Gy
                    if (k > i)
                    {
                        // Positive Gx
                        if (l > j)
                        {
                            gy_factor = 1;
                            gx_factor = 1;
                        }
                        // Negative Gx
                        else if (l < j)
                        {
                            gy_factor = 1;
                            gx_factor = -1;
                        }
                        // Zero Gx
                        else
                        {
                            gy_factor = 2;
                            gx_factor = 0;
                        }
                    }
                    // Negative Gy
                    else if (k < i)
                    {
                        // Positive Gx
                        if (l > j)
                        {
                            gy_factor = -1;
                            gx_factor = 1;
                        }
                        // Negative Gx
                        else if (l < j)
                        {
                            gy_factor = -1;
                            gx_factor = -1;
                        }
                        // Zero Gx
                        else
                        {
                            gy_factor = -2;
                            gx_factor = 0;
                        }
                    }
                    // Zero Gy
                    else
                    {
                        gy_factor = 0;
                        // Positive Gx
                        if (l > j)
                        {
                            gx_factor = 2;
                        }
                        // Negative Gx
                        else if (l < j)
                        {
                            gx_factor = -2;
                        }
                        // Zero Gx
                        else
                        {
                            gx_factor = 0;
                        }
                    }
                    // Horizontal border
                    if (k < 0 || k > height)
                    {
                        gy_factor = 0;
                    }
                    // Vertical border
                    if (l < 0 || l > width)
                    {
                        gx_factor = 0;
                    }
                }
            }
            // Assign factor for RGB of both X & Y using square root of Gx^2 +
            // Gy^2, assign, & ensuring ! > 255 & rounded to nearest int
            gx_red = (float) copy[i][j].rgbtRed * gx_factor;
            gy_red = (float) copy[i][j].rgbtRed * gy_factor;
            image[i][j].rgbtRed = return_lesser(255,
                                                round(sqrt(pow(gx_red, 2) +
                                                        pow(gy_red, 2))));

            gx_green = (float) copy[i][j].rgbtGreen * gx_factor;
            gy_green = (float) copy[i][j].rgbtGreen * gy_factor;
            image[i][j].rgbtGreen = return_lesser(255,
                                                  round(sqrt(pow(gx_green, 2) +
                                                          pow(gy_green, 2))));

            gx_blue = (float) copy[i][j].rgbtBlue * gx_factor;
            gy_blue = (float) copy[i][j].rgbtBlue * gy_factor;
            image[i][j].rgbtBlue = return_lesser(255,
                                                 round(sqrt(pow(gx_blue, 2) +
                                                         pow(gy_blue, 2))));
        }
    }
    return;
}

// Return lesser of 2 ints so never > 255 for pxs
int return_lesser(int max, int test)
{
    // printf("%i\n", test);
    return test > max ? max : test;
}
