

class individuo{
	
private:
	
	int *cromosoma,size;
	
	
public:
	
	// CONSTRUCTOR
	individuo(int cantGen){ 
		cromosoma= new int[cantGen];
		size=cantGen;
		// Inicializamos al azar el cromosoma
		for (int i=0; i<size;i++){
			cromosoma[i]=0;
			if((rand()/double(RAND_MAX))<0.5)
				cromosoma[i]=1;
		}
		
	}
	// CONSTRUCTOR COPIA, PARA HACER LAS CRUZAS
	individuo(int cantGen,int *cromo){
		size=cantGen;
		cromosoma= new int[size];
		for(int i=0;i<size;i++){
			cromosoma[i]=cromo[i];
		}
	}
	
	// CONSTRUCTOR COPIA, PARA HACER LAS CRUZAS
	individuo(const individuo &copiar){
		size=copiar.size;
		cromosoma= new int[size];
		for(int i=0;i<size;i++){
			cromosoma[i]=copiar.cromosoma[i];
		}
	}
	
	// CONSTRUCTOR VACIO
	individuo(){size=0;}
	
	int returnSize(){return size;}
	
	// Traducimos el valor binario a flotante
	double returnValor(int i){
		
		double aux=0;
		if(i==1){
			for(int i=size-2;i>-1;i--){
				aux+=(cromosoma[i]*pow(2,-1*(i-(size-1))));
			}
			if(cromosoma[size-1]==1)
				aux*=-1;
		}
		if(i==2){
			for(int i=size-1;i>size-5;i--){
				aux+=(cromosoma[i]*pow(2,i-(size-5)));
			}
			for(int i=size-5;i>-1;i--){
				aux+=(cromosoma[i]*pow(2,(4-size)+i));
			}
			
		}
		return aux;
	}
	
	// Retorna el valor de la funcion
	double returnFunctionVal(int i){
		
		double x=returnValor(i),valor=0;
////		if(i==1){
////			valor=-x*sin(pow(abs(x),0.5));
////		}
////		if(i==2){
////			valor=x+5*sin(3*x)+8*cos(5*x);
////		}
		
		// *** aca hay que codificar una funcion que recorra la matriz desde la
		//ciudad inicial hasta la misma, pasando por todas una sola vez sin
		//repeticiones y con la minima distancia
		
		return valor;
	}
	
	
	// Operador de mutacion
	void mutarPosI(int i){
		cromosoma[i]=!cromosoma[i];
	}
	
	void cruzarConI(individuo i, int cant, int posMia, int posEl, int *newIndi1,int *newIndi2 ){
		
		for(int j=0;j<size;j++){
			newIndi1[j]=cromosoma[j];
			newIndi2[j]=i.cromosoma[j];
		}
		
		
		for(int j=0;j<cant;j++){
			newIndi1[posMia+j] = i.cromosoma[posEl+j];
			newIndi2[posEl+j] = cromosoma[posMia+j];
		}
	}
	
	void dibIndi(int i){
		double xVal=returnValor(i),
			yVal=returnFunctionVal(i);
		
		glBegin(GL_POINTS);
			glVertex2f(xVal,yVal);
		glEnd();
	}
	
	// ShowTodo
	void mostrarIndi(){
		for(int i=size-1;i>-1;i--){
			cout<<cromosoma[i];
		}
		cout<<endl;
	}
	
};

