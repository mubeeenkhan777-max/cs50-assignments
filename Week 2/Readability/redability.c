#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Prompt the user for text
    string text = get_string("Text: ");

    // Variables to count letters, words, and sentences
    int letters = 0;
    int words = 1;
    int sentences = 0;

    // Loop through every character in the text
    for (int i = 0; i < strlen(text); i++)
    {
        // Count letters
        if (isalpha(text[i]))
        {
            letters++;
        }

        // Count words
        if (text[i] == ' ')
        {
            words++;
        }

        // Count sentences
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    // Calculate average number of letters and sentences per 100 words
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;

    // Calculate Coleman-Liau Index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Round the index to the nearest whole number
    int grade = round(index);

    // Print the appropriate grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
