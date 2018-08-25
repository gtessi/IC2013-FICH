function w = entrenamiento(entradas,salidas,epocas,error,nu)
    % ------------------------------------------------------
    % Genera un vector de n+1 pesos, ajustado a partir de los ejemplos en
    % la matriz entradas y en el vector salidas, en epocas y con una tasa
    % de aprendizaje nu
    % ------------------------------------------------------
    % ENTRADA
    % entradas = matriz con las entradas de los ejemplos
    % salidas = vector con los resultados deseados de los ejemplos
    % epocas = cantidad de epocas de entrenamiento
    % error = error aceptado
    % nu = tasa de aprendizaje nu
    % ------------------------------------------------------
    % SALIDA
    % w = vector de pesos
    % ------------------------------------------------------
    
    % tolerancia
    tol=1e-10;
    
    % cantidad de ejemplos n
    n=size(entradas,1);
    
    % cantidad de entradas
    cant_entradas=size(entradas,2);
    
    % genera un vector de n+1 (bias) pesos aleatorios entre -0.5 y 0.5
    w=genVectorAleatorio(cant_entradas+1,-0.5,0.5)';
    
    % grafica los puntos
    figure;
    hold on;
    axis([-2,2,-2,2]);
    grid on;
    xlabel('x1');
    ylabel('x2');
    
    for k=1:n
        if salidas(k)==1
            % azul o circulo
            plot(entradas(k,1),entradas(k,2),'b.');
        else
            % rojo o cruz
            plot(entradas(k,1),entradas(k,2),'rx');
        end
    end
    
    pause on;
    
    % recorre las epocas
    e=1;    
    siguiente=true;
    while siguiente
        % recorre los ejemplos
        for k=1:n
            % grafica la recta de pesos
            %plot(w(1)/w(3),-w(2)*entradas(eje,1)/w(3),'k','LineWidth',2);
            %line([0 -w(2)*entradas(k,1)/w(3)],[w(1)/w(3) 0]);
            
            % arma la entrada extendida
            x=[-1 entradas(k,:)];
            
            % calcula el producto interno de las entradas con los pesos
            prod_int=x*w;
            
            % obtiene la salida y
            y=sgn(prod_int);
            
            % calcula el error
            error=salidas(k)-y;
            
            % se adaptan los pesos con el metodo del gradiente
            w=w+2*nu*error.*x';
            
            %pause(0.01)
        end
        
        % calcula el contador de errores
        contador_errores=0;
        
        for k=1:n
            % arma la entrada extendida
            x=[-1 entradas(k,:)];
            
            % calcula el producto interno de las entradas con los pesos
            prod_int=x*w;
            
            % obtiene la salida y
            y=sgn(prod_int);
            
            % calcula el error
            error=salidas(k)-y;
            
            if abs(error)>0
                contador_errores=contador_errores+1;
            end
        end
        
        % tasa de aciertos
        tacierto=1-contador_errores/n;
        
        % sale por errores
        if tacierto<error
            siguiente=false;
        end
        
        % sale por epocas
        if e>epocas
            siguiente=false;
        end
        
        e=e+1;
    end
end