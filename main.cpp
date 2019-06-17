#include<iostream>
#include "cuerpo.h"
#include "gravitacion.h"

using namespace std;

int main(int argc, char const *argv[])
{
	double masa = 6371;
	double radio = 5.9;
	cout << sim(70,0,0,0,0,masa,radio) <<endl;
	return 0;
}