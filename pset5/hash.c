#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#define HASHSIZE 12000
#define LENGTH 45

//THIS IS A TEST PROGRAM
//not sure why i had to submit this but yeah.
//i used this as a playground to see what worked, then implemented it into the actual program
//I guess that it might work, might not.
//Who knows what it might do or generate

const char *s);
bool load();

int main(int argc, char *argv[])
{
    char *word = argv[1];
    char *wordtwo = argv[2];
    
    char lower[LENGTH + 1];

    strcpy(lower, word);
    for (int i = 0; word[i]; i++)
    {
        lower[i] = tolower(lower[i]);
    }
    
    char lowertwo[LENGTH + 1];

    strcpy(lowertwo, wordtwo);
    for (int i = 0; word[i]; i++)
    {
        lowertwo[i] = tolower(lowertwo[i]);
    }
    
    if (strcasecmp(word, wordtwo) == 0)
    {
        printf("words are the same\n");
    }
    else
    {
        printf("words are not the same\n");
    }
    printf("%s: ", word);
    printf("%i\n", hash(lower));

    printf("%s: ", wordtwo);
    printf("%i\n", hash(lowertwo));
}

unsigned int hash(const char *s)
{
    unsigned hashval = 0;
    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}



bool load()
{
    // TODO
    char *dictionary = "dictionaries/small";

    int indexes[HASHSIZE];

    for (int i = 0; i > HASHSIZE; i++)
    {
        indexes[i] = 0;
    }

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("could not load dictionary/n");
        return false;
    }

    int collisions = 0;
    char word[45];
    int words = 0;
    while (fscanf(dict, "%s", word) != EOF)
    {
        int index = hash(word);
        if (indexes[index] == 1)
        {
            collisions++;
            printf("%i collision: %s: %i\n", collisions, word, index);

        }
        else
        {
            indexes[index] = 1;
        }
        words++;
        
        printf("%ith: %s, h: %i\n", words, word, index);
    }

    printf("last word: %s\n\n", word);

    printf("%i collsions occured\n", collisions);
    printf("%i words read\n", words);
    return false;
}
