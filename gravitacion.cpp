#include "cuerpo.h"
#include "gravitacion.h"

using namespace std;

Simulacion sim(double ms, double mp, double rp, int na, double rd){

	std::vector<cuerpo> asteroides;
	double angulo;
	std::mt19937 generator;
	generator.seed(std::time(0));	
	std::uniform_int_distribution<uint32_t> angle(0,360);
	angulo = angle(generator)*3.14159265359/180;

	double radio_asteroide;

	double G = 6.674*(pow(10,-11));
	double radio_sol = 7*pow(10,8);
	cuerpo *sol = new cuerpo(ms, 0, 0, 0, 0, radio_sol);
	double radio_planeta = 7*pow(10,7);
	cuerpo *planeta = new cuerpo(mp, rp*cos(angulo), rp*sin(angulo), pow(G*ms/rp,0.5)*sin(angulo), -pow(G*ms/rp,0.5)*cos(angulo), radio_planeta);

	// Aqui creamos los asteroides

	std::uniform_int_distribution<uint_fast64_t> pos(0,rd);
	for (int i = 0; i < na; ++i)
	{
		double y = pos(generator) - rd/2;
		double x = pos(generator) - rd/2;

		radio_asteroide = pow((x*x) + (y*y),0.5);
		while (radio_asteroide > rd)
		{
			double y = pos(generator) - rd/2;
			double x = pos(generator) - rd/2;
			radio_asteroide = pow((x*x) + (y*y),0.5);
		}
		angulo = atan2(y,x);
		cuerpo *asteroide = new cuerpo(pow(10,18), x, y, pow(G*ms/radio_asteroide,0.5)*sin(angulo), -pow(G*ms/radio_asteroide,0.5)*cos(angulo), 0);
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

void Simulacion::Interactuar_objetos(cuerpo& c1, cuerpo& c2){
	std::vector<double> fuerza = Calcular_fuerza(c1,c2);
	c1.fx += fuerza[0];
	c1.fy += fuerza[1];
	c2.fx += -fuerza[0];
	c2.fy += -fuerza[1];
}

void Simulacion::Mover_objetos(cuerpo& c1){
	c1.vx += c1.fx*86400/c1.masa;
	c1.vy += c1.fy*86400/c1.masa;
	c1.x += c1.vx*86400;
	c1.y += c1.vy*86400;
}

std::vector<cuerpo> Simulacion::run(double tiempo){
	double radio_PlanetaAsteroides;
	double radio_SolAsteroides;
	double delta_x;
	double delta_y;
	for (int i = 0; i < tiempo; ++i)
	{
		sol.fx = 0;
		sol.fy = 0;
		planeta.fx = 0;
		planeta.fy = 0;

		for (double i = 0; i < asteroides.size(); ++i)
		{
			asteroides[i].fx = 0;
			asteroides[i].fy = 0;
			Interactuar_objetos(sol, asteroides[i]);
		}
		if (!planeta.colision)
		{
			Interactuar_objetos(sol, planeta);

			for (double i = 0; i < asteroides.size(); ++i)
			{
				Interactuar_objetos(planeta, asteroides[i]);
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
				asteroides.erase(asteroides.begin() + i);
			}
			else if (radio_SolAsteroides <= sol.radio)
			{
				sol.masa += asteroides[i].masa;
				asteroides.erase(asteroides.begin() + i);
			}
		}
		
		Mover_objetos(sol);
		if (!planeta.colision)
		{
			Mover_objetos(planeta);
		}
		for (double i = 0; i < asteroides.size(); ++i)
		{
			Mover_objetos(asteroides[i]);
		}

	}

	std::vector<cuerpo> cuerpos;
	cuerpos.push_back(sol);
	if (!planeta.colision)
	{
		Mover_objetos(planeta);
		cuerpos.push_back(planeta);
	}
	for (double i = 0; i < asteroides.size(); ++i)
	{
		Mover_objetos(asteroides[i]);
		cuerpos.push_back(asteroides[i]);
	}
	return cuerpos;
}