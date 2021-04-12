#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include "stats.h"
using namespace std;

//Stats1 class definitions

Stats1::Stats1()
{
	sumofnumbers = 0;
	sumofsquare = 0;
	length = 0;
	currentstDev = 0;
	currentmean = 0;
	currentdevsum = 0;
}
;
void Stats1::add(double num) { //add numbers in one at a time and sum them
	sumofnumbers += num;
	sumofsquare += pow(num, 2);
	length += 1.0;


}
double Stats1::mean() {
	return sumofnumbers / length;

}
double Stats1::stDev() {
	return sqrt((sumofsquare / length) - pow((sumofnumbers / length), 2));

}

NormalRandomGenerator::NormalRandomGenerator()
{
	usedZ1 = false;
	innerZ2 = 0;
};
double NormalRandomGenerator::generate()
{
	if (usedZ1 == true)
	{
		usedZ1 = false;
		return innerZ2;
	}
	else
	{
		double U1 = rand() / double(RAND_MAX);
		bool done = false;
		while (not done)
		{
			if (U1 == 0)
			{
				U1 = rand() / double(RAND_MAX);
			}
			else {
				done = true;
			}
		}
		double U2 = rand() / double(RAND_MAX);
		double Z1 = sqrt(-2.0 * log(U1)) * cos(2.0 * M_PI * U2);
		innerZ2 = sqrt(-2.0 * log(U1)) * sin(2.0 * M_PI * U2);
		usedZ1 = true;
		return Z1;
	}
}

Stats2::Stats2()
{
	xsum = 0;
	xsqsum = 0;
	xvarsum = 0;
	xvar = 0;
	xbar = 0;
	ysum = 0;
	ysqsum = 0;
	yvarsum = 0;
	yvar = 0;
	ybar = 0;
	xysum = 0;
	length = 0;
	fcovariance = 0;
	fcorrelation = 0;
	m = 0;
	c = 0;
	rsquared = 0;
};
void Stats2::add(double x, double y)
{
	xsum += x;
	xsqsum += pow(x, 2);
	ysum += y;
	ysqsum += pow(y, 2);
	xysum += (x * y);
	length += 1;
	xbar = xsum / length;
	ybar = ysum / length;
	//calculate covariance
	xvar = (xsqsum / length) - pow(xbar, 2);
	yvar = (ysqsum / length) - pow(ybar, 2);
	fcovariance = (xysum / length) - (xbar * ybar);
	//fcovariance = (xysum - (length * xbar * ybar)) / (length);
	fcorrelation = fcovariance / sqrt(yvar * xvar);
	//calculate m and c
	m = fcovariance / xvar;
	c = ybar - (m * xbar);
	rsquared = pow(((length * xysum) - (xsum * ysum)) / sqrt(((length * xsqsum) - pow(xsum, 2)) * ((length * ysqsum) - pow(ysum, 2))), 2);
}