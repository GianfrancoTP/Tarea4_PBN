%module gravitacion
%{
#include"cuerpo.h"
#include"gravitacion.h"
%}


class Simulacion{
public:
	cuerpo sol;
	cuerpo planeta;
	vector<cuerpo> asteroides;

	Simulacion(cuerpo *sol, cuerpo *planeta);
	vector<double> Calcular_fuersas(cuerpo c1, cuerpo c2);
	vector<cuerpo> run(double tiempo);
};

Simulacion sim(double ms, double mp, double rp, int na, double rd);

class cuerpo{

public:
	double masa;
	double x;
	double y;
	double vx;
	double vy;
	double radio;

	cuerpo(double masa, double x, double y, double vx, double vy, double radio);
	cuerpo() {};
};
