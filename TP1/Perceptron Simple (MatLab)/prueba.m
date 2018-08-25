function salidas = prueba(entradas,w)
    % ------------------------------------------------------
    % Genera un vector de n valores con las salidas del perceptron para
    % cada caso de prueba en las entradas, a partir del vector de pesos w
    % ------------------------------------------------------
    % ENTRADA
    % entradas = matriz con las entradas de las pruebas
    % w = vector de pesos
    % ------------------------------------------------------
    % SALIDA
    % salidas = salidas del perceptron para cada caso de prueba
    % ------------------------------------------------------
    
    % cantidad de casos de prueba n
    n=size(entradas,1);
    
    % define el vector de salidas
    salidas=zeros(n,1);
    
    % recorre los casos de pruebas
    for p=1:n
        % arma la entrada extendida
        x=[-1 entradas(p,:)];
        
        % calcula el producto interno de las entradas con los pesos
        prod_int=x*w;
        
        % obtiene la salida y
        y=sgn(prod_int);
        
        % arma el vector de salidas
        salidas(p)=y;
    end
end