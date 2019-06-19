#ifndef _Cuerpo
#define _Cuerpo

class cuerpo{

public:
	double masa;
	double x;
	double y;
	double vx;
	double vy;
	double fx;
	double fy;
	double radio;
	bool colision = false;

	cuerpo(double masa, double x, double y, double vx, double vy, double radio);
	cuerpo() {};
};

#endif