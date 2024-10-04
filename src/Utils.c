#include "Utils.h"
#include <stdlib.h>
#include <time.h>

void init_random_seed(void) {
    srand(time(NULL));
}

double randomd(void) {
    return (double)rand() / (double)RAND_MAX;    
}

int rand_in_range(int min, int max) {
    return min + (int)(randomd() * (max - min + 1));
}
