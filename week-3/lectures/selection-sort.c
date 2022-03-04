#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int nums[] = {3, 0, 6, 2, 1, 5, 6, 4, 5};
    int nums_cnt = 8;

    for (int i = 0; i < nums_cnt; i++)
    {
        printf("OG nums:\n");
        for (int i = 0; i < nums_cnt; i++)
        {
            printf("%i", nums[i]);
        }
        printf("\n");

        printf("Comparing %i...\n", nums[i]);
        int lowest = nums[i];
        int placeholder;
        for (int j = i; j < nums_cnt; j++)
        {
            if (nums[j] < nums[lowest])
            {
                lowest = j;
                placeholder = nums[j];
            }
        }

        if (lowest != nums[i])
        {
            printf("%i is lowest!!!\n", nums[lowest]);
            nums[lowest] = nums[i];
            nums[i] = placeholder;
        }
        printf("\n");
    }

    printf("Sorted nums:\n");
    for (int i = 0; i < nums_cnt; i++)
    {
        printf("%i", nums[i]);
    }
    printf("\n");

}
