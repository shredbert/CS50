#include <stdio.h>
#include <cs50.h>
#include <math.h>
/* NOTE: check50 don't work, probably compiler issue with math lib import*/

int main(void)
{
    // TODO: get amount of change from user as float -- don't check for money
    // formatting (2 decimals) but ensure positive val
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);

    // TODO: convert user input from float (dollars) to int (cents) to avoid
    // errors & round using math.h
    int cents = round(dollars * 100);

    // TODO: find total *min.* # of coins (count quarters, dimes, nickels, & pennies)
    int coins;
    while (cents > 0)
    {
        if ((cents / 25) > 0)
        {
            coins += cents / 25;
            cents = cents - ((cents / 25) * 25);
        }
        else if ((cents / 10) > 0)
        {
            coins += cents / 10;
            cents = cents - ((cents / 10) * 10);
        }
        else if ((cents / 5) > 0)
        {
            coins += cents / 5;
            cents = cents - ((cents / 5) * 5);
        }
        else
        {
            coins += cents;
            cents = 0;
        }
    }

    // TODO: display min. # of coins (with line break)
    printf("%i\n", coins);
}

