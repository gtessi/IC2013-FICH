function val = random(val_min,val_max)
    % ------------------------------------------------------
    % Genera un numero aleatorio entero entre val_min y val_max
    % ------------------------------------------------------
    % ENTRADA
    % val_min = valor minimo
    % val_max = valor maximo
    % ------------------------------------------------------
    % SALIDA
    % val = valor aleatorio entero
    % ------------------------------------------------------
    
    val=val_min+round((val_max-val_min)*rand());
end