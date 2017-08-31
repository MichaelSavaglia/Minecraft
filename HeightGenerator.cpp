#include "HeightGenerator.h"
#include <random>
#include <math.h>


HeightGenerator::HeightGenerator(int seed) :mSeed(seed)
{
	amplitude = 64.0f;
	octaves = 7;
	roughness = 0.53f;
}


HeightGenerator::~HeightGenerator()
{
}

int HeightGenerator::GenerateHeight(int x, int z)
{
	float total = 0;
	float d = (float)pow(2, octaves - 1);
	for (size_t i = 0; i < octaves; ++i)
	{
		float freq = pow(2, i) / d;
		float amp = powf(roughness, i) * amplitude;
		total += GetInterpolatedNoise(x*freq, z*freq) * amp;
	}
	float finalVal = total + (amplitude / 2);
	return finalVal < 0 ? 1 : finalVal;
}

double HeightGenerator::GetNoise(double x, double z)
{
	//std::random_device rd;     // only used once to initialise (seed) engine
	//std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	//rng.seed(x * 1234 + z * 4321 + mSeed);
	//std::uniform_real_distribution<double> uni(-1.0, 1.0); // guaranteed unbiased
	//return uni(rng);
	int n = (x + z * 57); // This way is 100x faster
	n += mSeed;
	n = (n << 13) ^ n;
	auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

	return 1.0 - ((double)newN / 1073741824.0);
}

double HeightGenerator::GetSmoothNoise(double x, double z)
{
	double corners = (GetNoise(x - 1, z - 1) + GetNoise(x + 1, z - 1) + GetNoise(x - 1, z + 1) + GetNoise(x + 1, z + 1)) / 16.0f;
	double sides = (GetNoise(x - 1, z) + GetNoise(x + 1, z) + GetNoise(x, z - 1) + GetNoise(x, z + 1)) / 8.0f;
	float centre = GetNoise(x, z) / 4.0f;
	return corners + sides + centre;
}



double HeightGenerator::interpolate(double a, double b, double blend)
{
	float f = (1.0f - cos(blend * 3.14156)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

double HeightGenerator::GetInterpolatedNoise(float x, float z)
{
	int intX = (int)x;
	int intZ = (int)z;
	float fracX = x - intX;
	float fracZ = z - intZ;
	float v1 = GetSmoothNoise(intX,		intZ);
	float v2 = GetSmoothNoise(intX + 1, intZ);
	float v3 = GetSmoothNoise(intX,		intZ + 1);
	float v4 = GetSmoothNoise(intX + 1, intZ + 1);
	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracZ);
}
