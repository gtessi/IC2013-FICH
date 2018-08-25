#ifndef CENVECTOR_H
#define CENVECTOR_H


class CenVector{
	
private:
	vector<Centroide> cenVector;
	int tamano;
public:
	CenVector(){
		cenVector.clear();
		tamano=0;
	}
	
	CenVector(int cantCentri, int ndatta){
		tamano=1;
		vdouble auxiliar;
		generarPesos(ndatta,auxiliar);
		Centroide aux=Centroide(auxiliar);
		cenVector.push_back(aux);
		
		for(int i=1;i<cantCentri;i++){
			generarPesos(ndatta,auxiliar);
			if(aceptar(auxiliar)){
				aux=Centroide(auxiliar);
				cenVector.push_back(aux);
				tamano++;
			}else{
				i--;
			}
		}
		
	}
	
	
	bool aceptar(vdouble v){
		
		double aux=0;
		for(int i=0;i<tamano;i++){
			aux=cenVector[i].distancia(v);
			if(aux<.6){
				return false;
			}
		}
		return true;
		
	}
	
	void plotCent(){
		for (int i=0;i<tamano;i++){
			cenVector[i].plotCentroide();
		}
	}
	
	void actualizar(mdouble inn){
		int innSize = inn.size(),pos=0;
		double aux=100,dist=0;
		
		for(int i=0;i<innSize;i++){
			for (int j=0;j<tamano;j++){
				dist = cenVector[j].distancia(inn[i]);
				if(dist<aux){
					pos=j; aux=dist;
				}
			}
			aux=100;
//			cenVector[pos].addDato(inn[i]);
			cenVector[pos].moverPaso(inn[i]);
		}
		
		for(int i=0;i<tamano;i++){
			cenVector[i].actualizar();
		}
		
	}
	
	void actualizarPaso(vdouble inn){
		
		double aux=100,dist=0;
		int pos=0;
		
		for (int j=0;j<tamano;j++){
			dist = cenVector[j].distancia(inn);
			if(dist<aux){
				pos=j; aux=dist;
			}
		}
		
		cenVector[pos].moverPaso(inn);
		
	}
	
	void calcularDV(mdouble inn){
		
		int innSize = inn.size(),pos=0;
		double aux=100,dist=0;
		
		for(int i=0;i<innSize;i++){
			for (int j=0;j<tamano;j++){
				dist = cenVector[j].distancia(inn[i]);
				if(dist<aux){
					pos=j; aux=dist;
				}
			}
			aux=100;
			cenVector[pos].addDato(inn[i]);
		}
		
		for(int i=0;i<tamano;i++){
//			cenVector[i].calcularDV();
			cenVector[i].calcularM();
		}
		
	}
	
	void show(){
		
		for(int i=0;i<tamano;i++){
			cenVector[i].showCentroide();
			cout<<endl;
		}
	}
	
};






#endif
