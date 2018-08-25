
float functionVal(int i,float x);



void iniCero(int *vec, int cant){
	
	for (int i=0;i<cant;i++){
		vec[i]=0;
	}
}

float functionVal(int i,float x){
	
	float valor=0;
	if(i==1){
		valor=-x*sin(pow(abs(x),0.5));
	}
	if(i==2){
		valor= x+5*sin(3*x)+8*cos(5*x);
	}
	return valor;
}

void dibPuntos(int j){
	//glBegin(GL_POINTS);
	glBegin(GL_LINES);
	if(j==1){
		for(int i=-512;i<513;i++){
			float aux=functionVal(j,i);
			glVertex2f(i,aux);
			aux=functionVal(j,i-1);
			glVertex2f(i,aux);
		}
	}
	if(j==2){
		for(float i=0;i<30;i+=0.01){
			float aux=functionVal(j,i);
			glVertex2f(i,aux);
			aux=functionVal(j,i-0.01);
			glVertex2f(i,aux);
		}
	}
	glEnd();
	
}

