/*
 * Utility.cpp
 *
 *  Created on: 4 Jul 2016
 *      Author: Fernando
 */

#include "Utility.h"
#include <cstdlib>

double Utility::random(double min, double max) {
	return ((std::rand() / static_cast<double>(RAND_MAX)) * (max - min)) + min;
}

double Utility::pi(double multiplier, double denominator) {
    return (3.14159265359 * multiplier) / denominator;
}
