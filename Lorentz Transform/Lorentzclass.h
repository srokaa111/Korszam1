#pragma once
#include <math.h>
#include <iostream>
#include <vector>
#include<cmath>

template<typename V, typename M>
std::vector<M> Mat4prod(M Mat[4][4], std::vector<V> Vec) {  //4x4 Matrix and 4 Vector product
	std::vector<M> Res = {0,0,0,0};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j <4; j++) {
			Res[i] += Mat[i][j]*Vec[j];
		}
	}
	return Res;
}

template<typename T,typename U,typename V,typename W>
class Lorentz {
public:
	std::vector<T> pos = {t,x,y,z};    //Position of the event
	std::vector<T> speed = {x,y,z};    //Speed of the frame of reference

	Lorentz& xboost(T v1) {				//Simple boost
		int c = 299'792'458;
		auto beta = (v1-speed[0]) / c;
		auto gamma = 1/sqrt(1 - pow(beta,2));
		double time = gamma * (c * pos[0] - beta * pos[1]) / c;
		pos[1] = gamma * (pos[1] - beta* c * pos[0]);
		pos[0] = time;
		speed[0] += v1;
		return *this;
	}

	std::vector<U> Boost(std::vector<V> v) {           //Boost in an arbitrary direction
		int c = 299'792'458;
		auto vtot = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
		auto sp = sqrt(speed[0] * speed[0] + speed[1] * speed[1] + speed[2] * speed[2]);
		pos[0] *= c;
		auto beta = (vtot - sp) / c;
		auto gamma = 1 / sqrt(1 - pow(beta, 2));
		speed[0] += v[0]; speed[2] += v[2]; speed[2] += v[2];
		U Rotmat[4][4] = { {gamma,-gamma * v[0] / c,-gamma * v[1] / c,-gamma * v[2] / c}, {-gamma * v[0] / c,1 + (gamma - 1) * pow(v[0] / vtot,2),(gamma - 1) * v[1] * v[0] / (vtot * vtot),(gamma - 1) * v[2] * v[0] / (vtot * vtot)}, {-gamma * v[1] / c,(gamma - 1) * v[1] * v[0] / (vtot * vtot),1 + (gamma - 1) * pow(v[1] / vtot,2),(gamma - 1) * v[2] * v[1] / (vtot * vtot)}, {-gamma * v[2] / c,(gamma - 1) * v[2] * v[0] / (vtot * vtot),(gamma - 1) * v[2] * v[1] / (vtot * vtot),1 + (gamma - 1) * pow(v[2] / vtot,2)} };
		return Mat4prod<V, U>(Rotmat, pos);
	}

	std::vector<U> Rotx(W angle) {             //Rotations about x, y and z
		U Mat[4][4] = { {1,0,0,0}, {0,1,0,0},{0,0,cos(angle),-sin(angle)},{0,0,sin(angle),cos(angle)} };
		return Mat4prod<W, U>(Mat, pos);
	}
	
	std::vector<U> Roty(W angle) {
		U Mat[4][4] = { {1,0,0,0}, {0,cos(angle),0,sin(angle)},{0,0,1,0},{0,-sin(angle),0,cos(angle)} };
		return Mat4prod<W, U>(Mat, pos);
	}

	std::vector<U> Rotz(W angle) {
		U Mat[4][4] = { {1,0,0,0}, {0,cos(angle),sin(angle),0},{0,-sin(angle),cos(angle),0},{0,0,0,1} };
		return Mat4prod<W, U>(Mat, pos);
	}

	auto rapidity() {                    //Rapidity
		int c = 299792458;
		auto sp = sqrt(speed[0] * speed[0] + speed[1] * speed[1] + speed[2] * speed[2]);
		return atanh(sp / c);
	}

	auto length() {                      //The length of the four-vector
	int c = 299792458;
	return sqrt(pow(c * pos[0], 2) - (pow(pos[1], 2) + pow(pos[2], 2) + pow(pos[3], 2)));
	}

	Lorentz& timerev() {                 //Time reversal
		pos[0] = -pos[0];
		return *this;
	}

	Lorentz& parity() {                  //Parity
		pos[1] = -pos[1];
		pos[2] = -pos[2];
		pos[3] = -pos[3];
		return *this;
	}
};
