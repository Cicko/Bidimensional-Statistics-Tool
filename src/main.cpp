#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "estadistica.cpp"
using namespace std;



int main(int argc, char *argv[]) {

	//char file[][] = {"1.data","2.data"};	
 
	EstadisticaDescriptiva E(argv[1]);

	E.mostrar();

	cout << endl;
	for(int i = 0; i < 2; i++)	
	{	
		cout << "La media de variable " << i <<  " es : " << E.media(i) << endl;	
		cout << "La varianza de variable "<< i << " es : " << E.varianza(i) << endl;
		cout << "La DT de variable " << i << " es : " << E.dt(i) << endl;
		cout << "El CV de variable " << i << " es : " << E.cv(i) << " % " << endl;
		cout << endl;
	}
	cout << "La covarianza es  : " << E.covarianza() << endl;
	cout << "El coeficiente de correlacion : " << E.cc() << endl;
	cout << "El coeficiente de determinacion : " << E.cd() << endl;
	cout << endl;
	E.mostrarRectas();
	return 0;
}

