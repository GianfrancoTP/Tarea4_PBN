#include "cuerpo.h"
#include "gravitacion.h"

using namespace std;

Simulacion sim(double ms, double mp, double rp, int na, double rd){

	std::vector<cuerpo> asteroides;

	double G = 6.674*(pow(10,-11));
	double radio_sol = 7*pow(10,8);
	cuerpo *sol = new cuerpo(ms, 0, 0, 0, 0, radio_sol);
	double radio_planeta = 7*pow(10,7);
	cuerpo *planeta = new cuerpo(mp, 0, rp, pow(G*ms/rp,0.5)*6/7, 0, radio_planeta);

	// Aqui creamos los asteroides

	std::mt19937 generator;
	generator.seed(std::time(0));	
	std::uniform_int_distribution<uint32_t> pos(0,2*rd);
	double radio_asteroide;

	int contador = 0;
	for (int i = 0; i < na; ++i)
	{
		double y = pos(generator) - rd;
		double x = pos(generator) - rd;

		radio_asteroide = pow(pow(x,2) + pow(y,2),0.5);
		while ((radio_asteroide > rd) & (contador < 100))
		{
			double y = pos(generator) - rd;
			double x = pos(generator) - rd;
			radio_asteroide = pow(pow(x,2) + pow(y,2),0.5);
			contador++;
		}
		cuerpo *asteroide = new cuerpo(pow(10,18), 0*x, 0*y + rp*9/10, 0, 0, 0);
		asteroides.push_back(*asteroide);
	}
	Simulacion *s = new Simulacion(sol, planeta, asteroides);
	return *s;
}

Simulacion::Simulacion(cuerpo *sol, cuerpo *planeta, vector<cuerpo> asteroides){
	this -> sol = *sol;
	this -> planeta = *planeta;
	this -> asteroides = asteroides;
}

std::vector<double> Simulacion::Calcular_fuerza(cuerpo c1, cuerpo c2){
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

void Simulacion::Interactuar_objetos(cuerpo c1, cuerpo c2){
	std::vector<double> fuerza = Calcular_fuerza(c1,c2);
	c1.vx += fuerza[0]*86400/c1.masa;
	c1.vy += fuerza[1]*86400/c1.masa;
	c1.x += c1.vx*86400;
	c1.y += c1.vy*86400;
	c2.vx += -fuerza[0]*86400/c2.masa;
	c2.vy += -fuerza[1]*86400/c2.masa;
	c2.x += c2.vx*86400;
	c2.y += c2.vy*86400;
}

std::vector<cuerpo> Simulacion::run(double tiempo){

	double radio_PlanetaAsteroides;
	double radio_SolAsteroides;
	std::vector<double> fuerza;
	double delta_x;
	double delta_y;
	for (int i = 0; i < tiempo; ++i)
	{
		for (double i = 0; i < asteroides.size(); ++i)
		{
			fuerza = Calcular_fuerza(sol, asteroides[i]);
			asteroides[i].vx += -fuerza[0]*86400/asteroides[i].masa;
			asteroides[i].vy += -fuerza[1]*86400/asteroides[i].masa;
			asteroides[i].x += 86400*asteroides[i].vx;
			asteroides[i].y += 86400*asteroides[i].vy;
			sol.vx += fuerza[0]*86400/sol.masa;
			sol.vy += fuerza[1]*86400/sol.masa;
			sol.x += 86400*sol.vx;
			sol.y += 86400*sol.vy;
		}
		if (!planeta.colision)
		{
			std::vector<double> fuerza = Calcular_fuerza(sol,planeta);
			sol.vx += fuerza[0]*86400/sol.masa;
			sol.vy += fuerza[1]*86400/sol.masa;
			sol.x += 86400*sol.vx;
			sol.y += 86400*sol.vy;
			planeta.vx += -fuerza[0]*86400/planeta.masa;
			planeta.vy += -fuerza[1]*86400/planeta.masa;
			planeta.x += 86400*planeta.vx;
			planeta.y += 86400*planeta.vy;

			for (double i = 0; i < asteroides.size(); ++i)
			{
				fuerza = Calcular_fuerza(planeta, asteroides[i]);
				asteroides[i].vx += -fuerza[0]*86400/asteroides[i].masa;
				asteroides[i].vy += -fuerza[1]*86400/asteroides[i].masa;
				asteroides[i].x += 86400*asteroides[i].vx;
				asteroides[i].y += 86400*asteroides[i].vy;
				planeta.vx += fuerza[0]*86400/planeta.masa;
				planeta.vy += fuerza[1]*86400/planeta.masa;
				planeta.x += 86400*planeta.vx;
				planeta.y += 86400*planeta.vy;
			}

			// Sacar distancia entre planeta y sol para luego ver si hay colisión
			delta_x = planeta.x - sol.x;
			delta_y = planeta.y - sol.y;
			double radio_PlanetaSol = pow((delta_x*delta_x) + (delta_y*delta_y),0.5);

			if (radio_PlanetaSol <= sol.radio)
			{
				sol.masa += planeta.masa;
				sol.vx += planeta.vx;
				sol.vy += planeta.vy;
				planeta.masa = 0;
				planeta.vx = 0;
				planeta.vy = 0;
				planeta.colision = true;
			}
		}
		for (double i = 0; i < asteroides.size(); ++i)
		{
			delta_x = planeta.x - asteroides[i].x;
			delta_y = planeta.y - asteroides[i].y;
			radio_PlanetaAsteroides = pow((delta_x*delta_x) + (delta_y*delta_y),0.5);
			delta_x = sol.x - asteroides[i].x;
			delta_y = sol.y - asteroides[i].y;
			radio_SolAsteroides = pow((delta_x*delta_x) + (delta_y*delta_y),0.5);
			if (radio_PlanetaAsteroides <= planeta.radio)
			{
				planeta.masa += asteroides[i].masa;
				planeta.vx += asteroides[i].vx;
				planeta.vy += asteroides[i].vy;
				asteroides.erase(asteroides.begin() + i);
			}
			else if (radio_SolAsteroides <= sol.radio)
			{
				sol.masa += asteroides[i].masa;
				sol.vx += asteroides[i].vx;
				sol.vy += asteroides[i].vy;
				asteroides.erase(asteroides.begin() + i);
			}
		}
	}

	std::vector<cuerpo> cuerpos;
	cuerpos.push_back(sol);
	if (!planeta.colision)
	{
		cuerpos.push_back(planeta);
	}
	for (double i = 0; i < asteroides.size(); ++i)
	{
		cuerpos.push_back(asteroides[i]);
	}
	return cuerpos;
}