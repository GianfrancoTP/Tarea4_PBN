#ifndef _GRAVITACION
#define _GRAVITACION

#include<iostream>
#include <stdlib.h>
#include <cmath>
#include <random>
#include<ctime>
#include<vector>


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

#endif