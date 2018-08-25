#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>


using namespace std;

typedef vector< vector< double> > mdouble;


// Definimos las variables
mdouble entradas; //matriz con todos los patrones
mdouble vecinos; //matriz con conexiones de cada neurona



int cant_neuronas; //cantidad de neuronas en el mapa
double it=0;

int mallaX,mallaY,iteRand=0; //cantidad de patrones
int cant_entradas,posx,posy; //cantidad de entradas

double nuInicial=.1,nu=nuInicial; //tasa de aprendizaje
double radioInicial=5,radio=radioInicial; //tamaño de la vecindad

double max_epocas1=200,max_epocas2=300,max_epocas3=100; //cantidad maxima de epocas

bool next,actualizo=false; //bandera


#include "funciones.h"
#include "neurona.h"
#include "mallaNeurona.h"
#include "generaPuntos.h"

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
		malla.ganadora(entradas[i],posx,posy);
		
		//adaptacion de los pesos de las neuronas que esten en la vecindad de la ganadora
		dist=0;
		
		
		//recorre todas las neuronas de la red
		for(int l=posx-radio; l<=posx+radio; l++){
			for(int m=posy-radio;m<=posy+radio;m++){
				
				if(l<0){
					l++;
				}
				if(l>mallaX-1)
					l=posx+radio;
				if(m<0)
					m++;
				if(m>mallaY-1)
					m=posy+radio;
				
				if(l>=0 && l<mallaX && m>=0 && m<mallaY){
					//calcula la distancia
					dist=malla.distancia(posx,posy,l,m);				
					//cout<<"LA DISTANCIA ES:  "<<dist<<endl;
					
					//pregunta si la neurona actual esta dentro de la vecindad de la ganadora (circulo con origen en pesos_g y de radio radio)
					if (dist<=radio){
						
						//esta adentro
						//temp=malla.pesosXY(l,m);
						
						// Calculamos el nu con una dispersion gausiana y cuando vale cero le damos el valor 1
						double nuAux=nu;
						
						malla.newPesos(l,m,sumaV(malla.pesosXY(l,m),escalarV(nuAux,diferenciaV(entradas[i],malla.pesosXY(l,m)))));
						
					}
					//sino no actualiza,esdecir w(n)=w(n)
				}
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
		glScaled(200,200,1);
		graficarEntradas(entradas);
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
			if(i%2){
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
			if(i%10){
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
				if(i%100){
					display_cb();
				}
				cout<<it<<endl;
			}
			cout<<"nu: "<<nu<<endl;
			cout<<"radio: "<<radio<<endl;
			
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
	
	
	//display_cb();
	
}

void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (640,480);
	glutInitWindowPosition (400,100);
	glutCreateWindow ("Ejercicio 4");
	glutDisplayFunc (display_cb);
	glutKeyboardFunc(Keyboard_cb);
	glutSpecialFunc(Special_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
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
	
	GenerarPuntosT();
	//GenerarPuntosCuadrado(-1, 1, -1, 1,0.5, 0.5);
	//GenerarPuntosCirculo(1,0.25,4);
	
	mallaX=15;mallaY=15;
	malla= Malla(mallaX,mallaY,2);
	
	//Leemos la base de datos
	readFile(entradas,"T.txt",false);
	//readFile(entradas,"cuadrado.txt",false);
	//readFile(entradas,"circulo.txt",false);
	
	// Cantidad de entradas
	cant_entradas=entradas.size();
	
	//cout<<endl<<"Graficar...."<<endl;
	//system("pause");
	
	// mostrar pesos
	cout<< "PESOS INICIALES DE LAS NEURONAS"<<endl;
	malla.mostrarPesos();
	
	cout<<"-- MOSTRAMOS LOS PARAMETROS --"<<endl;
	show(entradas);
	
	glutInit(&argc, argv);
	initialize();
	glutMainLoop();
	
	
	
	
	return 0;
}
