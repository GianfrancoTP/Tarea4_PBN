#include<iostream>
#include <cmath>
#include "cuerpo.h"
#include "gravitacion.h"

using namespace std;

int main(int argc, char const *argv[])
{
	argv += 'c';
	int a;
	double r_disco=3e12;
	Simulacion s = sim(1.988e30, 1.898e27,  7.7857e11, 50, r_disco);

	for (double i = 0; i < s.asteroides.size(); ++i)
	{
		double x = s.asteroides[i].x;
		double y = s.asteroides[i].y;
		double b = pow((x*x) + (y*y),0.5);
		cout << b << ' ' << (b < r_disco) << endl;
		a += argc;
	}
	vector<cuerpo> r=s.run(1);


	return 0;
}