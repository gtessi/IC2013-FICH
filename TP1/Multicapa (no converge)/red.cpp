#include <iostream>

#include "red.h"

using namespace std;

red::red(vector<int> estructura, double tasa_aprendizaje, double momento) {
	//cantidad de capas de la red (la primera es de entradas)
	int cant_capas=estructura.size();
	
	//crea las capas de la red
	for (int i=1; i<cant_capas; i++){
////		cout<<endl<<"Capa "<<i<<" ******"<<endl<<endl;
		
		//crea los perceptrones de cada capa
		for (int j=0; j<estructura[i]; j++){
////			cout<<endl<<"Neurona "<<j+1<<" ******"<<endl;
			
			//agrega un perceptron a la capa, con un vector w de la cantidad
			//de salidas de la capa anterior
			c.push_back(perceptron(estructura[i-1],tasa_aprendizaje,momento));
			
////			cout<<"Pesos: ";
////			c[j].mostrar_pesos();
////			cout<<" ---"<<endl<<endl;
		}
		//agrega la capa a la red
		r.push_back(c);
		
		//clear
		c.clear();
	}
	
	//dimensiona el vector de errores
	errores.resize(r.back().size());
}

void red::propagarAdelante(vdouble x){
	double val_y=0;
	int p=r.size()-1; //contador con la posicion de la ultima capa
	
	vdouble ent_temp;
	ent_temp.push_back(-1);
	
	// x es el vector con las entradas de la capa 1
	entradas.push_back(x);
	
	//las capas estan corridas
	//capa oculta 1 == i=0
	//capa oculta 2 == i=1
	//...
	// capa salida es diferente (no hay que agregarle el bias)
	
////	cout<<"--- Inicia PROPAGACION HACIA ADELANTE ---"<<endl<<endl;
	
	//capas ocultas
	for (int i=0; i<p; i++){
////		cout<<endl<<"Capa "<<i+1<<" (OCULTA) ******"<<endl<<endl;
		
		entradas.push_back(ent_temp);
		
		for (unsigned int j=0; j<r[i].size(); j++){
////			cout<<endl<<"Neurona "<<j+1<<" ******"<<endl<<endl;
			
			//calcula la salida
			val_y=r[i][j].calcularSalida(entradas[i]);
			
			//guarda la salida de la capa actual como la entrada de la capa siguiente
			entradas[i+1].push_back(val_y);
			
////			//muestra la salida calculada de la neurona
////			cout<<endl<<" ---------------- "<<endl;
////			r[i][j].mostrar_salida();
////			cout<<" ---------------- "<<endl<<endl;
////			
////			system("pause");
		}
	}
	//*** fin capas ocultas
	
	//capa de salida
////	cout<<endl<<"Capa "<<r.size()<<" (SALIDA) ******"<<endl<<endl;
	
	entradas.push_back(ent_temp);
	entradas.back().clear(); //saca el bias del vector de salidas
	
	for (unsigned int j=0; j<r[p].size(); j++){
////		cout<<endl<<"Neurona "<<j+1<<" ******"<<endl<<endl;
		
		//calcula la salida
		val_y=r[p][j].calcularSalida(entradas[p]);
		
		//guarda la salida de la neurona en la capa de salida
		entradas[p+1].push_back(val_y);
		
////		//muestra la salida calculada de la neurona
////		cout<<endl<<" ---------------- "<<endl;
////		r[p][j].mostrar_salida();
////		cout<<" ---------------- "<<endl<<endl;
////		
////		system("pause");
	}
	
////	cout<<"--- Termina PROPAGACION HACIA ADELANTE ---"<<endl<<endl;
}

void red::propagarAtras(int y_deseada){
	double d=0;
	double sumatoria=0;
	
	int p=r.size()-1;
	
	//aca hay que ver como calcular los deltas y esas cosas
	
	//el vector entradas.back() tiene las salidas
	
////	system("pause");
////	
////	cout<<"--- Inicia PROPAGACION HACIA ATRAS ---"<<endl<<endl;
	
	//capa de salida
////	cout<<endl<<"Capa "<<p+1<<" (SALIDA) ******"<<endl<<endl;
	
	//calcula los deltas
	for (unsigned int j=0; j<entradas.back().size(); j++){
////		cout<<endl<<"Neurona "<<j+1<<" ******"<<endl<<endl;
		
		//calcula los errores de la ultima capa
		errores[j]=y_deseada-entradas.back()[j];
		
		//calcula el delta
		d=errores[j]*(1+entradas.back()[j])*(1-entradas.back()[j])/2;
		
		//guarda el delta en la neurona
		r.back()[j].guardarDelta(d);
		
////		//muestra el delta de la neurona
////		cout<<endl<<" ---------------- "<<endl;
////		cout<<"Delta: "<<r[p][j].devolverDelta()<<endl;
////		cout<<" ---------------- "<<endl<<endl;
////		
////		system("pause");
	}
	//*** fin capa salida
	
	//capas ocultas
	for (int i=p; i>0; --i){
////		cout<<endl<<"Capa "<<i<<" (OCULTA) ******"<<endl<<endl;
		
		for (unsigned int j=0; j<r[i-1].size(); j++){
////			cout<<endl<<"Neurona "<<j+1<<" ******"<<endl<<endl;
			
			//calcula la sumatoria de los deltas con los pesos
			sumatoria=0;
			for (unsigned int k=0; k<r[i].size(); k++)
				sumatoria+=(r[i][k].devolverDelta()*r[i][k].devolverPesos()[j+1]);
			
			//calcula el delta
			d=sumatoria*(1+entradas[i][j+1])*(1-entradas[i][j+1])/2;
			
			//guarda el delta en la neurona
			r[i-1][j].guardarDelta(d);
			
////			//muestra el delta de la neurona
////			cout<<endl<<" ---------------- "<<endl;
////			cout<<"Delta: "<<r[i-1][j].devolverDelta()<<endl;
////			cout<<" ---------------- "<<endl<<endl;
////			
////			system("pause");
		}
	}
	//*** fin capas ocultas
	
////	cout<<"--- Termina PROPAGACION HACIA ATRAS ---"<<endl<<endl;
}

void red::actualizarPesos(){
	int p=r.size(); //cantidad de capas
	double	mu=0, //tasa de aprendizaje
			nu=0, //termino de momento
			delta=0; //delta
	
	vdouble pesos_anteriores, pesos_actuales, pesos_nuevos;
	
////	system("pause");
////	
////	cout<<endl<<"--- Inicia ACTUALIZACION DE PESOS ---"<<endl<<endl;
	
	//recorre las capas de la red
	for (int l=0; l<p; l++){
////		cout<<endl<<"Capa "<<l+1<<" ******"<<endl<<endl;
		
		//recorre las neuronas de cada capa
		for (unsigned int j=0; j<r[l].size(); j++){
////			cout<<endl<<"Neurona "<<j+1<<" ******"<<endl<<endl;
			
			//obtiene la tasa de aprendizaje y el termino de momento de cada neurona
			mu=r[l][j].devolverMu();
			nu=r[l][j].devolverNu();
			
			//obtiene el delta de la neurona
			delta=r[l][j].devolverDelta();
			
			//actualiza los pesos
			
			//pesos anteriores
			pesos_anteriores=r[l][j].devolverPesosAnt();
			
			//pesos actuales
			pesos_actuales=r[l][j].devolverPesos();
			
			//calcula los pesos nuevos
			pesos_nuevos.resize(pesos_actuales.size());
			
			for (unsigned int k=0; k<pesos_actuales.size(); k++)
				pesos_nuevos[k]=pesos_actuales[k]+mu*delta*entradas[l][k]+nu*pesos_anteriores[k];
			
			//actualiza los pesos anteriores con los actuales
			r[l][j].guardarPesosAnt(pesos_actuales);
			
			//actualiza los pesos actuales con los nuevos
			r[l][j].guardarPesos(pesos_nuevos);
			
////			cout<<"---------------------------------"<<endl<<endl;
////			
////			cout<<"Pesos anteriores "<<endl<<endl;
////			mostrar_vector(r[l][j].devolverPesosAnt());
////			
////			cout<<endl<<"Pesos actuales "<<endl<<endl;
////			mostrar_vector(r[l][j].devolverPesos());
////			
////			cout<<endl<<"---------------------------------"<<endl<<endl;
////			
////			system("pause");
		}
	}
	
	//clear
	entradas.clear();
	
////	cout<<"--- Termina ACTUALIZACION DE PESOS ---"<<endl<<endl;
}

void red::retropropagacion(vdouble x, int y_deseada){
	//propagacion hacia adelante
	propagarAdelante(x);
	//propagacion hacia atras
	propagarAtras(y_deseada);
	//actualizar los pesos
	actualizarPesos();
}

double red::prueba(vdouble x){
	double val_y=0;
	
	//propaga la entrada hacia adelante
	propagarAdelante(x);
	
	//clear
	entradas.clear();
	
	//obtiene la salida
	val_y=r.back()[0].devolverSalida();
	
	return val_y;
}
