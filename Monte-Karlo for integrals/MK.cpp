#include <iostream>
#include <random>
#include <math.h>

double randMToN(double M, double N)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<double> distr(M, N);

	return distr(eng);
}

double f(double x)
{
	return pow(x, 4);
}

int main()
{
	setlocale(LC_ALL, "ru");
	const long double pres = 1000000; // accuracy

	double start = 0; std::cout << "Lower limit:  "; std::cin >> start;
	double end = 0; std::cout << "Upper limit: ";  std::cin >> end;

	if (std::cin.fail())
	{
		return 0;
	}	

	if (start == end)
	{
		std::cout << "Integral = 0";
		return 0;
	}

	double max = 0.f;

	for (double i = start; i <= end; i += 0.000001) if (abs(max) <= abs(f(i))) max = f(i);

	double rec = abs(end - start) * abs(max);
	long double p = 0, pabs = 0;

	for (int i = 0; i < pres; i++)
	{
		double rx = randMToN(start,end);
		double ry = max > 0 ? randMToN(0.0f, max) : randMToN(max, 0.0f);

		if (ry <= f(rx) && max > 0) p++;
		if (abs(ry) <= abs(f(rx))) pabs++;
	}

	printf("Integral = %2.3f", 2 * rec * (p / pres) - rec * (pabs / pres));
}