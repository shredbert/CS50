#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

void calcReadability(int words, int sentences);

int main(void) 
{
    // TODO: Get text to interpret reading level from
    string text = get_string("Text: ");

    // TODO: Get chrCnt -- use isalpha()

    // TODO: Get wrdCnt -- use isspace()

    // TODO: Get sntncCnt -- use !isdigit() || above

    // TODO: Output grade level
    // calcReadability(wrdCnt, sntncCnt);
}

void calcReadability(int words, int sentences)
{
    double exactLvl = 0.0588 * words - 0.296 * sentences - 15.8;

    // TODO: >= 16 = print "Grade 16+"
    if (exactLvl >= 16)
    {
        printf("Grade 16+");
    }
    // TODO: < 1 = print "Before Grade 1"
    else if (exactLvl < 1)
    {
        printf("Before Grade 1");
    }
    // TODO: Round to nearest int & print "Grade X"
    else
    {
        printf("Grade %i\n", (int) round(exactLvl));
    }
}
