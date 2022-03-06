#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // int nums[] = {3, 0, 6, 2, 1, 5, 6, 4, 5};
    int nums[] = {12, 32, 104, 16, 2, 17, 18, 21, 69, 43, 69};
    int nums_cnt = 11;

    for (int i = 0; i < nums_cnt; i++)
    {
        printf("Nums:\n");
        for (int j = 0; j < nums_cnt; j++)
        {
            printf("%i ", nums[j]);
        }
        printf("\n");

        printf("Comparing %i...\n", nums[i]);
        int lowest_idx = i;
        int nums_tmp;
        for (int j = i + 1; j < nums_cnt; j++)
        {
            if (nums[j] < nums[lowest_idx])
            {
                lowest_idx = j;
                nums_tmp = nums[j];
            }
        }

        if (nums[lowest_idx] != nums[i])
        {
            printf("%i is lowest!!!\n", nums[lowest_idx]);
            nums[lowest_idx] = nums[i];
            nums[i] = nums_tmp;
        }
        printf("\n");
    }

    printf("Sorted nums:\n");
    for (int j = 0; j < nums_cnt; j++)
    {
        printf("%i ", nums[j]);
    }
    printf("\n");

}
