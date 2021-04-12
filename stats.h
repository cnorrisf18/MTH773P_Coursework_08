#pragma once
class Stats1
{
public:
	Stats1();
	void add(double num);
	double mean();
	double stDev();
	double length;
	double sumofnumbers;
private:


	double sumofsquare;
	double currentstDev;
	double currentmean;
	double currentdevsum;
};

class NormalRandomGenerator
{
public:
	NormalRandomGenerator();
	double generate();

private:
	bool usedZ1;
	double innerZ2;
};

class Stats2
{
public:
	Stats2();
	void add(double x, double y);
	double covariance() { return fcovariance; };
	double correlation() { return fcorrelation; };
	double m; //m and c are paramaters for fitting a straight line to the data (y=mx+c)
	double c;
	double rsquared;
private:
	double xsum;
	double xsqsum;
	double xvarsum;
	double xvar;
	double xbar;
	double ysum;
	double ysqsum;
	double yvarsum;
	double yvar;
	double ybar;
	double xysum;
	double length;
	double fcovariance;
	double fcorrelation;

};