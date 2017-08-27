#include "HeightGenerator.h"
#include <random>


HeightGenerator::HeightGenerator(int seed) :mSeed(seed)
{
}


HeightGenerator::~HeightGenerator()
{
}

int HeightGenerator::GenerateHeight(int x, int z)
{
	return GetSmoothNoise(x,z);
}

double HeightGenerator::GetNoise(double x, double z)
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	rng.seed(x * 1234 + z * 4321 + mSeed);
	std::uniform_real_distribution<double> uni(0, 32); // guaranteed unbiased

	return uni(rng);
}

double HeightGenerator::GetSmoothNoise(double x, double z)
{
	double corners = (GetNoise(x - 1, z - 1) + GetNoise(x + 1, z - 1) + GetNoise(x - 1, z + 1) + GetNoise(x + 1, z + 1)) / 16;
	double sides = (GetNoise(x - 1, z) + GetNoise(x + 1, z) + GetNoise(x, z + 1) + GetNoise(x, z + 1)) / 8;
	float centre = GetNoise(x, z) / 4;
	return corners + sides + centre;
}

double HeightGenerator::interpolate(double a, double b, double blend)
{
	
}
