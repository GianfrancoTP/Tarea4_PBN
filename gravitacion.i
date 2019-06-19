%module gravitacion
%{
#include"cuerpo.h"
#include"gravitacion.h"
%}

%include"std_vector.i"

namespace std {
	%template(vdob) vector<double>;
	%template(vcuerpo) vector<cuerpo>;
}

%include "cuerpo.h"
%include "gravitacion.h" 