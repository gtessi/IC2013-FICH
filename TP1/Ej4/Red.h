

using namespace std;


class Red{
	
private:
	vector<Capa> capas;
	
public:
	Red(){
		capas.clear();
	}
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
	double pruebaIris(mdouble salidas, mdouble entradas){
		
		//Realiza el producto punto entre los pesos y las entradas
		vdouble saux;
		int ccapas=capas.size()-1,
			correcto=0, eSize=entradas.size(),
			pos=0;
		
		for(int i=0; i<eSize; i++){
			//Aplico la funcion
			propagacion(entradas[i]);
			capas[ccapas].salidas(saux);
			
			maxElement(saux,pos);
			
			if(salidas[i][pos]==1)
				correcto++;
			
		}
		
		return correcto*100 / eSize;
		
	}
	
	
	// Realiza las pruebas con los mismos datos de entrenamiento
	void dibPuntos(vdouble salidas, mdouble entradas, int op){
		
		//Realiza el producto punto entre los pesos y las entradas
		vdouble saux;
		
		int ccapas=capas.size()-1,correcto=0;
		
		glPushMatrix();
		
		glTranslated(80,60,0);
		glScaled(90,90,1);
		glLineWidth(3);
		glColor3f(.0,1.0,.0);
		glBegin(GL_LINES);
			glVertex2f(0,0);
			glVertex2f(6,0);
			glVertex2f(0,0);
			glVertex2f(0,6);
		glEnd();
		
		int pos=0;
		glPointSize(4);
		glBegin(GL_POINTS);
		for(int i=0; i<entradas.size(); i++){
			//Aplico la funcion
			propagacion(entradas[i]);
			capas[ccapas].salidas(saux);
			glColor3f(.0,.0,1.0);
			maxElement(saux,pos);
			if(pos==0)glColor3f(1.0,.0,.0);
			if(pos==1)glColor3f(1.0,1.0,.0);
			if(pos==2)glColor3f(1.0,.0,1.0);
			glVertex2f(entradas[i][4],entradas[i][2]);
		}
		glEnd();
		glPopMatrix();
		
	}
	
	
	void dibPesos(int op){
		glPushMatrix();
		
		glTranslated(80,60,0);
		glScaled(60,60,1);
		glColor3f(.3,.3,.3);
		glBegin(GL_LINES);
		glVertex2f(0,0);
		glVertex2f(6,0);
		glVertex2f(0,0);
		glVertex2f(0,6);
		glEnd();
		
		capas[0].dibPesos();
		
		glPopMatrix();
	}
	
	void savePeso(){
		capas[0].savePeso();
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


