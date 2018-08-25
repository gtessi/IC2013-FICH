
extern mdouble entradas,salidasD;
extern vint capas;
extern int op;

class Particula{
	
	vdouble pos,mejorPos,vel;
	int n;
	double c1=0.5,c2=0.01;
	vector<mdouble> capasPesos;
	
public:
	
	Particula(){pos.clear(); mejorPos.clear(); vel.clear();}
	Particula(int cant){
		pos.clear(); mejorPos.clear(); vel.clear();
		double aux=0;
		int posSize=0;
		for(int i=1;i<capas.size(); i++){
			posSize+=(capas[i-1]*capas[i]);
		}
		
		if(cant!=posSize){
			cout<<"cant!=posSize CUIDADOOOOOOOOOOOOOO  "<<posSize<<endl;
			cant=posSize;
		}
		
		for(int i=0;i<cant;i++){
			// ********* Definimos el rango de valores ***********
			aux=rand()/double(RAND_MAX)*2-1;
			pos.push_back(aux);
			mejorPos.push_back(aux);
			vel.push_back(0.0);
		}
		n=cant;
	}

	void returnPos(vector<double> &bestPos){
		bestPos=mejorPos;
	}
	
	
	
	double funcionPos(){
		
		int cantEntradas = entradas[0].size(), cantDatos=entradas.size(),
			posIte=0, cantidadDeCapas = capas.size()-1,posSalida=0;
		double correcto=0;
		
		// ***************** Armamos las matrices de pesos capas ***************
		capasPesos.clear();
		// Por capa
		capasPesos.resize(cantidadDeCapas);
		for(int k=0;k<cantidadDeCapas;k++){
			//Por Neurona
			capasPesos[k].resize(capas[k+1]);
			
			for(int i=0;i<capas[k+1];i++){
				// Por pesos de la neurona i
				capasPesos[k][i].resize(capas[k]);
				for(int j=0;j<capas[k];j++){
					capasPesos[k][i][j]=pos[posIte];
					posIte++;
				}
			}
		}
		
		//**************** Propagacion Para todos los datos ********************
		for(int k=0;k<cantDatos-1;k++){
			vdouble entradasAux = entradas[k],temp;
			// Propagacion en todas las capas para una entradas
			for(int i=0;i<cantidadDeCapas;i++){
				productoMV(capasPesos[i],entradasAux,temp);
				entradasAux.clear();
				entradasAux=temp;
			}
			
			// verificamos si con los pesos acerto para la entrada k
			maxElement(temp,posSalida);
			if(salidasD[k][posSalida]==1 && op==3)
				correcto++;
			if(salidasD[k][posSalida]==signo(temp[0]) && op!=3)
				correcto++;
			
			
		}
		// La salida es el error mas error peor es
		return 1.0 - correcto/double(cantDatos);

	}
	
	
	double funcionMejorPos(){
		int cantEntradas = entradas[0].size(), cantDatos=entradas.size(),
			posIte=0, cantidadDeCapas = capas.size()-1,posSalida=0;
		double correcto=0;
		
		// ***************** Armamos las matrices de pesos capas ***************
		capasPesos.clear();
		// Por capa
		capasPesos.resize(cantidadDeCapas);
		for(int k=0;k<cantidadDeCapas;k++){
			//Por Neurona
			capasPesos[k].resize(capas[k+1]);
			
			for(int i=0;i<capas[k+1];i++){
				// Por pesos de la neurona i
				capasPesos[k][i].resize(capas[k]);
				for(int j=0;j<capas[k];j++){
					capasPesos[k][i][j]=mejorPos[posIte];
					posIte++;
				}
			}
		}
		
		//**************** Propagacion Para todos los datos ********************
		for(int k=0;k<cantDatos-1;k++){
			vdouble entradasAux = entradas[k],temp;
			// Propagacion en todas las capas para una entradas
			for(int i=0;i<cantidadDeCapas;i++){
				productoMV(capasPesos[i],entradasAux,temp);
				entradasAux.clear();
				entradasAux=temp;
			}
			// verificamos si con los pesos acerto para la entrada k
			maxElement(temp,posSalida);
			if(salidasD[k][posSalida]==1 && op==3)
				correcto++;
			if(salidasD[k][posSalida]==signo(temp[0]) && op!=3)
				correcto++;
		}
		// La salida es el error mas error peor es
		return 1.0 - correcto/double(cantDatos);
	}
	
	void actualizarVelocidad(vector <double>best){
		double r1 =rand()/double(RAND_MAX),
			r2 =rand()/double(RAND_MAX);
		for(int i=0;i<n;i++){
			vel[i]=vel[i]+c1*r1*(mejorPos[i]-pos[i])+c2*r2*(best[i]-pos[i]);
		}
	}
	
	void actualizarPos(){
		for(int i=0;i<n;i++){
			pos[i]=pos[i]+vel[i];
		}
		if(pos[0]<-100)
			pos[0]=-100;
		if(pos[0]>100)
			pos[0]=100;
			
		actualizarY();
	}
	
	double actualizarY(){
		if(funcionPos()<funcionMejorPos())
			mejorPos=pos;
	}
	
	void show(){
		cout<<"pos "<<pos[0]<<"  "<<pos[1]<<"  mejorPos  "<<mejorPos[0]<<mejorPos[1]<<endl;
	}
	
	
	void dibParticula(){
		
		glBegin(GL_POINTS);
			glVertex2f(pos[0],pos[1]);
		glEnd();
		
	}
	
	void showMatrizPesos(){
		
		cout<<endl;
		int cantidadDeCapas = capas.size()-1;
		// por capa
		for(int k=0;k<cantidadDeCapas;k++){
			cout<<"Pesos Capa "<<k+1<<endl;
			// por neurona
			for(int i=0;i<capas[k+1];i++){
				// por pesos de cada neurona i
				for(int j=0;j<capas[k];j++){
					cout<<capasPesos[k][i][j]<<"  ";
				}
				cout<<endl;
			}
			cout<<endl<<"**************************"<<endl<<endl;
		}
		
		
	}
	
};
