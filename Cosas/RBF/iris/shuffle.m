function e = shuffle(elemento)
    % ------------------------------------------------------
    % Aleatoriza un vector o matriz por filas
    % ------------------------------------------------------
    % ENTRADA
    % elemento = vector fila o matriz a aleatorizar
    % ------------------------------------------------------
    % SALIDA
    % e = vector fila o matriz aleatorizado
    % ------------------------------------------------------
    
    % verifica si es vector fila o matriz
    if isvector(elemento)~=1
        % matriz
        % cantidad de filas de la matriz
        n=size(elemento,1);
        
        % vector de indices aleatorios
        indices=randperm(n);
        
        % filas de la matriz aleatorizadas
        e=elemento(indices,:);
    else
        % vector
        % cantidad de elementos del vector
        n=length(elemento);
        
        % vector de indices aleatorios
        indices=randperm(n);
        
        % vector aleatorizado
        e=elemento(indices);
    end
end