#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int alphanum(char c)                                                //function that returns a characters place in the alphabet              
{
    if (c >= 'a' && c <= 'z')
    {
        return c - 97;
    }
    else if (c >= 'A' && c <= 'Z')
    {
        return c - 65;
    }
    else
    {
        return 0;
    }
}

int main(int argc, string argv[])
{
    
    if (argc != 2)                                                  //ensure that there is exactly 2 arguements
    {
        printf("Usage: ./substitution key\n");                      //tell the user the correct way to do it
        return 1;
    }
    
    if (strlen(argv[1]) != 26)                                      //check if the key is 26 digits
    {
        printf("Key must be 26 chars\n");
        return 1;
    }
    
    for (int i = 0; i < 26; i++)
    {
        if (!((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z')))
        {
            printf("Key must be alphabetic\n");                     //if it contains non-letter chars
            return 1;
        }
    }

    for (int i = 0; i < 26; i++)                                    //ensure that there are no duplicate characters
    {
        for (int j = 0; j < 26; j++)
        {
            if (i != j)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("key must not have repeated characters!!!\n");
                    return 1;
                }
            }
        }
    }
    
    string keys = argv[1];
    string text = get_string("plaintext: ");                        //prompt the motherf**ker for text yo
    int textLen = strlen(text);
    string output = text;                                           //output string
    
    for (int i = 0; i < textLen; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            output[i] = tolower(argv[1][alphanum(text[i])]);
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            output[i] = toupper(argv[1][alphanum(text[i])]);
        }
        else
        {
            output[i] = text[i];
        }

    }
    printf("ciphertext: %s\n", output);
    return 0;
}