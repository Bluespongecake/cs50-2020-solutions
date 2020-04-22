#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //user input
    string text = get_string("Text: ");

    //get letters, words and sentances
    int textLen = strlen(text);
    int letters = 0;
    int words = 1;  //starts at one because there wont be a space at the end of the sentance
    int sentances = 0;
    
    //loop through the text to get data
    for (int i = 0; i < textLen; i++)
    {
        if (((int)text[i] >= 'a' && (int)text[i] <= 'z') || ((int)text[i] >= 'A' && (int)text[i] <= 'Z'))
        {
            letters++;
        }
        if (text[i] == ' ')
        {
            words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentances++;
        }
    }
    
    //get key variables to calculate index
    float L = (100 * (float) letters / words);
    float S = (100 * (float) sentances / words);
    
    float index = 0.0588 * L - 0.296 * S - 15.8;
    
    //outputs. 3 cases. One will run no matter what happens
    if (index < 16 && index >= 0.5)
    {
        printf("Grade %i\n", (int)round(index));
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else 
    {
        printf("Before Grade 1\n");
    }


    
    
}