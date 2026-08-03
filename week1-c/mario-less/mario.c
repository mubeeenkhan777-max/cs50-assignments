#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt the user for a valid height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // Print the pyramid
    for (int row = 1; row <= height; row++)
    {
        // Print spaces
        for (int space = 0; space < height - row; space++)
        {
            printf(" ");
        }

        // Print bricks
        for (int brick = 0; brick < row; brick++)
        {
            printf("#");
        }

        // Move to the next line
        printf("\n");
    }
}
