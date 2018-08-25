#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>


using namespace std;

typedef vector< vector< double> > mdouble;


// Definimos las variables
mdouble entradas; //matriz con todos los patrones
vector <int> salidas;

int cant_neuronas; //cantidad de neuronas en el mapa
double it=0;

int mallaX,mallaY,iteRand=0; //cantidad de patrones
int cant_entradas,posx,posy; //cantidad de entradas

double nuInicial=.5,nu=nuInicial; //tasa de aprendizaje
double radioInicial=4,radio=radioInicial; //tamaño de la vecindad

double max_epocas1=200,max_epocas2=500,max_epocas3=300; //cantidad maxima de epocas

bool next,actualizo=false; //bandera


#include "funciones.h"
#include "neurona.h"
#include "mallaNeurona.h"
#include "generaPuntos.h"
#include "Readfile.h"

Malla malla;
typedef vector< vector< Neurona> > mNeurona;
// y mas...

void Epoca(double iteraciones){
	next=true;//BAndera
	int k=0;
	//variables temporales
	double dist;
	vector<double> temp;
	
	if(iteraciones>max_epocas1 && iteraciones<=max_epocas2+max_epocas1){
		radio= nuRadioVariable(iteraciones-max_epocas1, radioInicial, 1,max_epocas2);
		nu= nuRadioVariable(iteraciones-max_epocas1, nuInicial, 0.1,max_epocas2);
	}
	if(iteraciones > max_epocas2+max_epocas1){
		radio=0;
		nu=0.05;
	}
	//recorre los patrones
	for(int i=0; i<cant_entradas; i++){
		//aca viene la funcion de discriminacion (determina neurona ganadora)
		malla.ganadora(entradas[i],salidas[i],posx,posy);
		
		//recorre todas las neuronas de la red
		for(int l=0; l<mallaX; l++){
			for(int m=0;m<mallaY;m++){
				
				//calcula la distancia
				dist=malla.distancia(posx,posy,l,m);				
				
				//pregunta si la neurona actual esta dentro de la vecindad de la ganadora (circulo con origen en pesos_g y de radio radio)
				if (dist<=radio){
					
					// Calculamos el nu con una dispersion gausiana y cuando vale cero le damos el valor 1
					double nuAux=nu;
					
					malla.newPesos(l,m,sumaV(malla.pesosXY(l,m),escalarV(nuAux,diferenciaV(entradas[i],malla.pesosXY(l,m)))));
					
				}
				//sino no actualiza,esdecir w(n)=w(n)
			}
			
		}
	}

	//recorrer todas las neuronas
	//verificar que las diferencias acumuladas promedio sean menor a una tolerancia
	double error=0;
	for(int l=0;l<mallaX;l++){
		for(int m=0; m<mallaY;m++){
			error+=abs(malla.diferencia(l,m));
		}
	}
	
	
	//toma el promedio del error acumulado
	error/=cant_neuronas;
	
}//fin: cienEpocas();

//OpenGL
void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
		glTranslated(320,240,0);
		glScaled(60,60,1);
		graficarEntradas(entradas,salidas);
		malla.graficarPesos();
	glPopMatrix();	
	glutSwapBuffers();
}

void Keyboard_cb(unsigned char key,int xx=0,int yy=0) {	
	
	
	switch(key){
	//etapa 1
	case 'q':
		{		
		for(int i=0;i<max_epocas1;i++){
			Epoca(it);
			it++;
			if(!(i%10)){
				display_cb();
			}
			cout<<it<<endl;
		}
		cout<<" saliooo"<<endl;
		break;
		
	}
	//etapa 2
	case 'w':
		{
		for(int i=0;i<max_epocas2;i++){
			Epoca(it);
			it++;
			if(!(i%10)){
				display_cb();
			}
			cout<<it<<endl;
		}
		cout<<"nu: "<<nu<<endl;
		cout<<"radio: "<<radio<<endl;
		
		break;
		}
		//etapa 3
	case 'e':
		{
			for(int i=0;i<max_epocas3;i++){
				Epoca(it);
				it++;
				if(!(i%10)){
					display_cb();
				}
				cout<<it<<endl;
			}
			cout<<"nu: "<<nu<<endl;
			cout<<"radio: "<<radio<<endl;
			
			int posx=0,posy=0,contador=0;
			
			for(int i=0;i<cant_entradas;i++){
				malla.ganadora(entradas[i],salidas[i],posx,posy);
				if(malla.claseReturn(posx,posy) == salidas[i])
					contador++;
			}
			
			cout<<endl<<"ACIERTOS:  "<<contador*100/cant_entradas<<" %"<<endl;
			
			break;
		}
	case 'p':{
		// mostrar pesos
		cout<< "PESOS EN ESTE INSTANTE"<<endl;
		malla.mostrarPesos();
		break;
	}
	default:{
		break;
	}
	}
	
}

void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (700,600);
	glutInitWindowPosition (400,100);
	glutCreateWindow ("Ejercicio 4");
	glutDisplayFunc (display_cb);
	glutKeyboardFunc(Keyboard_cb);
	glutSpecialFunc(Special_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(0.f,0.f,0.f,0.f);
}


int main (int argc, char **argv) {
		
	// *** algoritmo
	// 1. generar el mapa, la grilla de neuronas, vector de conexiones (conexion de las neuronas)
	// 2. pasar la entrada a cada neurona
	// 3. encontrar la neurona ganadora
	// 4. ver el tema de los entornos (poenele que si)
	// 5. actualizar los pesos segun la distancia (ganadora=mayor, vecinos=menor)
	// 6. iterar unas 1000 veces hasta que la vecindad sea 0 (neurona ganadora)
	// 7. transicion
	// 8. una vez ajustados los parametros de aprendizaje y vecindad, iterar hasta convergencia
	
	srand(time(NULL));
	
	mallaX=10;mallaY=10;
	malla= Malla(mallaX,mallaY,2);
	
	readFile(entradas,salidas,"clouds.csv",false);
	
	// Cantidad de entradas
	cant_entradas=entradas.size();
	
	glutInit(&argc, argv);
	initialize();
	glutMainLoop();
	
	
	
	
	return 0;
}
