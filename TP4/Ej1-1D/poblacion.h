


class poblacion{
	
private:
	
	vector<individuo> pueblo;
	vector<individuo> progenitores;
	individuo Elite;
	int cantPoblacion, cantGenes,funcion;
	double probMutacion=0.01;
	
public:
	
	// poblacion vacía
	poblacion(){cantPoblacion=0;}
	
	// definimos la poblacion y ya la inicializamos al azar
	poblacion(int cantPobla, int cantGen, int func){
		cantGenes=cantGen;
		cantPoblacion=cantPobla;
		for(int i=0;i<cantPoblacion;i++){
			pueblo.push_back(individuo(cantGenes));
		}
		funcion=func;
		cout<<funcion<<endl;
	}
	
	// Operadore de mutacion y cruza
	void mutarI(int i){
		int pos= cantGenes*(rand()/double(RAND_MAX));
		pueblo[i].mutarPosI(pos);
	}
	
	void cruzarIJ(int i, int j){
		// el -1 +1 es para que por lo menos intercambien uno o sea evita
		// el 1 y 0 del rand
		int cantGenesCruzar = (cantGenes-2)*(rand()/double(RAND_MAX))+1;
		int posCruzar1= (cantGenes-cantGenesCruzar)*(rand()/double(RAND_MAX));
		int posCruzar2= (cantGenes-cantGenesCruzar)*(rand()/double(RAND_MAX));
		
		
		int *newIndi1=new int[cantGenes],*newIndi2=new int[cantGenes];
		
		//pueblo[i].cruzarConI(pueblo[j], cantGenesCruzar, posCruzar1, posCruzar2,newIndi1,newIndi2);
		progenitores[i].cruzarConI(progenitores[j], cantGenesCruzar, posCruzar1, posCruzar2,newIndi1,newIndi2);
		
		pueblo.push_back(individuo(cantGenes,newIndi1));
		pueblo.push_back(individuo(cantGenes,newIndi2));
		// Aumentamos la poblacion
		cantPoblacion+=2;
		
		//pobabilidad de mutacion
		if((rand()/double(RAND_MAX))<probMutacion){
			mutarI(cantPoblacion-2);
			//cout<<"Muto al indi "<<cantPoblacion-2<<endl;
		}
		if((rand()/double(RAND_MAX))<probMutacion){
			mutarI(cantPoblacion-1);
			//cout<<"Muto al indi "<<cantPoblacion-1<<endl;
		}
	}
	
	// SELECCIONAR LOS PROGENITORES
	void selectProgenitores(int porcentaje){
		
		int cantProg = cantPoblacion * double(porcentaje) /100.0;
		
		if(cantPoblacion<cantProg){
			cout<<"Error cantidad de progenitores"<<endl;
			return;}
		
		int ventana=cantPoblacion;
		vector< vector< double > > people;
		vector<double> aux;
		
		// Calculamos el fitness para todos los individuos
		// y los linkeamos con su posicion j
		for(int j=0;j<cantPoblacion;j++){
			aux.push_back(j);
			aux.push_back(pueblo[j].returnFunctionVal(funcion));
			people.push_back(aux);
			aux.clear();
		}
		
		// ordenamos los individuos para luego elegirlos
		int posAux;
		for(int i=0;i<cantPoblacion-1;i++){
			aux.push_back(i);
			aux.push_back(people[i][1]);
			posAux=i;
			
			// es un ordenamiento burbuja
			for(int j=i+1;j<cantPoblacion;j++){
				if(people[j][1]<aux[1]){
					aux[1]=people[j][1];
					aux[0]=people[j][0];
					posAux=j;
				}
				
			}
			// hacemos el cambio entre el mayor i con el que 
			// esta en la posicion i
			people[posAux][0] = people[i][0];
			people[posAux][1] = people[i][1];
			
			people[i][0] = aux[0];
			people[i][1] = aux[1];
			
			aux.clear();
		}
		
		Elite = pueblo[people[0][0]];
		
		double cteVarVentana = (ventana-cantProg)/cantProg;
		for(int i=0;i<cantProg;i++){
			progenitores.push_back(
				pueblo[people[int(ventana*(rand()/double(RAND_MAX)))][0]]);
			ventana= ventana - cteVarVentana;
		}
		
		
	}
	
	// Una vez elegidos los progenitores tenemos que mezclarlos entre si
	// con una probabilidad de mutacion
	void mezclarProgenitores(){
		
		int cantProg = progenitores.size();
		
		// Variables para la mezcla, la idea es usar todos los progenitores para
		// mezclar
		int cantVeces = cantPoblacion / cantProg, cantPoblacionBack=cantPoblacion,
			posRandom;
		
		// borramos el viejo poblado
		pueblo.clear();
		cantPoblacion=0;
		cantVeces=cantVeces/2;
		
		// Con elitismo
		pueblo.push_back(Elite);
		
		for (int i=0;i<cantProg;i++){
			for(int j=0;j<cantVeces;j++){
				posRandom=int(cantProg*(rand()/double(RAND_MAX)));
				if(posRandom==i){
					j--;
					continue;}
				cruzarIJ(i,posRandom);
			}
		}
		
		while(cantPoblacion<cantPoblacionBack){
			int posRandomi=int(cantProg*(rand()/double(RAND_MAX))), 
				posRandomj=int(cantProg*(rand()/double(RAND_MAX)));
			cruzarIJ(posRandomi,posRandomj);
		}
	}
	
	
	// Dibujar Individuos
	void dibPoblacion(){
		
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glColor3f(0,0,1); 
			glPointSize(3);
			for(int i=0;i<cantPoblacion;i++){
				pueblo[i].dibIndi(funcion);
			}
		glPopAttrib();
	}
	
	// showTodo
	void mostrarIndiI(int i){
		if(i>cantPoblacion)
			cout<<"Error, no existe ese numero de individuo"<<endl;
		pueblo[i].mostrarIndi();
	}
	void mostrarTodo(){
		for(int i=0;i<cantPoblacion;i++){
			cout<<i<<":  ";
			pueblo[i].mostrarIndi();
		}
		
	}
	
	void calcularTodo(){
		for(int i=0;i<cantPoblacion;i++){
			cout<<i<<":  "<<pueblo[i].returnValor(funcion)<<endl;
		}
	}
	
	void showBest(int i){
		cout<<"Valor binario: ";
		Elite.mostrarIndi();
		cout<<"Valor decimal: "<<Elite.returnValor(i)<<endl;
		cout<<"f(x): "<<Elite.returnFunctionVal(i)<<endl;
	}
};
