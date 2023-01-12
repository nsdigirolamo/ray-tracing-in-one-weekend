/**
    Author: Nicholas DiGirolamo
    Created: January 10, 2023
*/

#include "random_utils.h"

#include <stdlib.h>

double randDouble (double min, double max) {
    return min + (max - min) * (rand() / (RAND_MAX + 1.0));
}