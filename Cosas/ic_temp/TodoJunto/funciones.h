#include <cmath>

using namespace std;

extern vdouble ww;
extern int iteRand;

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
		aux= 2 / (1+exp(-aux)) - 1;
		// agregamos el nuevo valor al vector de salida
		v.push_back(aux);
		aux=0;
	}
	
}



// producto entre Matriz Vector
void productoMVLineal(mdouble matriz, vdouble vector, vdouble &v){
	
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
		
		// agregamos el nuevo valor al vector de salida
		v.push_back(aux);
		aux=0;
	}
	
}


// Producto entre Vector Matriz
void productoVM(vdouble vector, mdouble matriz, vdouble &v){
	
	
	if(vector.size()!=matriz.size()){
		cout<<"Error productoVM: "<<vector.size()<<"  "<<matriz.size()<<endl;
		return;
	}
	
	v.clear();
	int svector = matriz[0].size(),smatriz=matriz.size();
	double aux=0;
	
	
	for(int i=0; i<svector;i++){
		for(int j=0;j<smatriz;j++){
			aux=(vector[j]*matriz[j][i])+aux;
		}
		v.push_back(aux);
		aux=0;
	}
}

// Muestra un Vector
void show(vector<double> x){
	for(int i=0;i<x.size();i++)
		cout<<x[i]<<"  ";
	cout<<endl;
}


// Muestra una matriz
void show(vector< vector< double> > x){
	
	for(int j=0;j<x.size();j++){
		for(int i=0;i<x[0].size();i++)
			cout<<x[j][i]<<"  ";
		cout<<endl;
	}
}


// Genera los pesos aleatoriamente
void generarPesos(int cantidad, vector<double> &W){
	W.clear();
	
	double min =-0.6,max=0.6;
	srand(time(NULL)+iteRand);
	iteRand++;
	for(int i=0; i<cantidad; i++){
		
		W.push_back(double(rand()*(max-min)/RAND_MAX + min));
	}
	
	
}

void maxElement(vdouble v, int &pos){
	double aux=0;
	int vSize = v.size();
	pos=-1;
	
	for(int i=0;i<vSize;i++){
		if(v[i]>aux){
			aux=v[i];
			pos=i;
		}
	}
}

void generarZeros(int cantidad, vector<double> &W){
	W.clear();
	for(int i=0; i<cantidad; i++){
		W.push_back(0);
	}
}


void ordenar(mdouble matriz, float dt, mdouble &mOrdenada){
	
	// Definimos las variables
	int col = matriz[0].size(),
		reng = matriz.size();
	
	mOrdenada.clear();
	vdouble aux;
	double ini,fin;
	bool flag=false;
	
	// Los dos primeros for son para recorrer la matriz normalmente
	for(int r=0;r<reng;r++){
		for(int c=0;c<col;c++){
			
			if(matriz[r][c]==0)
				continue;
			
			ini=r*dt;
			fin=(r+1)*dt;
			aux.push_back(matriz[r][c]);
			aux.push_back(ini);
			
			// Estos dos for son para buscar valores repetiros una vez
			// posicionado en algun lugar r c de la matriz
			
			for(int rr=r+1;rr<reng;rr++){
				flag=false;
				for(int cc=0;cc<col;cc++){
					if(aux[0]==matriz[rr][cc]){
						flag=true;
						matriz[rr][cc]=0;
						fin+=dt;
						// en vez de joder con los continue que pueden hacer cagadas
						cc=col; 
					}
				}
				// en vez de joder con los continue que pueden hacer cagadas
				if(!flag)
					rr=reng;
				
			}
			aux.push_back(fin);
			mOrdenada.push_back(aux);
			aux.clear();
		}
	}
	
}


void ordenarTime1(mdouble &matriz){
	
	vdouble aux;
	int posAux, reng=matriz.size();
	for(int i=0;i<reng-1;i++){
		aux=matriz[i];
		posAux=i;
		
		// es un ordenamiento burbuja
		for(int j=i+1;j<reng;j++){
			if(matriz[j][1]<aux[1]){
				aux.clear();
				aux=matriz[j];
				posAux=j;
			}
			
		}
		// hacemos el cambio entre el mayor i con el que 
		// esta en la posicion i
		matriz[posAux][0] = matriz[i][0];
		matriz[posAux][1] = matriz[i][1];
		matriz[posAux][2] = matriz[i][2];
		
		matriz[i][0] = aux[0];
		matriz[i][1] = aux[1];
		matriz[i][2] = aux[2];
		
		aux.clear();
	}

}


void makeMatrizMidi(mdouble matriz,mdouble &mMidi){
	/*
	1- track number
	2- channel number
	3- note number (midi encoding of pitch)
	4- velocity
	5- start time (seconds)
	6- end time (seconds)*/
	
	vdouble aux;
	aux.resize(6);
	aux[0]=1;
	int reng = matriz.size();
	for(int i=0;i<reng;i++){
		aux[2]=matriz[i][0];
		aux[4]=matriz[i][1];
		aux[5]=matriz[i][2];
		aux[3]=int(100 * (rand()/double(RAND_MAX)));
		mMidi.push_back(aux);
	}

}





