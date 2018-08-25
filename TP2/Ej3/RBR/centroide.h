#ifndef CENTROIDE_H
#define CENTROIDE_H

// E = (x-nu) * (x-nu)t

class Centroide{
	
private:
	vdouble centroide;
	mdouble datos;
	int tamano;
	double delta=0.4,xmedia,xvarianza,ymedia,yvarianza;
	
public:
	
	Centroide(){
		centroide.clear();
		datos.clear();
		tamano=0;
		xmedia=0;xvarianza=0;
		ymedia=0;yvarianza=0;
	}
	
	Centroide(vdouble v){
		centroide=v;
		datos.clear();
		tamano=v.size();
		xmedia=0;xvarianza=0;
		ymedia=0;yvarianza=0;
	}
	
	void addDato(vdouble newData){ datos.push_back(newData);}
	
	double distancia(vdouble newData){
		
		
		if(tamano!=newData.size())
			return 1000000.0;
		
		double aux=0;
		for(int i=0;i<tamano;i++){
			// diferencia al cuadrado
			aux+=(centroide[i]-newData[i])*(centroide[i]-newData[i]);
		}
		return sqrt(aux);
	}
	
	void actualizar(){
		
		int dSize=datos.size();
		double aux=0;
		
		if(dSize==0)
			return;
		
		for(int i=0;i<tamano;i++){
			for(int j=0;j<dSize;j++){
				aux+=datos[j][i];
			}
			centroide[i]=aux/dSize;
			aux=0;
		}
		datos.clear();
	}
	
	void calcularDV(){
		calcularM();
		
		
	}
	
	void calcularM(){
		
		
		int sdatos = datos.size();
		
		for(int i=0;i<sdatos;i++){
			xmedia+=datos[i][0];
			ymedia+=datos[i][1];
		}
		
		xmedia/=sdatos;
		ymedia/=sdatos;
		
		cout<<"x media "<<xmedia<<"  ymedia "<<ymedia<<endl;
	}
	
	
	void plotCentroide(){
		
		double x1=centroide[0],x2=centroide[1];
		glColor3d(1.0,.0,.0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
			glVertex2d(x1,x2);
		glEnd();

	}
	
	void moverPaso(vdouble datt){
		
		for(int i=0;i<tamano;i++){
			centroide[i]+= (datt[i]-centroide[i])*delta;
		}
	}
	
	void showCentroide(){
		int cSize = centroide.size();
		
		for(int i=0;i<cSize;i++){
			cout<<i+1<<" "<<centroide[i]<<" - ";
		}
	}
	
};




#endif
