#include <stdio.h>
#include <cs50.h>

int main(void)
{
    /* TODO: get credit card # -- assume format OK, get_long(), must be
     * positive */
    long num;
    do
    {
        num = get_long("Number: ");
    }
    while (!num || num <= 0);

    /* TODO: check for valid # of digits -- 13 to 16 */
    long decimalPlaces = 1,
         firstDigit = (num - num % decimalPlaces) / decimalPlaces,
         firstTwoDigits;
    int digits = 1;

    while (firstDigit > 9)
    {
        decimalPlaces = decimalPlaces * 10;
        digits++;
        firstDigit = (num - num % decimalPlaces) / decimalPlaces;
        firstTwoDigits = (num - num % (decimalPlaces / 10)) / (decimalPlaces / 10);
    }

    if (digits < 13 || digits > 16)
    {
        printf("INVALID\n");
    }
    else
    {
        /* TODO: check starting digits: Visa = 4, MC = 51 - 55, Amex = 34 or 37 */
        int cardType = 0; // 0 = invalid, 1 = Visa, 2 = MC, 3 = Amex
        if (firstDigit == 4)
        {
            cardType = 1;
        }
        else if (firstTwoDigits > 50 && firstTwoDigits < 56)
        {
            cardType = 2;
        }
        else if (firstTwoDigits == 34 || firstTwoDigits == 37)
        {
            cardType = 3;
        }

        if (!cardType)
        {
            printf("INVALID\n");
        }
        else
        {
            /* TODO: check checksums with Luhn's algorithm:
             * 1. start from 2nd last digit, multiply each by 2, & add the
             * resulting DIGITS ONLY (NOT products)
             * 2. then add sum of all digits NOT multiplied by 2
             * 3. if % 10 == 0, valid (i.e., last dig. == 0)
             */

            /* TODO: create array from digits of num */
            long sumTotal = 0;
            int count = 0;
            bool isValid = false;
            /* printf("%ld\n", num); */
            /* for (int i = 0; i < digits; i++) */
            /* for (long i = decimalPlaces; i > 1; i = i / 10) */
            for (long i = 10; i <= decimalPlaces * 10; i = i * 10, count++)
            {
                long digit = (num % i) / (i / 10);
                if (count % 2)
                {
                    /* printf("even: "); */
                    digit = digit * 2;
                    if (digit < 10)
                    {
                        /* printf("%ld\n", digit); */
                        sumTotal = sumTotal + digit;
                    }
                    else
                    {
                        int first = (digit - digit % 10) / 10;
                        int second = digit % 10;
                        /* printf("first = %i, second = %i\n", first, second); */
                        sumTotal = sumTotal + first + second;
                    }
                }
                else
                {
                    /* printf("odd: "); */
                    /* printf("%ld\n", digit); */
                    sumTotal = sumTotal + digit;
                }
            }

            /* printf("%ld; %ld\n", sumTotal, sumTotal % 10); */
            if (sumTotal % 10 == 0)
            {
                isValid = true;
            }
            /* printf("%d\n", isValid); */

            /* TODO: output whether AMEX\n, MASTERCARD\n, VISA\n, INVALID\n */
            if (!isValid)
            {
                printf("INVALID\n");
            }
            else
            {
                if (cardType == 1)
                {
                    printf("VISA\n");
                }
                else if (cardType == 2)
                {
                    printf("MASTERCARD\n");
                }
                else if (cardType == 3)
                {
                    printf("AMEX\n");
                }
            }
        }
    }
}

