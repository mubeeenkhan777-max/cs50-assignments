#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter
int POINTS[] = {
    1, 3, 3, 2, 1, 4, 2, 4, 1, 8,
    5, 1, 3, 1, 1, 3, 10, 1, 1, 1,
    1, 4, 4, 8, 4, 10
};

// Function prototype
int compute_score(string word);

int main(void)
{
    // Get words from both players
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    // Compute scores
    int score1 = compute_score(player1);
    int score2 = compute_score(player2);

    // Compare scores
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int score = 0;

    // Loop through every letter in the word
    for (int i = 0; i < strlen(word); i++)
    {
        char letter = word[i];

        // If the letter is uppercase
        if (isupper(letter))
        {
            score += POINTS[letter - 'A'];
        }

        // If the letter is lowercase
        else if (islower(letter))
        {
            score += POINTS[letter - 'a'];
        }
    }

    return score;
}
