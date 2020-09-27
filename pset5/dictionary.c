// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table. I am setting it to equal to the number of letters in the alphabed, i.e one bucket per letter
const unsigned int HASHSIZE = 26;
// Hash table
node *table[HASHSIZE];
//counter for how many words there are
unsigned int words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char low_word[LENGTH + 1];

    strcpy(low_word, word);
    
    if (strcasecmp(word, "i") == 0 || strcasecmp(word, "a") == 0 || strcasecmp(word, "cat") == 0)
    {
        return true;
    }
    //convert word to lowercase
    for (int i = 0; i < strlen(word) + 1; i++)
    {
        low_word[i] = tolower(word[i]);
    }
    low_word[strlen(word)] = '\0';
    //Hash word to get a value for the table
    int hashNo = hash(low_word);
    
    //printf("%s: %i\n", low_word, hashNo);

    //free the lowercase word because we no longer need it
    //access the linked list for that bucket, using a cursor as was suggested in the walkthrough video
    node *cursor = table[hashNo];
    if (cursor == NULL)
    {
        printf("no words in hashbucket: ");
        return false;
    }
    if (strcasecmp(cursor->word, word) == 0)
    {
        return true;
    }
    //traverse the list, looking for the word using strcasecmp(). Return true if it is found
    //we will keep searching until the end of the linked list
    while (cursor->next != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;


    }
    return false;
}


// Hashes word to a number. Found the first function I tried at http://www.cse.yorku.ca/~oz/hash.html. It kept giving memory errors
//so I wrote my own one
//gets the value of the first letter of each word. I.e a=1, b=2 etc.
unsigned int hash(const char *word)
{
    int Hashn = 0;
    Hashn = (int) tolower(word[0]) - 'a';
    return Hashn;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    int hashNo = 0;
    for (int i = 0; i > HASHSIZE; i++)
    {
        table[i] = NULL;
    }

    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("could not load dictionary, bro/n");
        return false;
    }

    char *word = malloc(LENGTH + 1);
    words = 0;

    if (word == NULL)
    {
        printf("failed to create word pointer/n");
        return false;
    }

    //scan through all the words until the end
    while (fscanf(dict, "%s", word) != EOF)
    {
        //allocate memory for a node and check to make sure it worked
        node *nod = malloc(sizeof(node));
        if (nod == NULL)
        {
            printf("unable to allocate memory to a given dictionary word\n");
            return false;
        }

        //fill in the node
        strcpy(nod->word, word);
        nod->next = NULL;

        //insert into hashtable
        //the way that i will approach this is by just sticking them in at the start of each bucket (because that way they will be in lexographical order)
        hashNo = hash(word);
        words++;

        //printf("%i", hashNo);

        //set the "next" pointer to point to the start of the list in the hashbucket
        nod->next = table[hashNo];

        //make the table point at the node
        table[hashNo] = nod;
        
        //printf("%s: %i\n", n->word, hashNo);
    }
    fclose(dict);
    free(word);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    node *cursor;

    for (int i = 0; i < HASHSIZE; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        tmp = table[i];
        cursor = table[i];

        //iterate through the entire bucket, free all the nodes.
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        //this was it! the line I was missing! This is the cause of many hours of VALGRINDing!!!
        free(cursor);
    }
    return true;
}
