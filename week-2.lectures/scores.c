#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int num = 3;
    int scores[num];

    for (int i = 0; i < num; i++)
    {
        scores[i] = get_int("Score: ");
    }

    int avg;
    for (int i = 0; i < num; i++)
    {
        avg += scores[i];
    }

    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);
}

