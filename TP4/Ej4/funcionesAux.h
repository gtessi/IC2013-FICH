
extern mdouble entradas,salidasD;
extern vdouble salidasAux;
extern vint capas;

// producto entre Matriz Vector
void productoMV(mdouble matriz, vdouble vector, vdouble &v){
	
	// verifica si la cantidad de columnas es la
	// misma que la longitud del vector
	if(matriz[0].size()!=vector.size()){
		cout<<"Error productoMV: "<<matriz[0].size()<<"  "<<vector.size()<<endl;
		return ;
	}
	
	// Limpiamos el vector de retorno
	v.clear();
	
	// Cantidad de renglones 
	int smatriz = matriz.size(),
		// cantidad de columnas
		svector = vector.size();
	// variable auxiliar
	double aux=0;
	
	for(int i=0;i<smatriz;i++){
		for(int j=0;j<svector;j++){
			aux=matriz[i][j] * vector[j]+aux;
		}
		
		// Funcion sigmoida
		aux= 2 / (1+exp(-2.0*aux)) - 1;
		// agregamos el nuevo valor al vector de salida
		v.push_back(aux);
		aux=0;
	}
	
}


void maxElement(vdouble v, int &pos){
	double aux=v[0];
	int vSize = v.size();
	pos=0;
	
	for(int i=1;i<vSize;i++){
		if(v[i]>aux){
			aux=v[i];
			pos=i;
		}
	}
}


void Operacion(int op){
	
	switch(op){
	case 1:{
		readFile(entradas,salidasAux,"entradasOR.txt",false);
		
		capas.push_back(entradas[0].size());
		capas.push_back(1);
		
		int cantDatos=salidasAux.size(),cantidadDeSalidas=capas[capas.size()-1];
		vdouble aux;
		for(int i=0;i<cantidadDeSalidas;i++)
			aux.push_back(-1);
		
		for(int i=0;i<cantDatos;i++){
			if(salidasAux[i]==1)
				aux[0]=1;
			salidasD.push_back(aux);
			aux[0]=-1;
		}
		break;
		}
	case 2:{
		readFile(entradas,salidasAux,"entradasXOR.txt",false);
		
		capas.push_back(entradas[0].size());
		capas.push_back(2);
		capas.push_back(1);
		
		int cantDatos=salidasAux.size(),cantidadDeSalidas=capas[capas.size()-1];
		vdouble aux;
		for(int i=0;i<cantidadDeSalidas;i++)
			aux.push_back(-1);
		
		for(int i=0;i<cantDatos;i++){
			if(salidasAux[i]==1)
				aux[0]=1;
			salidasD.push_back(aux);
			aux[0]=-1;
		}
		break;
		}
	case 3:{
		readFile(entradas,salidasAux,"clouds.csv",true);
		
		capas.push_back(entradas[0].size());
		capas.push_back(6);
		capas.push_back(4);
		capas.push_back(2);
		
		int cantDatos=salidasAux.size(),cantidadDeSalidas=capas[capas.size()-1];
		vdouble aux;
		for(int i=0;i<cantidadDeSalidas;i++)
			aux.push_back(-1);
		
		for(int i=0;i<cantDatos;i++){
			salidasD.push_back(aux);
			if(salidasAux[i]==0.0)
				salidasD[i][0]=1;
			
			if(salidasAux[i]==1.0)
				salidasD[i][1]=1;
		}
		break;
		}
	}
}


int signo(double valor){
	
	if(valor<0)
		return -1;
	return 1;
	
}



