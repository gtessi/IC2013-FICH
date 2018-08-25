


class poblacion{
	
private:
	
	vector<individuo> pueblo;
	vector<individuo> progenitores;
	individuo Elite, Peor;
	int cantPoblacion,iteracion=0;
	float probMutacion=0.01;
	vector< vector <float > > Ciudades;
	
	vector <float > promv,elitev,peorv;
	
public:
	
	// poblacion vacía
	poblacion(){cantPoblacion=0;}
	
	// definimos la poblacion y ya la inicializamos al azar
	poblacion(int cantPobla, vector< vector <float> > City){
		cantPoblacion=cantPobla;
		Ciudades=City;
		int nCiudades = Ciudades.size();
		for(int i=0;i<cantPoblacion;i++){
			pueblo.push_back(individuo(nCiudades));
		}
	}
	
	// *********************** ESTE METODO NO HAY QUE TOCARLO *********************
	// SELECCIONAR LOS PROGENITORES
	
	void selectProgenitores(int porcentaje){
		
		int cantProg = cantPoblacion * double(porcentaje) /100.0;
		
		if(cantPoblacion<cantProg){
			cout<<"Error cantidad de progenitores"<<endl;
			return;}
		
		int ventana=cantPoblacion;
		vector< vector< float > > people;
		vector<float> aux;
		
		// Calculamos el fitness para todos los individuos
		// y los linkeamos con su posicion j
		for(int j=0;j<cantPoblacion;j++){
			aux.push_back(j);
			aux.push_back(pueblo[j].fitness(Ciudades));
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
		Peor = pueblo[people[cantPoblacion-1][0]];
		
		float cteVarVentana = (ventana-cantProg)/cantProg;
		for(int i=0;i<cantProg;i++){
			progenitores.push_back(
				pueblo[people[int(ventana*(rand()/float(RAND_MAX)))][0]]);
			ventana= ventana - cteVarVentana;
		}
		
		
	}
	
	
	// Una vez elegidos los progenitores tenemos que mezclarlos entre si
	// con una probabilidad de mutacion
	void mezclarProgenitores(){
		
		iteracion++;
		
		individuo nuevo1,nuevo2;
		int cantProg = progenitores.size();
		
		// Variables para la mezcla, la idea es usar todos los progenitores para
		// mezclar
		int cantVeces = cantPoblacion / cantProg, cantPoblacionBack=cantPoblacion,
			posRandom,cant=(Ciudades.size()-1)*rand()/float(RAND_MAX);
		
		// borramos el viejo poblado
		pueblo.clear();
		cantPoblacion=0;
		cantVeces=cantVeces/2;
		// Con elitismo
		pueblo.push_back(Elite);
		
		for (int i=0;i<cantProg;i++){
			for(int j=0;j<cantVeces;j++){
				posRandom=int(cantProg*(rand()/float(RAND_MAX)));
				if(posRandom==i){
					j--;
					continue;}
				progenitores[i].cruzarConI(progenitores[posRandom], cant, nuevo1, nuevo2);
				pueblo.push_back(nuevo1);pueblo.push_back(nuevo2);
				nuevo1.clear();nuevo2.clear();
				cantPoblacion+=2;
			}
			
		}
		
		while(cantPoblacion<cantPoblacionBack){
			int posRandomi=int(cantProg*(rand()/float(RAND_MAX))), 
				posRandomj=int(cantProg*(rand()/float(RAND_MAX)));
			progenitores[posRandomi].cruzarConI(progenitores[posRandomj],cant, nuevo1,nuevo2);
			pueblo.push_back(nuevo1);pueblo.push_back(nuevo2);
			nuevo1.clear();nuevo2.clear();
			cantPoblacion+=2;
		}
	}
	
	
	// *************** DIBUJAR ****************
	void dibIteracion(){
		float fitnessProm=0,fitnessPeor=0,fitnessElite=0;
		for(int i=0;i<cantPoblacion;i++){
			fitnessProm+=pueblo[i].fitness(Ciudades);
		}
		fitnessProm  = fitnessProm/float(cantPoblacion);
		cout<<fitnessProm<<endl;
		fitnessElite = Elite.fitness(Ciudades);
		fitnessPeor  = Peor.fitness(Ciudades);
		
		elitev.push_back(fitnessElite);
		promv.push_back(fitnessProm);
		peorv.push_back(fitnessPeor);
		
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		
		glPointSize(3);
		glBegin(GL_LINES);
		for(int i=0;i<iteracion-1;i++){
			glColor3f(1.0,.0,.0);
			glVertex2f(i,elitev[i]);
			glVertex2f(i+1,elitev[i+1]);
			glColor3f(.0,1.0,.0);
			glVertex2f(i,promv[i]);
			glVertex2f(i+1,promv[i+1]);
			glColor3f(.0,.0,1.0);
			glVertex2f(i,peorv[i]);
			glVertex2f(i+1,peorv[i+1]);
		}
		glEnd();
		
		glPopAttrib();
		
	}
	
	
	// *************** SHOWWWW ****************
	void mostrarIndiI(int i){
		if(i>cantPoblacion)
			cout<<"Error, no existe ese numero de individuo"<<endl;
		pueblo[i].mostrarIndi();
	}
	void mostrarTodo(){
		for(int i=0;i<cantPoblacion;i++){
			cout<<i<<":  ";
			pueblo[i].mostrarIndi();
			cout<<endl;
		}
		
	}
	
	void showPeor(){
		cout<<"Peor:  ";
		cout<<"f(x): "<<Peor.fitness(Ciudades)<<endl;
	}
	
	void showBest(){
		cout<<"Elite:  ";
		cout<<"f(x): "<<Elite.fitness(Ciudades)<<endl;
	}
};
