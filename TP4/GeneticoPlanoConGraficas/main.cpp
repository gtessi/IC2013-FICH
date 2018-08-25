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




void circulo_Bresenham(int xc, int yc, int r) {
	
	
	glBegin(GL_POINTS);
	if (!r){
		glVertex2i(xc,yc);
		glEnd();
		return;
	}
	
	int x=0, y=r, h=1-r;
	while (y>x){
		glVertex2i( x+xc, y+yc);
		glVertex2i( x+xc,-y+yc);
		glVertex2i(-x+xc, y+yc);
		glVertex2i(-x+xc,-y+yc);
		
		glVertex2i( y+xc, x+yc);
		glVertex2i( y+xc,-x+yc);
		glVertex2i(-y+xc, x+yc);
		glVertex2i(-y+xc,-x+yc);
		//cout << x << "," << y << "\n";
		if (h>=0){ // SE
			h+=((x-y)<<1)+5;
			y--;
		}
		else { // E
			h+=(x<<1)+3;
		}
		x++;
	}
	// x==y => no hace falta intercambiar
	glVertex2i( x+xc, y+yc);
	glVertex2i( x+xc,-y+yc);
	glVertex2i(-x+xc, y+yc);
	glVertex2i(-x+xc,-y+yc);
	glEnd();
	//cout << endl;
}



void dibRectas(){
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(.0,1.0,.0);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex2f(-100,0);
		glVertex2f(100,0);
		glVertex2f(0,-100);
		glVertex2f(0,100);
	glEnd();
	glPopAttrib();
}

void dibCirculos(int cantidad){
	float paso=100.0/float(cantidad),valor=0,x=0;
	float color1=0,color2=0;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPointSize(1.3);
	
	for(int i=0;i<cantidad;i++){
		x+=paso;
		valor=pow(pow(x,2),0.25)*(pow(sin(50*(pow(pow(x,2),0.1))),2)+1);
		// valor [0,25] hago el mapeo de los colores
		float max=12.5;
		if(valor<max){
			color1=valor/max;
			color2=1-valor/max;
			glColor3f(.0,color1,color2);
		}else{
			valor-=max;
			color1=valor/max;
			color2=1-valor/max;
			glColor3f(color1,color2,.0);
		}
		
		circulo_Bresenham(0,0,int(x));
		
	}
	
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
	
	glTranslated(650,350,0);
	glScaled(3,3,1);
	
	dibRectas();
	dibCirculos(100);
	poblado.dibPoblacion();
	glPopMatrix();
	
	glutSwapBuffers();
}

void Keyboard_cb(unsigned char key,int xx=0,int yy=0) {	
	switch(key){
	case 'q':{
		poblado.selectProgenitores(20);
		poblado.mezclarProgenitores();
		poblado.showBest();
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
	glutInitWindowSize (1300,750);
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
	
	int cantPobla=100, cantGene=30;
	
	poblado = poblacion(cantPobla,cantGene);
	
	poblado.mostrarTodo();
	
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	cin.get();
	return 0;
}
