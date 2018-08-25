

class individuo{
	
private:
	
	vector<int> ciudades;
	
public:
	
	// CONSTRUCTOR
	individuo(int cantCiudades){ 
		
		// Inicializamos el vector auxiliar
		for (int i=0; i<cantCiudades;i++){
			ciudades.push_back(i);
		}
		random_shuffle(ciudades.begin(),ciudades.end());
		
	}
	
	
	// CONSTRUCTOR COPIA, PARA HACER LAS CRUZAS
	individuo(const individuo &copiar){
		
		int size=copiar.ciudades.size();
		for(int i=0;i<size;i++){
			ciudades.push_back(copiar.ciudades[i]);
		}
	}
	
	// CONSTRUCTOR VACIO
	individuo(){}
	
	
	//Destructor
	void clear(){
		ciudades.clear();
	}
	// Retorna el valor de la funcion
	float fitness(vector< vector < float > > Citys){
		
		
		int cCiudades=ciudades.size();
		if(Citys.size()!=cCiudades)
			return 0;
		float dist=0;
		for(int i=0;i<cCiudades-1;i++){
			dist+=Citys[ciudades[i]][ciudades[i+1]];
		}
		dist+=Citys[ciudades[0]][ciudades[cCiudades-1]];
		return dist;
	}
	
	
	//*********************** PROBAR A PATA A VER SI ANDA BIEN ***********************
	
	void cruzarConI(individuo indi, int cant, individuo &nuevo1, individuo &nuevo2){
		int cCiudades=ciudades.size();
		int pos1=rand()/float(RAND_MAX) * (cCiudades-cant),
			pos2=rand()/float(RAND_MAX) * (cCiudades-cant);
		
		// *********** Hacemos la copia para retornar ***********
		for(int i=0;i<cCiudades;i++){
			nuevo1.ciudades.push_back(ciudades[i]);
			nuevo2.ciudades.push_back(indi.ciudades[i]);
		}
		
		//*********** Eliminamos los repetidos ***********
		int cCiudadesAux=cCiudades;
		for(int i=0;i<cant;i++){
			for(int j=0;j<cCiudadesAux;j++){
				if(indi.ciudades[pos1+i] == nuevo1.ciudades[j])
					nuevo1.ciudades.erase(nuevo1.ciudades.begin()+j);
				
				if(ciudades[pos2+i] == nuevo2.ciudades[j])
					nuevo2.ciudades.erase(nuevo2.ciudades.begin()+j);
				
			}
			cCiudadesAux--;
		}
		
		// ************* Agregamos a los elementos en una pos cualquiera **************
		int agre1=rand()/float(RAND_MAX) * cCiudadesAux,
			agre2=rand()/float(RAND_MAX) * cCiudadesAux;
		for(int i=0;i<cant;i++){
			nuevo1.ciudades.insert(nuevo1.ciudades.begin()+agre1+i,indi.ciudades[pos1+i]);
			nuevo2.ciudades.insert(nuevo2.ciudades.begin()+agre2+i,ciudades[pos2+i]);
		}
	}
	
	//*********************** PROBAR A PATA A VER SI ANDA BIEN ***********************
	
	//  Mutacion, es un intercambio de recorrido no se si valdria como mutacion
	void mutar(){
		int size = ciudades.size(),cityAux=0;
		int pos1=rand()/float(RAND_MAX) * size,
			pos2=rand()/float(RAND_MAX) * size;
		cityAux=ciudades[pos1];
		ciudades[pos1]=ciudades[pos2];
		ciudades[pos2]=cityAux;
	}
	
	// ShowTodo
	void mostrarIndi(){
		int size=ciudades.size();
		for(int i=0;i<size;i++){
			cout<<ciudades[i]<<" , ";
		}
		cout<<endl;
	}
	
};

