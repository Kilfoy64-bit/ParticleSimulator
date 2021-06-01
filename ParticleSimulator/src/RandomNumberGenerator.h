#pragma once

#include <vector>

class RandomNumberGenerator
{
private:

	static RandomNumberGenerator s_Instance;

	RandomNumberGenerator();

	float generateFloat(float lo, float hi);
	double generateDouble(double lo, double hi);
	std::vector<float> generateFloatVec(float lo, float hi, int size);

public:
	RandomNumberGenerator(const RandomNumberGenerator&) = delete;

	static RandomNumberGenerator& Get()
	{
		return s_Instance;
	}
	double Double(double lo, double hi) { return generateDouble(lo, hi); }
	float Float(float lo, float hi) { return generateFloat(lo, hi); }
	std::vector<float> FloatVec(float lo, float hi, int size) { return generateFloatVec(lo, hi, size); }
};