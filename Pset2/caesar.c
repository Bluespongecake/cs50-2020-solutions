#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)                                                  //ensure that there is exactly 2 arguements
    {
        printf("Usage: ./caesar key\n");                            //tell the user the correct way to do it
        return 1;
    }
    int key = atoi(argv[1]);
    int num_check = key;
    int num_len = 0;
    do                                                              //find how many digits the key has
    {
        num_len++;
        num_check /= 10;
    }
    while (num_check);
    
    if (num_len != strlen(argv[1]))                                 //check if the int key and the arguement passed are the same lenght
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    string text = get_string("Plaintext: ");                        //prompt the motherf**ker for text yo
    int bang = strlen(text);
    printf("ciphertext: ");
    for (int i = 0; i < bang; i++)                                  //dunno why i called the lenght of plain text bang, but yeah...
    {
        if (text[i] >= 'a' && text[i] <= 'z')                       //case: lowercase
        {
            printf("%c", 'a' + (((text[i] - 'a') + key) % 26));
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')                  //case: UPPERCASE
        {
            printf("%c", 'A' + (((text[i] - 'A') + key) % 26));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}