

using namespace std;


class Red{
	
private:
	vector<Capa> capas;
	
public:
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
	
	
	void retropopagacion(vdouble yd, vdouble in){
		
		int cantCapas = capas.size()-1;
		
		for (int i=cantCapas;i>-1;i--){
			capas[i].caldelta(yd,i);
		}
		
		for(int i=0;i<cantCapas+1;i++){
			capas[i].actualizarPeso(in);
		}
		
	}
	
	// Realiza las pruebas con los mismos datos de entrenamiento
	double prueba(vdouble salidas, mdouble entradas){
		
		//Realiza el producto punto entre los pesos y las entradas
		vdouble saux;
		
		int ccapas=capas.size()-1,correcto=0;
		
		for(int i=0; i<entradas.size(); i++){
			//Aplico la funcion
			propagacion(entradas[i]);
			capas[ccapas].salidas(saux);
			
			if((saux[0]<0 && salidas[i]==-1)
				|| (saux[0]>0 && salidas[i]==1)) correcto++;
		}
		
		return correcto*100 / salidas.size();
		
	}
	
	
	
	
	
	
	// 	SHOW SHOW SHOW SHOW SHOW
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


