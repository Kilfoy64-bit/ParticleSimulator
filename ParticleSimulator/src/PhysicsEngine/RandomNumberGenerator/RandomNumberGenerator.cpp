#include "RandomNumberGenerator.h"

#include <stdlib.h>
#include <time.h>

RandomNumberGenerator::RandomNumberGenerator()
{
	srand(time(0));
}

float RandomNumberGenerator::generateFloat(float lo=0.0f, float hi=1.0f)
{
	return lo + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (hi - lo)));
}

double RandomNumberGenerator::generateDouble(double lo=0.0, double hi=0.0)
{
	return lo + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (hi - lo)));
}

std::vector<float> RandomNumberGenerator::generateFloatVec(float lo=0.0f, float hi=1.0f, int size=1)
{
	std::vector<float> randomFloats;
	for (int i = 0; i < size; i++) {
		randomFloats.push_back(generateFloat(lo, hi));
	}
	return randomFloats;
}