class Enjambre{
	
	vector<Particula> enjambre;
	vector<float> mejorPos;
	float valorMejorpos;
	int cantParticulas;
	
public:
	
	Enjambre(){};
	Enjambre(int cParticulas, int cValores){
		Particula aux;
		cantParticulas=cParticulas;
		for(int i=0;i<cantParticulas;i++){
			aux=Particula(cValores);
			enjambre.push_back(aux);
		}
		
		float valAux=enjambre[0].funcionPos();
		for(int i=1;i<cantParticulas;i++){
			if(enjambre[i].funcionPos()<valAux){
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
		
		cout<<"best is  "<<mejorPos[0]<<endl;
		for(int i=0;i<cantParticulas;i++){
			enjambre[i].show();
		}
	}
	
	void dibEnjambre(){
		for(int i=0;i<cantParticulas;i++){
			enjambre[i].dibParticula();
		}
	}
	
};
