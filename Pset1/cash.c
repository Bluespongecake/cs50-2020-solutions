#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float cashMoney = -1;
    int coins = 0;

    while (cashMoney < 0.00)
    {
        cashMoney = get_float("Change Owed: ");         //get cash owed
    }
    int cash = round(cashMoney * 100);                  //round it up to an int

    if (cash / 25 > 0)                                  //find quarters
    {
        coins += cash / 25;
        cash %= 25;
    }
    if (cash / 10 > 0)                                  //Find nickels or whatever the americans call them
    {
        coins += cash / 10;
        cash %= 10;
    }
    if (cash / 5 > 0)                                   //find dimes? Is that what the 5c is called?
    {                                                   
        coins += cash / 5;                              //Its kinda wack that the americans have names for like
        cash %= 5;                                      //all their coins but i gotta say it sounds cool af
    }
    coins += cash;                                      //add the leftover pennies to the count
    printf("%i\n", coins);

}
