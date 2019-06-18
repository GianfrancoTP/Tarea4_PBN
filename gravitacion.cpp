#include "cuerpo.h"
#include "gravitacion.h"

using namespace std;

Simulacion sim(double ms, double mp, double rp, int na, double rd){
	double G = 6.674*(pow(10,-11));
	double radio_sol = 7*pow(10,8);
	cuerpo *sol = new cuerpo(ms, 0, 0, 0, 0, radio_sol);
	double radio_planeta = 7*pow(10,7);
	cuerpo *planeta = new cuerpo(mp, 0, rp, pow(G*ms/(rp),0.5), 0, radio_planeta);
	Simulacion *s = new Simulacion(sol, planeta);
	return *s;
}

Simulacion::Simulacion(cuerpo *sol, cuerpo *planeta){
	this -> sol = *sol;
	this -> planeta = *planeta;
}

std::vector<double> Simulacion::Calcular_fuersas(cuerpo c1, cuerpo c2){
	double G = 6.674*(pow(10,-11));
	// Calculo del angulo entre ambos cuerpos
	double angulo;
	double delta_x = c2.x - c1.x;
	double delta_y = c2.y - c1.y;
	angulo = atan2((double)delta_y,(double)delta_x);
	//Calculo de las fuerzas en el eje X e Y
	double magnitud_F = (G*c1.masa*c2.masa)/((delta_x*delta_x) + (delta_y*delta_y));
	double fx = magnitud_F*cos(angulo);
	double fy = magnitud_F*sin(angulo);
	std::vector<double> r;
	r.push_back(fx);
	r.push_back(fy);
	return r;
}

std::vector<cuerpo> Simulacion::run(double tiempo){

	for (int i = 0; i < tiempo; ++i)
	{
		std::vector<double> fuerzas = Calcular_fuersas(sol,planeta);
		sol.vx += fuerzas[0]*86400/sol.masa;
		sol.vy += fuerzas[1]*86400/sol.masa;
		sol.x += 86400*sol.vx;
		sol.y += 86400*sol.vy;
		planeta.vx += -fuerzas[0]*86400/planeta.masa;
		planeta.vy += -fuerzas[1]*86400/planeta.masa;
		planeta.x += 86400*planeta.vx;
		planeta.y += 86400*planeta.vy;
	}
	std::vector<cuerpo> cuerpos;
	cuerpos.push_back(sol);
	cuerpos.push_back(planeta);
	return cuerpos;
}