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

	Simulacion(cuerpo *sol, cuerpo *planeta, std::vector<cuerpo> asteroides);
	std::vector<double> Calcular_fuerza(cuerpo c1, cuerpo c2);
	void Interactuar_objetos(cuerpo c1, cuerpo c2);
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
	bool colision = false;

	cuerpo(double masa, double x, double y, double vx, double vy, double radio);
	cuerpo() {};
};
