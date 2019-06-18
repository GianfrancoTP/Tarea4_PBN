#include<iostream>
#include "cuerpo.h"
#include "gravitacion.h"

using namespace std;

int main(int argc, char const *argv[])
{
	double r_disco=3e12;
	Simulacion s = sim(1.988e30, 1.898e27,  7.7857e11, 5000, r_disco);
	vector<cuerpo> r=s.run(1);


	return 0;
}