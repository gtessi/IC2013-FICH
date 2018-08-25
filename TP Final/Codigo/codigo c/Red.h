

using namespace std;


class Red{
	
private:
	vector<Capa> capas;
	
public:
	Red(){
		capas.clear();
	}
	Red(vector<int> capaCant, int cantEntradas){
		
		capas.clear();
		
		int cantCapas = capaCant.size(),i=0;
		
		for(; i<cantCapas-1 ; i++){
			Capa aux = Capa(cantEntradas,capaCant[i],false);
			capas.push_back(aux);
			aux.clear();
			cantEntradas = capaCant[i]+1;
		}
		
		Capa aux= Capa(cantEntradas,capaCant[i],true);
		capas.push_back(aux);
	}
	
	
	void propagacion(vdouble in){
		
		capas[0].calcularSalidas(in);
		int scapas = capas.size(),i=1;
		vdouble entradas;
		
		for (; i<scapas;i++){
			capas[i-1].salidas(entradas);
			capas[i].calcularSalidas(entradas);
		}
	}
	
	void salidas(vdouble &salida){
		salida.clear();
		capas[capas.size()-1].salidas(salida);
	}
	
	void retropopagacion(vdouble in){
		
		int cantCapas = capas.size()-1;
		vdouble inAux=in;
		for (int i=cantCapas;i>-1;i--){
			capas[i].caldelta(inAux,i);
		}
		
		for(int i=0;i<cantCapas+1;i++){
			capas[i].actualizarPeso(in);
		}
		
	}
	
	// Calcula el error promedio en valor absoluto
	double error(mdouble entradas){
		
		//Realiza el producto punto entre los pesos y las entradas
		vdouble saux;
		int ccapas=capas.size()-1,
			cantSalidas = entradas[0].size(), 
			eSize=entradas.size();
		
		double error=0;
		
		for(int i=0; i<eSize; i++){
			//Aplico la propagacion
			propagacion(entradas[i]);
			capas[ccapas].salidas(saux);
			
			// calculamos el error absoluto
			for(int j=0;j<cantSalidas;j++){
				error+=abs(saux[j]-entradas[i][j]);
			}
			
		}
		
		// retornamos el error en promedio de la suma
		// de los valores absolutos
		return error/double(eSize);
		
	}
	
	
	// 	-------------- SHOW SHOW SHOW SHOW SHOW
	void showSalidas(){
		int cantCapas = capas.size();
		for(int i=0;i<cantCapas;i++){
			cout<<"--- Capa "<<i+1<<" ---"<<endl;
			capas[i].showSalidas();
		}
	}
	
	
	void showSalida(){
		int cantCapas = capas.size();
		capas[cantCapas-1].showSalidas();
		cout<<endl;
	}
	
	void showPesos(){
		int p=capas.size();
		for(int i=0;i<p;i++){
			capas[i].showPesos();
		}
	}
	
	void showdeltaientes(){
		int p=capas.size();
		for(int i=0;i<p;i++){
			capas[i].showdeltaiente();
		}
	}
};


