

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

clock_t startC, finishC;

using namespace std;

#include "particula.h"
#include "enjambre.h"


// ***************** VARIABLES GLOBALES *****************
Enjambre enja;

int w=800,h=750;

void dibCurba(){
	glBegin(GL_LINES);
		float i=0, dt=0.1;
		while(i<=20){
			glVertex2f(i,i+5*sin(3*i)+8*cos(5*i));
			glVertex2f(i+dt,(i+dt)+5*sin(3*(i+dt))+8*cos(5*(i+dt)));
			i+=dt;
		}
	glEnd();
}

void dibRectas(){
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(.0,1.0,.0);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(-30,0);
	glVertex2f(30,0);
	glVertex2f(0,-30);
	glVertex2f(0,30);
	
	float pos=0,ap=1;
	// eje x
	for(int i=0;i<30;i++){
		glVertex2f(pos+ap*i,-0.25);
		glVertex2f(pos+ap*i,0.25);
	}
	// eje y
	for(int i=0;i<30;i++){
		glVertex2f(-0.25,pos+ap*i);
		glVertex2f(0.25,pos+ap*i);
	}
	glEnd();
	glPopAttrib();
}

void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,1); glLineWidth(3);
	glPointSize(4);
	glLineWidth(1);
	glPushMatrix();
		
		glTranslated(w*0.25,h*0.25,0);
		glScaled(15,15,1);
		dibRectas();
		enja.dibEnjambre();
		glColor3f(1.0,0.,0.);
		dibCurba();
		
	glPopMatrix();
	glutSwapBuffers();
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




void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F1)
		exit(EXIT_SUCCESS);
}


void Keyboard_cb(unsigned char key,int xx=0,int yy=0) {	
	switch(key){
	case 'q':{
		enja.evaluarTodos();
		display_cb();
		break;
	}
	case 'w':{
		startC=clock();
		for(int i=0;i<500;i++){
			enja.evaluarTodos();
			display_cb();
		}
		finishC=clock();
		
		cout<<"Tiempo: "<<difftime(finishC,startC)/1000.0<<endl;
		break;
	}
	}
}

void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (w,h);
	glutInitWindowPosition (400,50);
	glutCreateWindow ("Ventana OpenGL");
	glutDisplayFunc (display_cb);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
	glutKeyboardFunc(Keyboard_cb);
	glutSpecialFunc(Special_cb);
}

int main (int argc, char **argv) {
	
	enja=Enjambre(100,1);
	
	glutInit (&argc, argv);
	initialize();
	glutMainLoop();
	return 0;
}
