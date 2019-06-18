#ifndef _Cuerpo
#define _Cuerpo

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

#endif