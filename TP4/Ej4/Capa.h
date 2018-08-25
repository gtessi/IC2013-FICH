

using namespace std;


class Capa{
	
private:
	mdouble w,dw; // Matriz de pesos
	vdouble y,delta; // salidas y deltaiente (las entradas es al pedo, porque
	// terminás redundando datos al pedo...
	bool lastc; // si es la ultima capa
	double nu = 0.1,epsilon=0.6;

public:
	
	// Constructor
	Capa(int cantEntradas, int cantNeuronas, bool last){
		
		vdouble aux;
		
		for (int i=0; i<cantNeuronas;i++){
			generarPesos(cantEntradas,aux);
			w.push_back(aux);
			generarZeros(cantEntradas,aux);
			dw.push_back(aux);
		}
		lastc=last;
	}
	
	// Constructor vacio
	
	// Calcula el deltaiente de error en dicha capa
	void caldelta(vdouble &yd_delta, bool notPrimera){
//		// La cantidad de salidas obtenidas 
//		// tiene que ser igual a la cantidad real

		if(yd_delta.size()!=y.size()-1 && !lastc){
			cout<<"Error caldeltaiente"<<endl<<yd_delta.size()<<"  "<<y.size()-1<<endl<<endl;
			return;
		}
		
		// vaciamos el vector delta
		delta.clear();
		
		// creamos una matriz peso sin los w0
		mdouble aux_w = w;
		
		// aliminamos el w0 y andabien.
		for(int i=0;i<aux_w.size();i++){
			aux_w[i].erase(aux_w[i].begin());
		}
		
		// realizamos el caso particular de la ultima capa
		double aux=0;
		if(lastc){
			delta.clear();
			for(int i=0;i<w.size(); i++){
				aux=(1+y[i])*(1-y[i])*(yd_delta[i]-y[i])/2;
				delta.push_back(aux);
				aux=0;
			}
			yd_delta.clear();
			productoVM(delta,aux_w,yd_delta);
			return;
		}
		
		// Falta poner el factor 1/2 que viene de la derivada
		// que facilmente se podría meter en factor de aprendizaje
		for(int i=0;i<w.size();i++){
			aux=yd_delta[i]*(1+y[i+1])*(1-y[i+1])/2;
			delta.push_back(aux);
		}
		
		// Calculamos el deltaiente de error para cada neurona 
		// de la capa
		if(notPrimera)
			productoVM(delta,aux_w,yd_delta);
		
	}
	
	void deltaiente(vdouble deltaiente){
		delta=deltaiente;
	}
	
	// Calcula la salidas con las entradas como referencia
	void calcularSalidas(vdouble x){
		productoMV(w,x,y);
		if(!lastc)
			y.insert(y.begin(),-1.0);
	}
	
	// Actualizar los pesos
	void actualizarPeso(vdouble &x){
		
		int cantNeu = w.size(),canEntra=x.size();
		double aux=0;
		for(int i=0; i<cantNeu;i++){
			for(int j=0;j<canEntra;j++){
				aux=w[i][j];
				// epsilon*(w(n) - w(n-1))
				w[i][j] = w[i][j] + nu*delta[i] * x[j] + epsilon*(w[i][j] - dw[i][j]);
				dw[i][j]= aux;
				
			}
		}
		x.clear();
		x=y;
	}
	
	
	void salidas(vdouble &salida){
		salida.clear();
		salida=y;
	}
	
	
	
	void savePeso(){
		savePesos(w, "pesosFinales.csv");
	}
	
	
	// Limpiamos la clase entera
	void clear(){
		w.clear();
		y.clear();
		delta.clear();
		lastc= false;
	}
	
	// Mostramos las salidas
	void showSalidas(){
		
		int n=y.size();
		
		for(int i=0;i<n;i++){
			cout<<"y-"<<i+1<<":   "<<y[i]<<"    ";
		}
		cout<<endl;
		
	}
	
	// Mostramos los pesos
	void showPesos(){
		int p=w[0].size(),pp=w.size();
		cout<<endl<<"---Pesos---"<<endl;
		for(int i=0;i<pp;i++){
			for(int j=0;j<p;j++){
				cout<<w[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	void showdeltaiente(){
		int p=delta.size();
		for(int i=0;i<p;i++)
			cout<<delta[i]<<"  ";
		cout<<endl;
	}
	
};
