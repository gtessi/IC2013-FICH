function w = generarPesos(cantidad,disp)
    % ------------------------------------------------------
    % Genera un vector de pesos
    % ------------------------------------------------------
    % ENTRADA
    % cantidad = cantidad de valores del vector
    % disp = dispersion de los valores aleatorios
    % ------------------------------------------------------
    % SALIDA
    % w = vector de pesos
    % ------------------------------------------------------
    
    w=zeros(1,cantidad);
    
    for k=1:cantidad
        w(k)=random(-disp,disp);
    end
end