#ifndef MALLANEURONA_H
#define MALLANEURONA_H

class Malla{
	
	vector < vector < Neurona> > malla;
	
public:
	Malla(){};
	Malla(int x,int y, int dimension){
		srand(time(NULL));
		
		vector< Neurona > aux;
		for(int i=0;i<x;i++){
			for(int j=0;j<y;j++){
				double idx=i*x+j;
				Neurona naux=Neurona(dimension,idx);
				aux.push_back(naux);
			}
			malla.push_back(aux);
			aux.clear();
		}
		
		
	}
	
	// pesos i
	vector<double> pesosXY(int x,int y){
		return malla[x][y].pesos();
	}
	
	// actualizar pesos
	void newPesos(int x,int y,vector<double> w){
		malla[x][y].newPesos(w);
	}
	
	// diferencia
	void diferencia(int x,int y, double dif){
		malla[x][y].diferencia(dif);
	}
	
	// return diferencia
	double diferencia(int x,int y){
		return malla[x][y].diferencia();
	}
	// Distancia
	double distancia(int x,int y,int x1,int y1){
		return (abs(x-x1)+abs(y-y1));
		//return malla[x][y].distancia(malla[x1][y1]);
	}
	
	// Funcion de Discriminacion (ganadora)
	void ganadora(vector<double> in, int &x,int &y){
		int xmalla=malla.size(), ymalla=malla[0].size(),idx;
		double minimo=9999999999,temp;
		
		for(int i=0; i<xmalla; i++){
			for(int j=0;j<ymalla;j++){
				temp=norma1(diferenciaV(in,pesosXY(i,j)));
				//cout <<" Distancias:  "<< temp <<endl;
				
				if (temp<minimo){
					minimo=temp;
					x=i; y=j;
				}
			}
		}
	}
	
	// graficamos la matriz de pesos
	void graficarPesos(){
		
		int matrizSizeX = malla.size(),matrizSizeY = malla[0].size();
		vector<double> aux;
		
		glPointSize(4);
		glColor3b(1,0,1);
		
		glBegin(GL_POINTS);
		for(int i=0;i<matrizSizeX;i++){
			for(int j=0;j<matrizSizeY;j++){
				aux=pesosXY(i,j);
				glVertex2d(aux[0],aux[1]);
			}
		}
		glEnd();
		
		glBegin(GL_LINES);
		for(int i=0;i<matrizSizeX;i++){
			for(int j=0;j<matrizSizeY;j++){
				
				if(j!=matrizSizeY-1){					
					aux=pesosXY(i,j);
					glVertex2d(aux[0],aux[1]);
					aux=pesosXY(i,j+1);
					glVertex2d(aux[0],aux[1]);
				}
				if(matrizSizeX-1!=i){
					aux=pesosXY(i,j);
					glVertex2d(aux[0],aux[1]);
					aux=pesosXY(i+1,j);
					glVertex2d(aux[0],aux[1]);
				}
			}
		}
		glEnd();
		
	}
	
	// Mostrar pesos
	void mostrarPesos(int i,int j){
		malla[i][j].mostrarPesos();
	}
	
	// Mostrar Pesos
	void mostrarPesos(){
		for(int i=0;i<malla.size();i++){
			for(int j=0;j<malla[0].size();j++){
				mostrarPesos(i,j);
			}
		}
	}
};

#endif
