#include "cuerpo.h"
#include "gravitacion.h"

double sim(double masa, double x, double y, double vx, double vy, double masa1, double radio){
	cuerpo *c = new cuerpo(masa, x, y, vx, vy);
	return c->Ley_gun(masa1, radio);
}
