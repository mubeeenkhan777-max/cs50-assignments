#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;

// Function prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele(void);

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a family with three generations
    person *p = create_family(GENERATIONS);

    // Print the family tree
    print_family(p, 0);

    // Free the entire family tree
    free_family(p);

    return 0;
}

// Create a new individual
person *create_family(int generations)
{
    // Allocate memory for a new person
    person *p = malloc(sizeof(person));

    if (p == NULL)
    {
        return NULL;
    }

    // If we've reached the oldest generation
    if (generations == 1)
    {
        // This person has no parents
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // Randomly assign alleles
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }
    else
    {
        // Create two parents recursively
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Inherit one random allele from each parent
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }

    return p;
}

// Free the entire family tree
void free_family(person *p)
{
    // Stop if there is no person
    if (p == NULL)
    {
        return;
    }

    // Free both parents first
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Then free this person
    free(p);
}

// Randomly return A, B, or O
char random_allele(void)
{
    int r = rand() % 3;

    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}

// Print family tree
void print_family(person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }

    // Print indentation based on generation
    for (int i = 0; i < generation; i++)
    {
        printf("  ");
    }

    // Print person's alleles
    printf("Generation %i: %c%c\n", generation, p->alleles[0], p->alleles[1]);

    // Print parents
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}
