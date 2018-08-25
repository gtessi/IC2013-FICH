

class individuo{
	
private:
	
	int *cromosoma,size;
	
	
public:
	
	// CONSTRUCTOR
	individuo(int cantGen){ 
		if(cantGen%2!=0){
			cout<<"CantGen debe ser par"<<endl;
			cin.get();}
		
		cromosoma= new int[cantGen];
		size=cantGen;
		// Inicializamos al azar el cromosoma
		for (int i=0; i<size;i++){
			cromosoma[i]=0;
			if((rand()/float(RAND_MAX))<0.5)
				cromosoma[i]=1;
		}
		
	}
	// CONSTRUCTOR COPIA, PARA HACER LAS CRUZAS
	individuo(int cantGen,int *cromo){
		size=cantGen;
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
	void returnValor(float returnXY[]){
		
		int iniY = size/2;
		//returnXY = new float[2];
		float aux=0;
		
		for(int i=1;i<iniY;i++){
			aux+=(cromosoma[i]*pow(2,iniY-1-i));
		}
		if(cromosoma[1]==1)
			aux*=-1;
		returnXY[0] = aux;
		aux=0;
		
		for(int i=iniY+1;i<size;i++){
			aux+=(cromosoma[i]*pow(2,size-1-i));
		}
		if(cromosoma[1]==1)
			aux*=-1;
		returnXY[1]=aux;
	}
	
	// Retorna el valor de la funcion
	float returnFunctionVal(){
		
		float *XY= new float[2];
		
		returnValor(XY);
		//((X^2+Y^2).^0.25) .* (sin(50.*((X^2+Y^2).^0.1)).^2+1);
		return
			pow(pow(XY[0],2)+pow(XY[1],2),0.25)*(pow(sin(50*(pow(pow(XY[0],2)+pow(XY[1],2),0.1))),2)+1);
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
	// ShowTodo
	void mostrarIndi(){
		for(int i=size-1;i>-1;i--){
			cout<<cromosoma[i];
		}
		float *XY= new float[2];
		returnValor(XY);
		cout<<"  x: "<<XY[0]<<" ,  y: "<<XY[1]<<endl;
	}
	
};

