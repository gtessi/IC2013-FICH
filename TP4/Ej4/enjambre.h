class Enjambre{
	
	vector<Particula> enjambre;
	vdouble mejorPos, prom,promBest,Best;
	double valorMejorpos;
	int cantParticulas,iteracion=0;
	
public:
	
	Enjambre(){};
	Enjambre(int cParticulas, int cValores){
		Particula aux;
		cantParticulas=cParticulas;
		for(int i=0;i<cantParticulas;i++){
			aux=Particula(cValores);
			enjambre.push_back(aux);
		}
		mejorPos.resize(cValores);
		valorMejorpos=enjambre[0].funcionPos();
		for(int i=1;i<cantParticulas;i++){
			if(enjambre[i].funcionPos()<valorMejorpos){
				enjambre[i].returnPos(mejorPos);
				valorMejorpos=enjambre[i].funcionMejorPos();
			}
		}
	}
	
	
	void evaluarTodos(){
		
		for(int i=0;i<cantParticulas;i++){
			enjambre[i].actualizarVelocidad(mejorPos);
			enjambre[i].actualizarPos();
		}
		
		for(int i=0;i<cantParticulas;i++){
			if(enjambre[i].funcionPos()<valorMejorpos){
				enjambre[i].returnPos(mejorPos);
				valorMejorpos=enjambre[i].funcionMejorPos();
			}
		}
		cout<<"Finalizo iteracion  "<<iteracion<<endl;
		iteracion++;
	}
	
	// *************** DIBUJAR ****************
	void dibIteracion(){
		double Prom=0, PromBest=0;
		for(int i=0;i<cantParticulas;i++){
			Prom+=enjambre[i].funcionPos();
			PromBest+=enjambre[i].funcionMejorPos();
		}
		Prom  = Prom/double(cantParticulas);
		PromBest = PromBest / double(cantParticulas);
		
		cout<<"Prom: "<<Prom<<", PromBest: "<<PromBest<<", Best: "<<valorMejorpos<<endl;
		prom.push_back(Prom);
		promBest.push_back(PromBest);
		Best.push_back(valorMejorpos);
		
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		
		glPointSize(3);
		glBegin(GL_LINES);
		double di=0.0025,ipos=0;
		for(double i=0;i<iteracion-1;i++){
			glColor3f(1.0,.0,.0);
			glVertex2f(ipos,Best[i]);
			glVertex2f(ipos+di,Best[i+1]);
			
			glColor3f(.0,1.0,.0);
			glVertex2f(ipos,promBest[i]);
			glVertex2f(ipos+di,promBest[i+1]);
			
			glColor3f(.0,.0,1.0);
			glVertex2f(ipos,prom[i]);
			glVertex2f(ipos+di,prom[i+1]);
			ipos+=di;
		}
		glEnd();
		
		glPopAttrib();
		
	}
	
	void showMatricesPesos(){
		for(int i=0;i<cantParticulas;i++){
			enjambre[i].showMatrizPesos();
		}
	}
	
};
