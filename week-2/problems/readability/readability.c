#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void) 
{
    // TODO: Get text to interpret reading level from
    string text = get_string("Text: ");

    // TODO: Get letters
    int letters = count_letters(text);

    // TODO: Get words
    int words = count_words(text);

    // TODO: Get sentences
    int sentences = count_sentences(text);

    // TODO: Calc averages & output grade level
    float avg_letters = (float) letters / (float) words * 100.0;
    float avg_sentences = (float) sentences / (float) words * 100.0;
    int level = round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8);

    // TODO: >= 16 = print "Grade 16+"
    if (level >= 16)
    {
        printf("Grade 16+\n");
    }
    // TODO: < 1 = print "Before Grade 1"
    else if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    // TODO: Round to nearest int & print "Grade X"
    else
    {
        printf("Grade %i\n", level);
    }
}

int count_letters(string text)
{
    int lCount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            lCount++;
        }
    }
    return lCount;
}

int count_words(string text)
{
    int wCount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            wCount++;
        }
    }
    return wCount + 1;
}

int count_sentences(string text)
{
    int sCount = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sCount++;
        }
    }
    return sCount;
}
