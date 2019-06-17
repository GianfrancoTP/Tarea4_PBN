%module gravitacion
%{
#include"cuerpo.h"
#include"gravitacion.h"
%}

double sim(double masa, double x, double y, double vx, double vy, double masa1, double radio);

class cuerpo{

public:
	double masa;
	double x;
	double y;
	double vx;
	double vy;

	cuerpo(double masa, double x, double y, double vx, double vy);
	double Ley_gun(double masa1, double radio);
};
