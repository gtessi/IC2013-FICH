
// Funciones auxiliares, lectura de archivos scv
void readFile(mdouble &X, vector<double> &Y, string file, bool insX0);
void explode(string line, mdouble&X, vector<double>&Y, bool insX0);


/**
Lee de un archivo valores de varias entradas y una salida separados por comas
*/
void readFile(mdouble &X, vector<double> &Y, string file, bool insX0){
	ifstream archi;
	archi.open(file.c_str());
	
	if(archi.is_open()){
		while(!archi.eof()){
			string str_line;
			getline(archi,str_line);
			
			if(!archi.eof())
				//Manda el string al parser para separar los datos
				//por comas en los vectores X y Y
				explode(str_line, X, Y, insX0);
		}
		
		archi.close();
	}
}

/**
Dado un string, separa su contenido, separado por comas,
en valores numericos y los agrega a los vectores pasados por referencia
*/
void explode(string line, mdouble&X, vector<double>&Y, bool insX0){
	vector<double>Aux;
	//Segun la bandera insX0, inserta como primer elemento
	//el valor del X0 (-1) o no (no se necesita cuando particionamos)
	if(insX0)
		Aux.push_back(-1); //Valor que proporciona movilidad a la recta (abcisa)
	
	char Buffer[25]; //Maximo 25 cifras
	//for(int l=0;l<25;l++) Buffer[l] = '\0';
	int i = 0;
	//Lee el string hasta el final
	for (int k=0; line[k] != '\0'; k++){
		//Guarda los primero 'k' caracteres del
		//string hasta la coma en el Buffer
		if (line[k] != ','){
			Buffer[i] = line[k];
			i++;
		}else{
			//Sino, agrega una finalizacion al Buffer
			//y mete la cadena convertida en el vector auxiliar
			Buffer[i] = '\0';
			Aux.push_back(atof(Buffer));
			//Vacio el Buffer y posiciono el cursor en en inicio
			for(int l=0;l<25;l++) Buffer[l] = '\0';
			i = 0;
		}
	}
	Y.push_back(atoi(Buffer)); //El ultimo que lei es la salida	
	X.push_back(Aux); //Agrego las nuevas entradas como filas de la matriz
}
