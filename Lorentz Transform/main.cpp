#include "Lorentzclass.h"

int main(){
	Lorentz<double, double, double, double> test1 = { {0,0,0,0 },{0,0,0} }, test2 = { {0,0,0,0 },{0,0,0} };
	int c = 299'792'458;
	double angle, simpspeed;
	std::vector<double> arbspeed = { 0,0,0 };
	std::cout << "The position of the event (in t,x,y,z coordinates): \n";
	std::cin >> test1.pos[0] >> test1.pos[1] >> test1.pos[2] >> test1.pos[3];
	test2 = test1;
	std::cout << "\nSpeed of the simple boost: \n";
	std::cin >> simpspeed;
	test1.xboost(simpspeed);    //Testing the simple boost
	std::cout <<"\nSimple boost: \n" <<"x: "<< test1.pos[1] << "\ty: " << test1.pos[2] << "\t\tz: " << test1.pos[3] << "\t\tt: " << test1.pos[0] << "\n";
	std::cout << "\nSpeed of the arbitrary boost: \n";
	std::cin >> arbspeed[0] >> arbspeed[1] >> arbspeed[2];
	Lorentz<double, double, double, double> test3 = { test2.Boost(arbspeed),arbspeed };  //Testing the arbitrary boost
	test2.pos[0] /= c;
	std::cout << "\nArbitrary boost:\n" << "x: " << test3.pos[1] << "\ty: " << test3.pos[2] << "\tz: " << test3.pos[3] << "\tt: " << test3.pos[0] << "\n";
	std::cout <<"\nMagnitude of rapidity after boost:  "<< test1.rapidity() << '\n';      //Rapidity after the boost
	std::cout << "\nAngle of rotation: ";
	std::cin >> angle;
	std::vector<double> test4 = test2.Rotx(angle);           //Testing the rotation
	std::cout << "\nAfter rotation:\n" << "x: " << test4[1] << "\t\ty: " << test4[2] << "\tz: " << test4[3] << "\n";
	std::cout << "\nComparing the length of the four-vectors: \nBefore boost: " << test2.length() << "\nAfter boost: " << test2.length();   //Testing the invariance of the length
	return 1;
}