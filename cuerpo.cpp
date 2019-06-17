#include "cuerpo.h"
#include <cmath>

cuerpo::cuerpo(double masa, double x, double y, double vx, double vy){
	this -> masa = masa;
	this -> x = x;
	this ->  y = y;
	this ->  vx = vx;
	this ->  vy = vy;
}

double cuerpo::Ley_gun(double masa1, double radio){
	double f;
	double G = 6.674*(pow(10,-11));
	f = G*masa1*(masa)/(radio*radio);
	return f;
}