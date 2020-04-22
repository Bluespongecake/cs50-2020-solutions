#include <cs50.h>
#include <stdio.h>

//print n hashes
void hash(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}
//print n spaces
void space(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

//main code
int main(void)
{
    int h = 0;
    //get height
    while (h > 8 || h < 1)
    {
        h = get_int("Height: ");
    }
    //print out pyramid
    for (int i = 1; i < h + 1; i++)
    {
        space(h - i);
        hash(i);
        space(2);
        hash(i);
        printf("\n");
        //next row
    }
}
