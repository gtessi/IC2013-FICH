function v = genVectorAleatorio(n,val_min,val_max)
    % ------------------------------------------------------
    % Genera un vector de dimension n con valores aleatorios entre val_min
    % y val_max
    % ------------------------------------------------------
    % ENTRADA
    % n = dimension del vector
    % val_min = valor minimo
    % val_max = valor maximo
    % ------------------------------------------------------
    % SALIDA
    % v = vector de valores aleatorios
    % ------------------------------------------------------
    
    % declara el vector v de dimension n
    v=zeros(1,n);
    
    for k=1:n
        v(k)=random(val_min,val_max);
    end
end