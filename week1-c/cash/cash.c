#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while (change < 0);
    int coins = 0;

    // For Quarter
    while (change >= 25)
    {

        change = change - 25;
        coins++;
    }
    // For Dime
    while (change >= 10)
    {
        change = change - 10;
        coins++;
    }
    // For Nickel
    while (change >= 5)
    {
        change = change - 5;
        coins++;
    }
    // For Penny
    while (change >= 1)
    {
        change = change - 1;
        coins++;
    }
    // Print the total numbers of coins
    printf("%i\n", coins);
}
