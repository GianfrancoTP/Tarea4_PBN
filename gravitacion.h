#ifndef _GRAVITACION
#define _GRAVITACION

#include <stdlib.h>
#include <cmath>
#include<vector>
using namespace std;


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

#endif