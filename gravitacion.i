%module gravitacion
%{
#include"cuerpo.h"
#include"gravitacion.h"
%}

%include"std_vector.i"

namespace std {
	%template(vdob) vector<double>;
	%template(vcuerpo) vector<cuerpo>;
}

class Simulacion{
public:
	cuerpo sol;
	cuerpo planeta;
	std::vector<cuerpo> asteroides;

	Simulacion(cuerpo *sol, cuerpo *planeta);
	std::vector<double> Calcular_fuersas(cuerpo c1, cuerpo c2);
	std::vector<cuerpo> run(double tiempo);
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
