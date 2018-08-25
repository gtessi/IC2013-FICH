function val = randomP(prob)
    % ------------------------------------------------------
    % Genera un numero aleatorio entero
    % ------------------------------------------------------
    % ENTRADA
    % prob = probabilidad del valor
    % ------------------------------------------------------
    % SALIDA
    % val = valor aleatorio entero
    % ------------------------------------------------------
    
    val=sign(rand()-1/prob)-1;
end