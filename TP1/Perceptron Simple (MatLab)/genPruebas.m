function entradas = genPruebas(nom_archi,n)
    % ------------------------------------------------------
    % Genera un archivo con n valores de pruebas, creados a partir de los
    % datos en el archivo nom_archi.csv
    % ------------------------------------------------------
    % ENTRADA
    % nom_archi = nombre del archivo .csv con el formato base
    % n = cantidad de casos
    % ------------------------------------------------------
    % SALIDA
    % entradas = valores de entrada
    % ------------------------------------------------------
    
    % carga el archivo en la matriz casos
    casos=csvread(nom_archi);
    
    % cantidad de valores en cada fila
    cant_valores=size(casos,2);
    
    % cantidad de entradas
    cant_entradas=cant_valores-1;
    
    % cantidad de casos base
    cant_casos=size(casos,1);
    
    % define la matriz con los casos aleatorios 
    casos_nuevos=zeros(n,cant_entradas);
    
    % calcula la cantidad de casos que entran en n
    cociente=fix(n/cant_casos);
    
    % crea n ejemplos a partir de la matriz casos con variaciones entre
    % -0.5 y 0.5
    contador=1;
    for k=1:cociente
        for l=1:cant_casos
            % genera un vector de cant_entradas valores aleatorios
            valores=genVectorAleatorio(cant_entradas,-0.05,0.05);
            
            % genera los casos (entradas)
            casos_nuevos(contador,1:cant_entradas)=casos(l,1:cant_entradas)+valores;
            
            % incrementa el contador
            contador=contador+1;
        end
    end
    
    % agrega los casos restantes para obtener n ejemplos
    if contador~=n
        for k=contador:n
            % genera un vector de cant_entradas valores aleatorios
            valores=genVectorAleatorio(cant_entradas,-0.05,0.05);
            
            % genera los casos (entradas)
            casos_nuevos(k,1:cant_entradas)=casos(k-contador+1,1:cant_entradas)+valores;
        end
    end
    
    % aleatoriza la matriz con los datos
    casos_nuevos=shuffle(casos_nuevos);
    
    % guarda los datos en un archivo
    csvwrite(['pruebas_' nom_archi],casos_nuevos);
    
    % separa las entradas y las salidas
    entradas=casos_nuevos;
end