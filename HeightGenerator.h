#pragma once
class HeightGenerator
{
public:
	HeightGenerator(int seed);
	~HeightGenerator();


	int GenerateHeight(int x, int z);

private:
	const int mSeed;

	double GetNoise(double x, double z);
	double GetSmoothNoise(double x, double z);
	double interpolate(double a, double b, double blend);
	double GetInterpolatedNoise(float x, float z);

	float amplitude = 32.0f;
	int octaves = 7;
	float roughness = 0.53f;
};

