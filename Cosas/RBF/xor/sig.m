function v = sig(z)
    % ------------------------------------------------------
    % Funcion sigmoide
    % ------------------------------------------------------
    % ENTRADA
    % z = valor real del dominio
    % ------------------------------------------------------
    % SALIDA
    % v = valor de la funcion
    % ------------------------------------------------------
    
    alfa=10;
    
    v=2/(1+exp(-alfa*z))-1;
end