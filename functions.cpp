#include "functions.h"
#include "stats.h"
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;




double IndicatorFunction(double x, double y)
{

	if (sqrt(pow(x, 2) + pow(y, 2)) <= 3 - cos(8.0 * acos(x / sqrt(pow(x, 2) + pow(y, 2)))))
	{
		return 1.0;
	}
	return 0.0;

}




Results EstimateD(const int num_steps)
{
	const double pi = 6.0*asin(0.5);
	const double lower_bound = 4.0 * pi; //12.5664
	const double upper_bound = 16.0 * pi; //50.2654
	const double S_area = 64.0;

	Stats1 indicator_points;
	NormalRandomGenerator RandomGen;

	for (int i = 0; i < num_steps; ++i)
	{
		double x = RandomGen.generate() * 2.0;
		double y = RandomGen.generate() * 2.0;
		indicator_points.add(IndicatorFunction(x, y));
	}

	Results MC_results;
	MC_results.area = S_area * indicator_points.mean();
	MC_results.error = indicator_points.stDev() / sqrt(num_steps - 1.0);
	MC_results.num_steps = num_steps;
	return MC_results; 

}

Results EstimateWithAcc(const double req_acc)
{
	const double pi = 6.0 * asin(0.5);
	const double lower_bound = 4.0 * pi; //12.5664
	const double upper_bound = 16.0 * pi; //50.2654
	const double S_area = 64.0;


	Stats1 indicator_points;
	NormalRandomGenerator RandomGen;
	
	double error = 1;
	int num_rounds = 10;

	for (int i = 0; i < num_rounds; ++i)
	{
		double x = RandomGen.generate() * 2.0;
		double y = RandomGen.generate() * 2.0;
		indicator_points.add(IndicatorFunction(x, y));
	}
	bool done = false;
	while (not done) 
	{
		double x = RandomGen.generate() * 2.0;
		double y = RandomGen.generate() * 2.0;
		indicator_points.add(IndicatorFunction(x, y));
		++num_rounds;

		error = indicator_points.stDev() / sqrt(num_rounds - 1.0);
		if (error <= req_acc)
		{
			done = true;
		}
	}
	Results MC_results;
	MC_results.area = S_area * indicator_points.mean();
	MC_results.error = error;
	MC_results.num_steps = num_rounds;
	return MC_results;

}

Results RangeAccrualMC()
{
	const double S_min = 100.0;
	const double S_max = 110.0;
	const double M = 1'000'000.0;
	const int D = 252;
	const double S0 = 105.0;
	const double sigma = 0.25;
	const double r = 0.05;
	const double T = 252.0 / 365.0;

	NormalRandomGenerator nrg; 
	int m = D;

	const double req_error = .001;

	const double dt = double(T) / m;
	const double drift = (r - sigma * sigma / 2.0) * dt;
	const double vol = sigma * sqrt(dt);

	Stats1 results_stats;
	Stats1 results_delta;
	int num_steps = 0;
	bool done = false;
	int d = 0;
	double payoff = 0;
	const int eps = 0.001;
	double error = 1.0;
	while (not done)
	{
		vector <double> S(m+1);
		S[0] = S0;
		for (int j = 1; j <= m; ++j)
		{
			const double z = nrg.generate();
			S[j] = S[j - 1] * exp(drift + vol * z);
			if(S[j] >= S_min && S[j] <= S_max) //value is inside the range.
			{
				++d;
			}
		}
		payoff = M * (double(d) / D);
		results_stats.add(payoff);
		d = 0;
		for (int j = 0; j <= m; ++j)
		{
			S[j] *= 1 + eps;
			if (S[j] >= S_min && S[j] <= S_max) //value is inside the range.
			{
				++d;
			}
		}
		double new_payoff = M * double(d) / D;
		//cout << payoff << "\t" << new_payoff << "\t" << new_payoff - payoff << endl;
		results_delta.add(new_payoff - payoff);
		//cout << results_delta.mean() << endl;
		++num_steps;
		d = 0;
		error = exp(-r * T) * (results_stats.stDev()/results_stats.mean()) / sqrt(num_steps-1);
		if (error <= req_error && num_steps > 10) //num steps > 10 is to stop small errors with too few num steps
		{
			done = true;
		}
	}
	Results results;
	results.area = exp(-r * T) * results_stats.mean();
	results.error = error;
	results.num_steps = num_steps;
	cout << results_delta.mean() << endl;
	results.delta = exp(-r * T) * results_delta.mean() / (S0 * eps);
	return results;
}