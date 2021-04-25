#include<math.h>
#include<vector>
#include<iostream>
#include<fstream>

double deriv(double const& y){
	return 1 + pow(y,2);
}

template<typename Function>
std::vector<double> Euler(double const& y0, Function const& f, double const& h, int const& steps) {
	std::vector<double> out;
	double y;
	out.push_back(y0);
	for (int i = 1; i < steps; i++) {
		y = out.back();
		out.push_back(y + h * f(y));
	}
	return out;
}

template<typename Function>
std::vector<double> RK4(double const& y0, Function const& f, double const& h, int const& steps) {
	std::vector<double> out;
	double y;
	double k1, k2, k3, k4;
	out.push_back(y0);
	for (int i = 1; i < steps; i++) {
		y = out.back();
		k1 = f(y);
		k2 = f(y + h * 0.5 * k1);
		k3 = f(y + h * 0.5 * k2);
		k4 = f(y + h * k3);
		out.push_back(y + (k1 + k4 + 2 * (k2 + k3)) * (h / 6));
	}
	return out;
}

int main() {
	std::vector<double> RKres,Eures;
	int stepnum = 1000;
	double rk4, euler;
	double delta = (3.14159 / 2) / stepnum;
	Eures = Euler(0, deriv, delta, stepnum);
	RKres = RK4(0, deriv, delta, stepnum);
	std::ofstream result("results.txt");
	result << "Time\t\tNewton-method\tRunge-Kutta\tAnalytic\n";
	result << "0" << "\t\t" << Eures[0] << "\t\t" << RKres[0] << "\t\t" << tan(0) << "\n";
	for (int i = 1; i < stepnum; i++) {
		euler = Eures[i];
		rk4 = RKres[i];
		result << i * delta << "    \t" << euler <<"     \t" << rk4 << "    \t" <<tan(i*delta) <<"\n";
	}
	return 0;
}