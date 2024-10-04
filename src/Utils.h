#pragma once

// Get a random integer in the interval [min, max]
int rand_in_range(int min, int max);

// Random number in [0, 1)
double randomd(void);

// Seed the random number generator with current time
void init_random_seed(void);
