void GenerarPuntosCuadrado(int x1, int x2, int y1, int y2, double dx, double dy){
	// Nombre de las variables:
//	x1 = posicion desde x
//	x2 = posicion hasta x
//	y1 = posicion desde y
//	y2 = posicion hasta y
//	dy dx, el paso de cada uno
	
	mdouble posiciones;
	
	int canti_nodos_x=round((x2-x1)/dx)+1;
	int canti_nodos_y=round((y2-y1)/dy)+1;
	
	double posx=0;
	double posy=0;
	vector<double> fila_aux;
	for(int i=0; i<canti_nodos_x; i++){
		for(int j=0; j<canti_nodos_y;j++){
			posx=x1+i*dx;
			posy=y1+j*dy;
			fila_aux.push_back(posx);
			fila_aux.push_back(posy);
			posiciones.push_back(fila_aux);
			fila_aux.clear();
		}		
		
	}
	string file="cuadrado.txt";
	ofstream archi(file.c_str(), ios::trunc);
	
	unsigned int nRow=posiciones.size(); //Numero de filas
	vector<double>::iterator itx, final;
	
	if(archi.is_open()){	
		for (unsigned int i=0; i<nRow; i++){ //Habria que mejorar como lee el tamanio, por ahora funca
			//Graba los 'nCol' datos por filas
			itx=posiciones[i].begin();
			final=itx++;
			archi<<*itx<<","<<*final<<endl;
		}
		archi.close();
	}
	
}



/////***************************************************////


void GenerarPuntosCirculo(double r,double dr, double dt){
//	dr=paso de radio;
//	dt= paso de theta;
//	r= radio;
	
	double pi=3.14159265358979;
	double dtheta=pi/dt;
	
	
	
	mdouble posiciones;
	
	
	int canti_nodos_r=round(r/dr)+1;
	int canti_nodos_theta=round(2*pi/dtheta);
	
	double posx=0;
	double posy=0;
	vector<double> fila_aux;
	for(int i=1; i<canti_nodos_r; i++){
		for(int j=0; j<canti_nodos_theta;j++){
			posx=dr*i*cos(j*dtheta);
			posy=dr*i*sin(j*dtheta);
			fila_aux.push_back(posx);
			fila_aux.push_back(posy);
			posiciones.push_back(fila_aux);
			fila_aux.clear();
		}	
	}
	fila_aux.push_back(0);
	fila_aux.push_back(0);
	posiciones.push_back(fila_aux);
	string file="circulo.txt";
	ofstream archi(file.c_str(), ios::trunc);
	
	unsigned int nRow=posiciones.size(); //Numero de filas
	vector<double>::iterator itx, final;
	
	if(archi.is_open()){	
		for (unsigned int i=0; i<nRow; i++){ //Habria que mejorar como lee el tamanio, por ahora funca
			//Graba los 'nCol' datos por filas
			itx=posiciones[i].begin();
			final=itx++;
			archi<<*itx<<","<<*final<<endl;
		}
		archi.close();
	}	
}




//////////////***************************************


void GenerarPuntosT(){
	// Nombre de las variables:
//	x1 = posicion desde x
//	x2 = posicion hasta x
//	y1 = posicion desde y
//	y2 = posicion hasta y
//	dy dx, el paso de cada uno
	
	double dx=0.05;
	double dy=0.05;
	
	//Generar rectangulo horizontal
	double x1=-1;
	double x2=1;
	double y1=0.5;
	double y2=1;	
	
	mdouble posiciones;
	
	int canti_nodos_x=round((x2-x1)/dx)+1;
	int canti_nodos_y=round((y2-y1)/dy)+1;
	
	//cout<<canti_nodos_x<<" "<<canti_nodos_y<<endl;
	
	double posx=0;
	double posy=0;
	vector<double> fila_aux;
	for(unsigned int i=0; i<canti_nodos_x; i++){
		for(unsigned int j=0; j<canti_nodos_y;j++){
			posx=x1+i*dx;
			posy=y1+j*dy;
			fila_aux.push_back(posx);
			fila_aux.push_back(posy);
			posiciones.push_back(fila_aux);
			fila_aux.clear();
			
			//cout<<posx<<"  "<<posy<<endl;
		}		
		//cout<<endl;
	}
	
//	Generar rectangulo vertical
	fila_aux.clear();
	x1=-0.25;
	x2=0.25;
	y1=-1;
	y2=0.5;	
	
	canti_nodos_x=round((x2-x1)/dx)+1;
	canti_nodos_y=round((y2-y1)/dy);
	
	posx=0;
	posy=0;
	
	for(int i=0; i<canti_nodos_x; i++){
		for(int j=0; j<canti_nodos_y;j++){
			posx=x1+i*dx;
			posy=y1+j*dy;
			fila_aux.push_back(posx);
			fila_aux.push_back(posy);
			posiciones.push_back(fila_aux);
			fila_aux.clear();
		}		
		
	}
	
	string file="T.txt";
	ofstream archi(file.c_str(), ios::trunc);
	
	unsigned int nRow=posiciones.size(); //Numero de filas
	vector<double>::iterator itx, final;
	
	if(archi.is_open()){	
		for (unsigned int i=0; i<nRow; i++){ //Habria que mejorar como lee el tamanio, por ahora funca
			//Graba los 'nCol' datos por filas
			itx=posiciones[i].begin();
			final=itx++;
			archi<<*final<<","<<*itx<<endl;
		}
		archi.close();
	}
	
}
