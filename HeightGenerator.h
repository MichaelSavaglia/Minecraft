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
};

