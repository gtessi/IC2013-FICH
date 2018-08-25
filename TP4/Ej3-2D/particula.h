class Particula{
	
	vector <float> pos,mejorPos,vel;
	int n;
public:
	
	Particula(){pos.clear(); mejorPos.clear(); vel.clear();}
	Particula(int cant){
		pos.clear(); mejorPos.clear(); vel.clear();
		float aux=0;
		for(int i=0;i<cant;i++){
			// ************************ Definimos el rango de valores
			aux=rand()/double(RAND_MAX)*1000-500;
			pos.push_back(aux);
			mejorPos.push_back(aux);
			vel.push_back(0.0);
		}
		n=cant;
	}

	void returnPos(vector<float> &bestPos){
		bestPos=mejorPos;
	}
	
	float funcionPos(){
		return -pos[0]*sin(sqrt(abs(pos[0])));
	}
	float funcionMejorPos(){
		return -mejorPos[0]*sin(sqrt(abs(mejorPos[0])));
	}
	
	void actualizarVelocidad(vector <float>best){
		for(int i=0;i<n;i++){
			vel[i]=vel[i]+0.001*(mejorPos[i]-pos[i])+0.0001*(best[i]-pos[i]);
		}
	}
	
	void actualizarPos(){
		for(int i=0;i<n;i++){
			pos[i]=pos[i]+vel[i];
		}
		if(pos[0]<-500)
			pos[0]=-500;
		if(pos[0]>500)
			pos[0]=500;
			
		actualizarY();
	}
	
	float actualizarY(){
		if(funcionPos()<funcionMejorPos())
			mejorPos=pos;
	}
	
	void show(){
		cout<<"pos "<<pos[0]<<"  mejorPos  "<<mejorPos[0]<<endl;
	}
	
	
	void dibParticula(){
		
		glBegin(GL_POINTS);
			glVertex2f(pos[0],funcionPos());
		glEnd();
		
	}
	
};
