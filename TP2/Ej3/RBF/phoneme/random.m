function val = random(val_min,val_max)
    % ------------------------------------------------------
    % Genera un numero aleatorio entre val_min y val_max
    % ------------------------------------------------------
    % ENTRADA
    % val_min = valor minimo
    % val_max = valor maximo
    % ------------------------------------------------------
    % SALIDA
    % val = valor aleatorio
    % ------------------------------------------------------
    
    val=val_min+(val_max-val_min)*rand(1);
end