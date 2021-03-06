#ifndef NEURONA_H
#define NEURONA_H


using namespace std;

class Neurona{
	//variables
	vector<double> w; //pesos
	vector<int> clase;
	int identificador; //numero de neurona
	double diferenciaW; //diferencia peso actual-peso anterior
	
public:
	//constructor
	Neurona(int cantidad, int id){
		generarPesos(cantidad,w);
		identificador=id;
		
		// las 3 clases
		clase.push_back(0);
		clase.push_back(0);
		clase.push_back(0);
	}
	
	// Mostrar los Pesos
	void mostrarPesos(){show(w);}
	
	//metodos
	vector<double> pesos(){return w;}
	
	// actualizar pesos
	void newPesos(vector<double> wx){w=wx;}
	
	// actualiza la diferencia
	void diferencia(double diff){diferenciaW=diff;}
	
	// retorna las diferencias
	double diferencia(){return diferenciaW;}
	
	
	void claseUP(int c){clase[c] = clase[c] +1;}
	
	int claseReturn(){
		if(clase[0]>clase[1])
			return 0;
		return 1;
	}
	
	//Funcion distancia euclidea
	double distancia(Neurona x1){
		int n1=x1.w.size(),n2=w.size();
		double suma=0,dif=0;
		// Control
		if (n1!=n2){
			cout<<"ERROR - Vectores de diferente dimension"<<endl<<endl;
			return 0;}
		
		for(int i=0; i<n1; i++){
			dif=x1.w[i]-w[i];
			suma+=dif*dif;
		}
		return sqrt(suma);
	}
	
	void posXY(int xsize, int &x,int &y){
		x=identificador/xsize;
		y=identificador-x*xsize;
	}
	
	
};

#endif
