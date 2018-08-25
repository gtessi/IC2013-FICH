#include <iostream>

#include "perceptron.h"

using namespace std;


//  VARIABLES
mdouble entradas;////Vector de entradas
vector<double> w; //Vector de pesos
vector<double> error_prueba;
vector<int> salidas;//Vector de salidas

double disp=0.05; //Dispersion de los datos

unsigned int pos=0;
int cant_epocas, contador_epocas=0;
int op,op_criterio; //Entrenar OR o XOR
double nu; //=0.1 //Velocidad de Aprendizaje
//double error=100.0;
double error_deseado=0.0;
int num_ejemplos; //Cantidad de ejemplos aleatorios a generar
double correcto=0;
bool corte=true;


void reshape_cb (int w, int h) {
	if (w==0||h==0) return;
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D(0,w,0,h);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}

// Graficas
void display_cb() {
	glClear(GL_COLOR_BUFFER_BIT);
	graficarEntradas(entradas,salidas);
	graficarRectaPesos(w);
	glutSwapBuffers();
	
//	pruebaentre(w,entradas,salidas,nu,cant_epocas,pos,contador_epocas);
	
//	system("pause");
}

void Special_cb(int key, int xm=0, int im=0){
	if(key ==GLUT_KEY_F12)
		exit(EXIT_SUCCESS);
	
}

void Keyboard_cb(unsigned char key,int xx=0,int yy=0) {
	switch (key){
		case 'q':{		
			double tecla1,tecla2;
			cout<<"Ingrese primer valor:  ";
			cin>>tecla1;
			cout<<"Ingrese segundo valor:  ";
			cin>>tecla2;
			vector<double> aux;
			aux.push_back(-1);
			aux.push_back(tecla1);
			aux.push_back(tecla2);			
			if (prodInterno(w,aux) < 0 ){
				cout<<"El resultado es: "<<prodInterno(w,aux)<<" == "<<"-1"<<endl;
			}else cout<<"El resultado es: "<<prodInterno(w,aux)<<" == "<<"1"<<endl;		
			aux.clear();
			break;
		}
	case 'w':{		
		entrenador(w,entradas,salidas,nu);
		cout<<endl<<"Pesos: ";
		mostrar_vector(w);
		prueba(w,entradas,salidas,error_prueba,correcto);
		cout<<"Porcentaje de aciertos: "<<correcto<<endl;
		display_cb();
		break;
		}	
	default:{
			if(pos<entradas.size()){
				entrenamiento(w,entradas[pos],salidas[pos],nu);				
				cout<<endl<<"Pesos: ";
				mostrar_vector(w);
//				cout<<" -Error: "<<error<<endl;				
				pos++;
			}					
			display_cb();
		}
	
	}
	
}

//Inicializacion
void initialize() {
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);//inicializa la ventana en RGBA y doble buffer
	glutInitWindowSize (640,480);//ventana de 640x480
	glutInitWindowPosition (600,100);//posiciona en la posicion 100,100
	glutCreateWindow ("Guia 1 ejercicio 1");//titulo de la ventana
	glutKeyboardFunc (Keyboard_cb); // funcion al callback del teclado
	glutDisplayFunc (display_cb);// funcion para dibujar
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);//color de fondo: blanco
	glutSpecialFunc(Special_cb);
}


int main (int argc, char **argv) {
	// genera semilla pseudoaleatoria
	srand(time(0));
	
	cout<<"*******************************************"<<endl;
	cout<<"              EJERCICIO 1"<<endl;
	cout<<"*******************************************"<<endl;
//	cout<<"Realizar Entrenamiento: Seleccionar la opcion"<<endl;
//	cout<<"1-OR"<<endl;
//	cout<<"2-XOR"<<endl;
//	cin>>op;
//	cout<<"Ingresar velocidad de aprendizaje: ";
//	cin>>nu;
//	cout<<"Ingresar cantidad de ejemplos: ";
//	cin>>num_ejemplos;
//	cout<<"Ingresar epocas: ";
//	cin>>cant_epocas;
//	cout<<"Ingresar error (tolerancia de aciertos): ";
//	cin>>error_deseado;
//	cout<<"Seleccionar cirterio de corte: "<<endl;
//	cout<<"1-Automatico"<<endl;
//	cout<<"2-Manual"<<endl;
//	cin>>op_criterio;
//	
	op=1;
	nu=0.05;
	num_ejemplos=1000;
	cant_epocas=10;
	error_deseado=90;
	op_criterio=1;
	
	
	switch (op){
	case 1:{
		readFile(entradas,salidas,"datosOR.txt",true);
		getRandMatrix(entradas,salidas,num_ejemplos,disp);
		saveFile(entradas,salidas,"entradasOR.txt");
		generarPesos(entradas[0].size(),w);	
		break;
	}
	case 2:{		
		readFile(entradas,salidas,"datosXOR.txt",true);
		getRandMatrix(entradas,salidas,num_ejemplos,disp);
		saveFile(entradas,salidas,"entradasXOR.txt");
		generarPesos(entradas[0].size(),w);
	break;		
	}
	}
	
	switch(op_criterio){
	case 1:{			
		while(corte){
			//Realiza una época
			entrenador(w,entradas,salidas,nu);
			contador_epocas++;
			//Calculamos el acierto de las entradas
			prueba(w,entradas,salidas,error_prueba,correcto);
			//Criterios de corte
			//Por error tolerado
			if(correcto>error_deseado)
				corte=false;//Criterio de Corte
			//Por epoca
			if(contador_epocas==cant_epocas)
				corte=false;//Criterio de Corte
		}			
		cout<<"Peso Optimo: ";
		mostrar_vector(w);
		//int porcentaje;
		cout<<"Calidad: "<<correcto<<"%"<<endl;
		cout<<"Epocas realizadas: "<<contador_epocas;
		break;
	}
	case 2:{
//			Graficar:
		cout<<"--------------------------------------------------------"<<endl;
		cout<<"Tecla q: Consulta sobre un punto en particular"<<endl;
		cout<<"Tecla w: Visualizar la recta de pesos para cada Epoca"<<endl;
		cout<<"Cualquier Tecla: Visualizar la recta de pesos para cada entrenamiento"<<endl;
		glutInit (&argc, argv);
		initialize();
		glutMainLoop();
		
		break;
	}
		
	}
	
	
//	readFile(entradas,salidas,"datosOR.txt",true);
//	getRandMatrix(entradas,salidas,100);
//	mezclar(entradas,salidas);
//	saveFile(entradas,salidas,"entradasOR.txt");
//	generarPesos(entradas[0].size(),w);
//	entrenador(w,entradas,salidas,0.05);
//	//Calculamos el acierto de las entradas
//	prueba(w,entradas,salidas,error_prueba,correcto);
//	mostrar_vector(w);
//	
//	mostrar_vector(error_prueba);
//	cout<<"*********"<<endl;
//	cout<<correcto<<endl;
//	cout<<"*********"<<endl;
//	cout<<"*********"<<endl;
//	cout<<salidas.size()<<endl;
//	cout<<"*********"<<endl;
//	
	return 0;
}
