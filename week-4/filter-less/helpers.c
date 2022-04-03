#include "helpers.h"
#include <math.h>

// Test--remove
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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate rows/pxs
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Apply sepia filter, rounding to nearest int, & !> 255
            int sepia_red = return_lesser(255, round(
                        0.393 * image[i][j].rgbtRed +
                        0.769 * image[i][j].rgbtGreen +
                        0.189 * image[i][j].rgbtBlue));
            int sepia_green = return_lesser(255, round(
                        0.349 * image[i][j].rgbtRed +
                        0.686 * image[i][j].rgbtGreen +
                        0.168 * image[i][j].rgbtBlue));
            int sepia_blue = return_lesser(255, round(
                        0.272* image[i][j].rgbtRed +
                        0.534 * image[i][j].rgbtGreen +
                        0.131 * image[i][j].rgbtBlue));

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
    // Iterate rows/pxs
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // // Test:
            // printf("OG px: ");
            // printf("Red: %i, ", image[i][j].rgbtRed);
            // printf("Green: %i, ", image[i][j].rgbtGreen);
            // printf("Blue: %i\n", image[i][j].rgbtBlue);

            // TODO: Box blur -- avg of pxs in 9 px radius

            // // Test:
            // printf("NU px: ");
            // printf("Red: %i, ", image[i][j].rgbtRed);
            // printf("Green: %i, ", image[i][j].rgbtGreen);
            // printf("Blue: %i\n", image[i][j].rgbtBlue);
            // printf("\n");

        }
    }
    return;
}
