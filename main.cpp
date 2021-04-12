#include "stats.h"
#include "functions.h"
#include <iostream>
using namespace std;



int main()
{
	cout << EstimateD(1000).area << "\t" << EstimateD(1000).error << endl; //Area: 40.768, Error: 0.0150192, N = 1000
	cout << EstimateWithAcc(0.01).area << "\t" << EstimateWithAcc(0.01).error << "\t" << EstimateWithAcc(0.01).num_steps << endl; //Area: 42.4186, Error: 0.00999763,  N: 2230
	//1d) Specifiying the accuracy is probably pretty efficient because then the program can just run until it gets the required accuracy, while you have to keep testing different Ns for the other method

	/*
	1e) I think Monte-Carlo could be pretty useful with this one-dimensional integral. It may take more time than e.g. analytical methods but it would be pretty simple
	to implement. Generate a series of random stock prices, find the payoff with them (this would be different based on call or put options) and the probability density
	function g(St), keep the sum of g(St) * h(St), and divide the sum by the number of steps then multiply by e^rT to get the price. Code would look very similar to the 
	code samples in topic 12, just adding a pdf to the process.
	*/


	//2a) If a stock is pretty stable in price and doesn't do a lot of jumping around, it could be very profitable to purchase a range accrual note.

	Results accrual = RangeAccrualMC();
	cout << accrual.area << "\t" << accrual.error << "\t" << accrual.num_steps << "\t" << accrual.delta << endl;




	return 0;
}