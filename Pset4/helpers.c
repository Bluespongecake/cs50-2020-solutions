#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//max mccormack 2020
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (float)(image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3;
            image[i][j].rgbtRed = (int)round(average);
            image[i][j].rgbtGreen = (int)round(average);
            image[i][j].rgbtBlue = (int)round(average);
            //yea so we round all dem values to get em all equal to each other
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE dupe[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dupe[i][j] = image[i][width - j - 1]; //lil temporary array to store the image flipped
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = dupe[i][j];   //paste the flipped image into the array we will create a new file with.
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE dupe[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dupe[i][j] = image[i][j]; //copy the original array into a duplicate array
        
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float redAvg = 0;
            float blueAvg = 0;
            float greenAvg = 0;             //we finna go over the 9 required pixels and average them to get each pixel in the final thing.             
            float numPx = 0;                // counter to find how many pixels actually exist. Should be 9 unless on an edge.
            for (int k = -1; k < 2; k++)    //man really be running out of single letter variables tho.   
            {
                for (int y = -1; y < 2; y++)
                {
                    if ((i + k > -1)  && (i + k < height)  && (j + y > -1)  && (j + y < width))
                    {
                        redAvg += dupe[i + k][j + y].rgbtRed;
                        greenAvg += dupe[i + k][j + y].rgbtGreen;
                        blueAvg += dupe[i + k][j + y].rgbtBlue;
                        numPx++;

                    }
                }
            }
            
            image[i][j].rgbtRed = round(redAvg / numPx);
            image[i][j].rgbtBlue = round(blueAvg / numPx);
            image[i][j].rgbtGreen = round(greenAvg / numPx);
            
        }
        printf("\n");
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx_kernel[3][3] = 
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy_kernel[3][3] = 
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    
    int gxRed = 0;          //maybe not necessary to define all the variables here?
    int gyRed = 0;          //but i dont want to risk it so ill leave it for now

    int gxGreen = 0;        //cos it works
    int gyGreen = 0;
    
    int gxBlue = 0;
    int gyBlue = 0;
    
    RGBTRIPLE dupe[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            dupe[i][j] = image[i][j];               //copy  original array into dupe array
        
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if ((i + x > -1) && (i + x < height) && (j + y > -1) && (j + y < width)) //this was the root of all the problemos!!
                    {
                        gxRed += gx_kernel[x + 1][y + 1] * dupe[i + x][j + y].rgbtRed;
                        gxGreen += gx_kernel[x + 1][y + 1] * dupe[i + x][j + y].rgbtGreen;
                        gxBlue += gx_kernel[x + 1][y + 1] * dupe[i + x][j + y].rgbtBlue;
                        
                        gyRed += gy_kernel[x + 1][y + 1] * dupe[i + x][j + y].rgbtRed;
                        gyGreen += gy_kernel[x + 1][y + 1] * dupe[i + x][j + y].rgbtGreen;
                        gyBlue += gy_kernel[x + 1][y + 1] * dupe[i + x][j + y].rgbtBlue;
                        
                    }
                }
            }
            int red_layer = round(sqrt(pow(gxRed, 2) + pow(gyRed, 2)));
            int green_layer = round(sqrt(pow(gxGreen, 2) + pow(gyGreen, 2)));
            int blue_layer = round(sqrt(pow(gxBlue, 2) + pow(gyBlue, 2)));
            
            //make sure none of the values are above 255
            if (red_layer > 255)
            {
                red_layer = 255;
            }
            if (green_layer > 255)
            {
                green_layer = 255;
            }
            if (blue_layer > 255)
            {
                blue_layer = 255;
            }
            
            image[i][j].rgbtRed = red_layer;
            image[i][j].rgbtGreen = green_layer;
            image[i][j].rgbtBlue = blue_layer;

            //reset all them variables
            gxRed = 0;
            gyRed = 0;
            
            gxGreen = 0;
            gyGreen = 0;
            
            gxBlue = 0;
            gyBlue = 0;
        }
    }
    return;
}
