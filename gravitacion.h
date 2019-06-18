#ifndef _GRAVITACION
#define _GRAVITACION

#include <stdlib.h>
#include <cmath>
#include<vector>


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

#endif