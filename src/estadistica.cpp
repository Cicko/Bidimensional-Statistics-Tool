#include <iostream>
#include <cstdlib>
#include <fstream>


using namespace std;

class EstadisticaDescriptiva{
	vector<float> datos1_;
	vector<float> datos2_; // Si es unidimensional el caso a estudiar este vector está vacío
	bool bidimensional_;
public:
	EstadisticaDescriptiva(char*);
	~EstadisticaDescriptiva();
	
	void mostrar() const;
	
	// Unidimensional
	float media(bool) const;
	float varianza(bool) const; // (Sigma al cuadrado)
	float dt(bool) const ; // Desviación típica ( sigma )
	float cv(bool) const; // Coeficiente de variación
	
	// Bidimensional
	
	float covarianza() const;
	float vr() const; // Varianza residual
	float cc() const; // Coeficiente de correlación
	float cd() const; // Coeficiente de determinación
	float ecm() const; // Error Cuadrático Medio

	void mostrarRectas() const; // Recta Regresión
	
};


EstadisticaDescriptiva::EstadisticaDescriptiva(char * fileName)
	:datos1_(),datos2_(),bidimensional_()
	{

		fstream fs(fileName, fstream::in );
		char buffer[1000];

		fs.getline(buffer,10,'\n');
		bidimensional_ = atoi(buffer);
		
		fs.getline(buffer,10,'\n');
		datos1_.reserve(atoi(buffer));

		if(bidimensional_)
		{
			fs.getline(buffer,10,'\n');
			datos2_.reserve(atoi(buffer));
		}

		cout << "Tamanio variable 1 : " << datos1_.capacity() << endl;
		cout << "Tamanio variable 2 : " << datos2_.capacity() << endl;
		
		for(int i = 0; i < datos1_.capacity(); i++)
		{
			if(i != datos1_.capacity()-1)
				fs.getline(buffer,256,' ');
			else
				fs.getline(buffer,256,'\n');
			datos1_.push_back(atof(buffer));	
		}

		if(bidimensional_)
		for(int i = 0; i < datos2_.capacity(); i++)
		{
			fs.getline(buffer,256,' ');
			datos2_.push_back(atof(buffer));
		}
	
		cout << endl << endl;

		fs.close();
	}

EstadisticaDescriptiva::~EstadisticaDescriptiva()
{}

float EstadisticaDescriptiva::media(bool var) const // Si var = 0 , media de la variable1 si var = 1 , media de la variable2
{
	float media = 0;
	int size = var ? datos2_.capacity() : datos1_.capacity();
	for(int i = 0; i < size; i++)
	{
		if(var)
			media += datos2_[i];
		else
			media += datos1_[i];
	}
	return media/size;
}


float EstadisticaDescriptiva::varianza(bool var) const
{
	float varianza = 0;
	int size = var ? datos2_.capacity() : datos1_.capacity();
	for(int i = 0; i < size; i++)
	{
		if(var)
			varianza += pow(datos2_[i] - media(var),2); 
		else
			varianza += pow(datos1_[i] - media(var),2); 
	}
	
	return varianza/size;
}

float EstadisticaDescriptiva::dt(bool var) const
{
	return sqrt(varianza(var));
}

float EstadisticaDescriptiva::cv(bool var) const
{
	return (dt(var) / media(var)) * 100;
}

void EstadisticaDescriptiva::mostrar() const
{
	
	cout << "Variable 1 : ";
	for(int i = 0; i < datos1_.capacity() ; i++)
		cout << datos1_[i] << " ";
	cout << endl;
	if(bidimensional_)
	{
		cout << "Variable 2 : ";
		for(int i = 0; i < datos2_.capacity(); i++)
			cout << datos2_[i] << " ";
		cout << endl;
	}
}


float EstadisticaDescriptiva::covarianza() const
{
	float cov = 0;
	for(int i = 0; i < datos1_.capacity(); i++)
			cov += datos1_[i]*datos2_[i];
	cov /= datos1_.capacity();
	cov -= media(0)*media(1);
		
	return cov;	
}


float EstadisticaDescriptiva::cc() const
{
	return covarianza() / (dt(0) * dt(1));
}


float EstadisticaDescriptiva::cd() const
{
	return pow(cc(),2);
}


void EstadisticaDescriptiva::mostrarRectas() const
{
	float a = covarianza() / varianza(0);
	float b = media(1) - (covarianza()/varianza(0))*media(0);

	cout << "La Recta Y/X ---->   y = " << a << "x + " << b << endl;

	a = covarianza() / varianza(1);
	b = media(0) - (covarianza()/varianza(1))*media(1);

	cout << "La Recta X/Y ---->   x = " << a << "y + " << b << endl;

}
