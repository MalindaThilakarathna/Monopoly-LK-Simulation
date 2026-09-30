/*
 * MONOPOLY-LK Viva deterministic random generator
 *
 * Lecturer-supplied file.
 *
 * This file provides deterministic values for:
 *
 *     rand()
 *     srand()
 *     randRange(min, max)
 *
 * The student's random seed is ignored.
 */

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
   PART 1: Standard rand()/srand()
   ============================================================ */

static unsigned long state = 123456789UL;

void srand(unsigned int seed)
{
    (void)seed;
    state = 123456789UL;
}

int rand(void)
{
    state = (1103515245UL * state + 12345UL)
            & 0x7fffffffUL;

    return (int)state;
}


/* ============================================================
   PART 2: Fixed randRange() values
   ============================================================ */

/*
 * These are the values that will be returned by successive
 * calls to randRange(min, max).
 */

static const int fixed_values[] =
{
    4, 2,
    6, 3,
    5, 1,
    4, 4,
    2, 6,
    3, 5,
    6, 2,
    1, 4,
    5, 3,
    2, 2,

    6, 5,
    4, 1,
    3, 6,
    5, 2,
    1, 3,
    4, 6,
    2, 5,
    6, 4,
    3, 2,
    5, 1
};

static const size_t fixed_count =
    sizeof(fixed_values) / sizeof(fixed_values[0]);

static size_t fixed_index = 0;


/* ============================================================
   PART 3: Wrapped randRange()
   ============================================================ */

int __wrap_randRange(int min, int max)
{
    int value;

    if (fixed_index >= fixed_count)
    {
        fprintf(stderr,
                "\nERROR: Viva randRange sequence exhausted.\n");

        exit(EXIT_FAILURE);
    }

    value = fixed_values[fixed_index++];

    if (value < min || value > max)
    {
        fprintf(stderr,
                "\nERROR: Invalid viva randRange value.\n"
                "Call number : %zu\n"
                "Requested   : %d to %d\n"
                "Test value  : %d\n",
                fixed_index,
                min,
                max,
                value);

        exit(EXIT_FAILURE);
    }

    return value;
}