#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

double function(double const& x, std::vector<double> const& param) {
	auto F = param[0];
	auto q = param[1];
	auto a = param[2];
	auto h = param[3];
	return (F / q) * (cosh(q * x / F) - cosh(q * a / (2 * F))) + h;
} 

template<typename Function>
double Richardson(double const& x, Function const& func, double delta, int order, std::vector<double> const& param) {
	if (order==2){
		return (func(x + delta, param) - func(x - delta, param)) / (2 * delta);
	}
	else {
		double temp1 = Richardson(x, func, delta, order - 2, param), temp2 = Richardson(x, func, 2 * delta, order - 2, param);
		return (pow(2,order - 2) * temp1 - temp2) /(pow(2, order - 2) - 1);
	}
}

template<typename Function>
double rectint(Function const& func, double const& start, double const& end, int const& n, std::vector<double> const& param) {
	double delta = (end - start) / n,result = 0;
	for (int i = 0; i <= n; i++) {
		result += sqrt(1 + pow(Richardson(start + (i + 1 / 2) * delta, func, delta, 6, param),2)) * delta;
	}
	return result;
}

template<typename Function>
double trapint(Function const& func, double const& start, double const& end, int const& n, std::vector<double> const& param) {
	double delta = (end - start) / n, result = 0;
	for (int i = 0; i <= n; i++) {
		result += sqrt(1 + pow(Richardson(start + i * delta, func, delta, 6, param), 2)) * delta;
	}
	result -= sqrt((1 + pow(Richardson(start, func, delta, 6, param), 2)) + (1 + pow(Richardson(end, func, delta, 6, param), 2))) * delta / 2;
	return result;
}

template<typename Function>
double simpsint(Function const& func, double const& start, double const& end, int const& n, std::vector<double> const& param) {
	double delta = (end - start) / n, result = 0;
	for (int i = 1; i < n; i++) {
		if (i % 2 == 0) {
			result += 4*sqrt(1 + pow(Richardson(start + i * delta, func, delta, 6, param), 2));
		}
		else {
			result += 2*sqrt(1 + pow(Richardson(start + i * delta, func, delta, 6, param), 2));
		}
		
	}
	result += sqrt(1 + pow(Richardson(start, func, delta, 6, param), 2)) + sqrt(1 + pow(Richardson(end * delta, func, delta, 6, param), 2));
	return result * delta / 3;
}

int main() {
	std::vector<double> param = { 900,1.8,200,35 };
	std::ofstream result ("results.txt");
	result << rectint(function, -100, 100, 50000, param) << ", " << trapint(function, -100, 100, 50000, param) << ", " << simpsint(function, -100, 100, 50000, param);   //50000 lépéssel az analitikus megoldástól már csak 10^-3 rendben tért el az eredmény
	result.close();
	return 0;
}