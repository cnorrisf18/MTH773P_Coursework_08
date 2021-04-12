#pragma once
struct Results
{
	double area;
	double error;
	double num_steps;
	double delta;
	double gamma;
};


double IndicatorFunction(double x, double y);
Results EstimateD(const int num_steps);
Results EstimateWithAcc(const double acc_req);
Results RangeAccrualMC();