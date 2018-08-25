#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

// librerias calcular el tiempo que tarda
#include<ctime>

clock_t startC, finishC;


using namespace std;

#include "individuo.h"
#include "poblacion.h"

poblacion poblado;

void dibRectas(){
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(.0,1.0,.0);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2f(0,0);
		glVertex2f(500,0);
		glVertex2f(0,0);
		glVertex2f(0,500);
		
		glVertex2f(0,100);
		glVertex2f(10,100);
		glVertex2f(0,150);
		glVertex2f(5,150);
		glVertex2f(0,200);
		glVertex2f(10,200);
		glVertex2f(0,150);
		glVertex2f(5,150);
		glVertex2f(0,300);
		glVertex2f(10,300);
	glEnd();
	glPopAttrib();
}


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
	glColor3f(0,0,0); 
	glPointSize(3);
	glLineWidth(1);
	glPushMatrix();
		glTranslated(10,10,0);
		glScaled(1,1,1);
		dibRectas();
		poblado.dibIteracion();
	glPopMatrix();
	
	glutSwapBuffers();
}

void Keyboard_cb(unsigned char key,int xx=0,int yy=0) {	
	switch(key){
	case 'q':{
		poblado.selectProgenitores(20);
		poblado.mezclarProgenitores();
		//cout<<endl<<endl;
		//poblado.mostrarTodo();
		cout<<endl;
		poblado.showBest();
		poblado.showPeor();
		poblado.dibIteracion();
		
		break;
	}
	case 'b':{
		poblado.showBest();
		break;
	}
	case 'w':{
		startC = clock();
		for(int i=0;i<1000;i++){
			poblado.selectProgenitores(20);
			poblado.mezclarProgenitores();
		}
		poblado.showBest();
		finishC = clock();
		cout << "Time (difftime): " << difftime(finishC, startC)/1000000.0<< endl;
		break;
	}
	default:{
		break;
	}
	}
	display_cb();
}

void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (800,750);
	glutInitWindowPosition (20,10);
	glutCreateWindow ("Algoritmo Genetico");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(.96f,.96f,.96f,1.f);
	glutKeyboardFunc(Keyboard_cb);
	glutSpecialFunc(Special_cb);
}


int main (int argc, char **argv) {
	
	srand(time(NULL));
	
	int cantPobla=100, cantGene=10, cantCiudades=10;
	float distancia = 50;
	
	vector< vector<float> > Ciudades;
	
	// Hacemos el risize de la matriz de distancias
	// entre las ciudades
	Ciudades.resize(cantCiudades);
	for(int i=0;i<cantCiudades;i++){
		Ciudades[i].resize(cantCiudades);
	}
	// Inicializamos la matriz con valores aleatorios
	for(int i=0;i<cantCiudades;i++){
		for(int j=i;j<cantCiudades;j++){
			if(i==j)
				Ciudades[i][j]=0;
			Ciudades[i][j] = rand()/float(RAND_MAX) * distancia;
			Ciudades[j][i] = Ciudades[i][j] ;
		}
	}
	
	poblado = poblacion(cantPobla,Ciudades);
	
	poblado.mostrarTodo();
	
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	cin.get();
	return 0;
}
