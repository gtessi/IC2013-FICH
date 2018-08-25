

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
	double prueba(vdouble salidas, mdouble entradas){
		
		//Realiza el producto punto entre los pesos y las entradas
		vdouble saux;
		
		int ccapas=capas.size()-1,correcto=0;
		
		for(int i=0; i<entradas.size(); i++){
			//Aplico la funcion
			propagacion(entradas[i]);
			capas[ccapas].salidas(saux);
			
			if((saux[0]<0 && salidas[i]==-1)
				|| (saux[0]>0 && salidas[i]==1)) correcto++;
		}
		
		return correcto*100 / salidas.size();
		
	}
	
	
	// Realiza las pruebas con los mismos datos de entrenamiento
	void dibPuntos(vdouble salidas, mdouble entradas, int op){
		
		//Realiza el producto punto entre los pesos y las entradas
		vdouble saux;
		
		int ccapas=capas.size()-1,correcto=0;
		
		glPushMatrix();
		
		switch (op){
		case 1:{		
			glTranslated(320,240,0);
			glScaled(200,200,1);
			glPointSize(3);
			glColor3f(.0,1.0,.0);
			glBegin(GL_LINES);
				glVertex2f(-2,0);
				glVertex2f(2,0);
				glVertex2f(0,-2);
				glVertex2f(0,2);
			glEnd();
			break;
		}
		case 2:
			{
				glTranslated(50,50,0);
				glScaled(400,400,1);
				glPointSize(3);
				glLineWidth(2);
				glColor3f(.0,1.0,.0);
				glBegin(GL_LINES);
				glVertex2f(-.1,-.1);
				glVertex2f(2,-.1);
				glVertex2f(-.1,-.1);
				glVertex2f(-.1,2);
				glEnd();
				
				break;
			}
			
		}
		
		glBegin(GL_POINTS);
		for(int i=0; i<entradas.size(); i++){
			//Aplico la funcion
			propagacion(entradas[i]);
			capas[ccapas].salidas(saux);
			glColor3f(.0,.0,1.0);
			if(saux[0]<0) glColor3f(1.0,.0,.0);
			glVertex2f(entradas[i][1],entradas[i][2]);
		}
		glEnd();
		glPopMatrix();
		
	}
	
	
	void dibPesos(int op){
		
		glPushMatrix();
		switch (op){
		case 1:{
			glTranslated(320,240,0);
			glScaled(200,200,1);
			glPointSize(3);
			glColor3f(.0,1.0,.0);
			glBegin(GL_LINES);
				glVertex2f(-2,0);
				glVertex2f(2,0);
				glVertex2f(0,-2);
				glVertex2f(0,2);
			glEnd();
			break;
		}
		case 2:
			{
				glTranslated(50,50,0);
				glScaled(400,400,1);
				glPointSize(3);
				glLineWidth(2);
				glColor3f(.0,1.0,.0);
				glBegin(GL_LINES);
					glVertex2f(-.1,-.1);
					glVertex2f(2,-.1);
					glVertex2f(-.1,-.1);
					glVertex2f(-.1,2);
				glEnd();
				
				break;
			}
			
		}
		capas[0].dibPesos();
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
//	Muestra los pesos para cada capa
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


