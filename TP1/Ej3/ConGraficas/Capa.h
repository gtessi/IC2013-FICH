

using namespace std;


class Capa{
	
private:
	mdouble w,dw; // Matriz de pesos
	vdouble y,delta; // salidas y deltaiente (las entradas es al pedo, porque
	// terminás redundando datos al pedo...
	bool lastc; // si es la ultima capa
	double nu = 0.1,epsilon=0.2;

public:
	
	// Constructor
	//last = especifica si es la ultima capa o no
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
		
		// eliminamos el w0 (peso del bias) 
		for(int i=0;i<aux_w.size();i++){
			aux_w[i].erase(aux_w[i].begin());
		}
		
		// realizamos el caso particular de la ultima capa
		double aux=0;
		if(lastc){//Ultima capa
			delta.clear();
			for(int i=0;i<w.size(); i++){//Para cada peso..
				aux=(1+y[i])*(1-y[i])*(yd_delta[i]-y[i])/2;//Calculamos el delta
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
		for(int i=0; i<cantNeu;i++){//Recorro todas las neuronas
			for(int j=0;j<canEntra;j++){//y para cada entrada de cada neurona...
//				w[i][j] = w[i][j] + nu*delta[i] * x[j];
				aux=w[i][j];//le asigno a aux, los pesos de la neurona i, entrada j
				// epsilon*(w(n) - w(n-1))
				w[i][j] = w[i][j] + nu*delta[i] * x[j] + epsilon*(w[i][j] - dw[i][j]);//Genero los nuevos pesos. Donde Nu=velocidad de aprendizaje y epsilon es el momento.
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
	
	
	void dibPesos(){
		
		// Calculamos dos puntos de las rectas
		// y las dibuja
		
		double x1=-2.0,x2=2.0,y1,y2;
		glColor3f(1.0,1.0,.0);
		glLineWidth(4);
		glBegin(GL_LINES);
			for(int i=0;i<w.size();i++){
				y1=( w[i][0] - w[i][1] * x1)/w[i][2];
				y2=( w[i][0] - w[i][1] * x2)/w[i][2];
				glVertex2d(x1,y1);
				glVertex2d(x2,y2);
			}
		glEnd();
		glLineWidth(2);
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
