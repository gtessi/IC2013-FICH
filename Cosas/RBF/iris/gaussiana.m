function val = gaussiana(x,mu)
    % ------------------------------------------------------
    % Calcula el valor de la funcion gaussiana
    % ------------------------------------------------------
    % ENTRADA
    % x = valor
    % mu = media
    % ------------------------------------------------------
    % SALIDA
    % val = valor de la funcion
    % ------------------------------------------------------
    
    sumatoria=0;
    
    for k=1:length(x)
        sumatoria=sumatoria+(x(k)-mu(k))^2;
    end
    
    val=exp(-0.5*sumatoria);
end