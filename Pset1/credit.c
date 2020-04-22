#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //define some variables
    int cardnumber[16];                     //number on the card
    int check = 0;                          //variable to check how long the number is
    int validate = 0;                       //number for arithmetic
    long card = get_long("Number: ");
    int val;
    string cardtype = "INVALID";

    //add number to the array
    for (int i = 15; i > -1; i--)   
    {
        cardnumber[i] = card % 10;
        card = card / 10;
    }

    while (cardnumber[check] == 0)              //this means that the card is 16 digits
    {
        check += 1;
    }
    if (check == 0)
    {
        if (cardnumber[0] == 5 && cardnumber[1] > 0 && cardnumber[1] < 6)
        {
            cardtype = "MASTERCARD";
        }
        else if (cardnumber[0] == 4)
        {
            cardtype = "VISA";
        }
    }
    else if (check == 1 && cardnumber[1] == 3 && (cardnumber[2] == 4 || cardnumber[2] == 7))
    {
        cardtype = "AMEX";
    }
    else if (check == 3 && cardnumber[2] == 4)
    {
        cardtype = "VISA";
    }

    //validation process
    for (int i = 14; i > -1; i -= 2)
    {
        val = cardnumber[i] * 2;
        if (val >= 10)
        {
            val = (val % 10) + 1;
        }
        validate += val;
    }
    for (int i = 15; i > -1; i -= 2)
    {
        validate += cardnumber[i];
    }
    if (!(validate % 10 == 0))
    {
        cardtype = "INVALID";
    }
    printf("%s\n", cardtype);
}
