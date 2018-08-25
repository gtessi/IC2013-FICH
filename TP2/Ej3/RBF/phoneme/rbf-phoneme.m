clear all
close all
clc
% ------------------------------------------------------
% carga el archivo en la matriz patrones
patrones=csvread('phoneme.csv');

% cantidad de funciones de base radial
clases=6;

% cantidad de neuronas de salida
neuronas=2;

% tasa de aprendizaje
nu=0.1;

% cantidad de epocas
max_epocas=100;

% tolerancia
tol=0.8;

% ------------------------------------------------------

% cantidad de valores en cada fila
cant_valores=size(patrones,2);

% cantidad de entradas
cant_entradas=cant_valores-1;

% cantidad de patrones
cant_patrones=size(patrones,1);

% *** inicia etapa de entrenamiento no supervisado ***
disp('Inicia etapa de entrenamiento no supervisado')

% define el vector de indices con clases
idx_clases=zeros(cant_patrones,2);

% lo mezcla
idx_clases(:,1)=shuffle(1:cant_patrones)';

% le asigna una clase a cada patron
cont=1;

while(cont<=cant_patrones)
    idx_clases(cont,2)=mod(cont-1,clases)+1;
    cont=cont+1;
end

% genera los centroides
mu=zeros(clases,cant_entradas);

for k=1:clases
    % calcula los centroides para cada clase
    mu(k,:)=calculaCentroide(patrones,idx_clases,k);
end

% iteraciones
it=0;

% bandera de control
bandera=1;

while(bandera~=0)
    % calcula las reasignaciones de los patrones al centroide mas cercano
    [idx_clases,reasignaciones]=actualizarPatrones(patrones,idx_clases,mu);
    
    % recalcula los centroides
    for k=1:clases
        % recalcula los centroides para cada clase
        mu(k,:)=calculaCentroide(patrones,idx_clases,k);
    end
    
    % actualiza la bandera cuando no hay reasignaciones
    if reasignaciones==0
        bandera=0;
    end
    
    % actualiza el contador de iteraciones
    it=it+1;
end

disp(['Iteraciones: ',num2str(it)])

% *** termina etapa de entrenamiento no supervisado ***
disp('Termina etapa de entrenamiento no supervisado')
disp('------------------------------------------------------')

% ------------------------------------------------------

% *** inicia etapa de entrenamiento supervisado ***
disp('Inicia etapa de entrenamiento supervisado')

% entrenamiento
% define la matriz de pesos
pesos=zeros(neuronas,clases+1);

% inicializa la matriz de pesos con valores aleatorios
for k=1:neuronas
    pesos(k,:)=generarPesos(clases+1,0.5); % +1 = bias
end

% matriz de salidas deseadas
yd=zeros(cant_patrones,neuronas);

% codifica las salidas
for k=1:cant_patrones
    if patrones(k,cant_valores)==0
        yd(k,:)=[1 -1];
    end
    if patrones(k,cant_valores)==1
        yd(k,:)=[-1 1];
    end
end

next=1;
epoca=1;

while(next)
    for k=1:cant_patrones
        % aca hay que meter la entrada en la funcion de base radial, ya tengo
        % el mu falta definir el sigma
        
        idx=idx_clases(k,1);
        
        % entrada
        x=patrones(idx,1:cant_entradas);
        
        % arma el vector de entradas de la capa de salida
        g=zeros(1,clases+1);
        g(1)=-1;
        
        % funciones gaussianas
        for l=1:clases
            g(l+1)=gaussiana(x,mu(l,:));
        end
        
        % recorre las neuronas de salida
        v=zeros(1,neuronas);
        y=v;
        e=y;
        
        for l=1:neuronas
            % calcula el producto interno
            v(l)=g*pesos(l,:)';
            
            % funcion de activacion
            y(l)=sgn(v(l));
            
            % error
            e=y(l)-yd(idx,l);
            
            % actualiza los pesos
            pesos(l,:)=pesos(l,:)-nu*e*g;
        end
    end
    
    % calcula el contador de errores
    contador_errores=0;
    
    for k=1:cant_patrones
        % entrada
        x=patrones(k,1:cant_entradas);
        
        % arma el vector de entradas de la capa de salida
        g=zeros(1,clases+1);
        g(1)=-1;
        
        % funciones gaussianas
        for l=1:clases
            g(l+1)=gaussiana(x,mu(l,:));
        end
        
        % recorre las neuronas de salida
        v=zeros(1,neuronas);
        y=v;
        e=y;
        
        for l=1:neuronas
            % calcula el producto interno
            v(l)=g*pesos(l,:)';
            
            % funcion de activacion
            y(l)=sgn(v(l));
            
            % error
            e=y(l)-yd(k,l);
            
            if abs(e)>0
                contador_errores=contador_errores+1;
            end
        end
    end
    
    % tasa de aciertos
    tacierto=1-(contador_errores/cant_patrones);
    
    % criterios de corte
    % aciertos
    if tacierto>tol
        next=false;
        disp('*************************')
        disp('*** Sale por aciertos ***')
        disp('*************************')
    end
    % epocas
    if epoca>max_epocas
        next=false;
        disp('***********************')
        disp('*** Sale por epocas ***')
        disp('***********************')
    end
    
    epoca=epoca+1;
end

% *** termina etapa de entrenamiento supervisado ***
disp('Termina etapa de entrenamiento supervisado')
disp('------------------------------------------------------')

% ------------------------------------------------------

% *** inicia etapa de pruebas ***
disp('Inicia etapa de pruebas')

% pruebas
% calcula el contador de errores
contador_errores=0;

for k=1:cant_patrones
    % entrada
    x=patrones(k,1:cant_entradas);
    
    % arma el vector de entradas de la capa de salida
    g=zeros(1,clases+1);
    g(1)=-1;
    
    % funciones gaussianas
    for l=1:clases
        g(l+1)=gaussiana(x,mu(l,:));
    end
    
    % recorre las neuronas de salida
    v=zeros(1,neuronas);
    y=v;
    e=y;
    
    for l=1:neuronas
        % calcula el producto interno
        v(l)=g*pesos(l,:)';
        
        % funcion de activacion
        y(l)=sgn(v(l));
        
        % error
        e=y(l)-yd(k,l);
        
        if abs(e)>0
            contador_errores=contador_errores+1;
        end
    end
end

% tasa de aciertos
tacierto=1-(contador_errores/cant_patrones);

disp('+++++++++++++++++++++++')
disp(['Tasa de aciertos para casos de prueba: ',num2str(tacierto*100),'%'])
disp('+++++++++++++++++++++++')


% ------------------------------------------------------