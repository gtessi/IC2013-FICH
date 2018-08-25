function d = distancia(v1,v2)
    % ------------------------------------------------------
    % Calcula la distancia euclidea entre dos vectores
    % ------------------------------------------------------
    % ENTRADA
    % v1 = vector 1
    % v2 = vector 2
    % ------------------------------------------------------
    % SALIDA
    % d = distancia
    % ------------------------------------------------------
    
    d=0;
    
    if length(v1)==length(v2)
        for k=1:length(v1)
            d=d+(v1(k)-v2(k)).^2;
        end
    else
        disp('ERROR - Vectores de diferente dimension\n\n')
    end
end