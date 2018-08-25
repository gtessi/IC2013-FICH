function reglas = codificacion4(e)
    % ------------------------------------------------------
    % Codificacion
    % Determina que reglas se activan y el conjunto borroso correspondiente
    % Los conjuntos borrosos son [Bajo MedioBajo MedioAlto Alto]
    % ------------------------------------------------------
    % ENTRADA
    % e = error
    % ------------------------------------------------------
    % SALIDA
    % reglas = vector con las reglas activadas y su grado de membresia
    % ------------------------------------------------------
    
    % Vector de Reglas:
    reglas=[0 0 0 0];
    
    % Verifica si el error es:
    % positivo -> Aire Acondicionado
    % negativo -> Calefactor
    
    % Se prende el aire acondicionado
    if e>0.75 && e<=3
        reglas(1)=min(4*e-3,min(1,-e+3)); % Bajo        
    end
    if e>=1.5 && e<=4.50
        reglas(2)=min(e-1.5,min(1,-e+4.5)); % MedioBajo
    end
    if e>=3 && e<=6
        reglas(3)=min(e-3,min(1,-e+6)); % MedioAlto
    end
    if e>=4.5 
        reglas(4)=min(e-4.5,1); % Alto
    end
    
    % Se prende el calefactor
    if e<-0.75 && e>=-3
        reglas(1)=min(-4*e-3,min(1,e+3)); % Bajo
    end
    if e<=-1.5 && e>=-4.5
        reglas(2)=min(-e-1.5,min(1,e+4.5)); % MedioBajo
    end
    if e<=-3 && e>=-6
        reglas(3)=min(-e-3,min(1,e+6)); % MedioAlto
    end
    if e<=-4.5
        reglas(4)=min(-e-4.5,1); % Alto
    end
end