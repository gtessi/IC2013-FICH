function reglas = codificacion5(e)
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
    if e>0.75 && e<=4
        reglas(1)=min(e-0.75,min(1,-e+4)); % Bajo        
    end
    if e>=2 && e<=6
        reglas(2)=min(e-2,min(1,-e+6)); % MedioBajo
    end
    if e>=4 && e<=8
        reglas(3)=min(e-4,min(1,-e+8)); % MedioAlto
    end
    if e>=6 && e<=10
        reglas(4)=min(e-6,min(1,-e+10)); % Alto
    end
    
    % Se prende el calefactor
	if e<-0.75 && e>=-4
        reglas(1)=min(-e+0.75,min(1,e+4)); % Bajo        
    end
    if e<=-2 && e>=-6
        reglas(2)=min(-e-2,min(1,e+6)); % MedioBajo
    end
    if e<=-4 && e>=-8
        reglas(3)=min(-e-4,min(1,e+8)); % MedioAlto
    end
    if e<=-6 && e>=-10
        reglas(4)=min(-e-6,min(1,e+10)); % Alto
    end
end