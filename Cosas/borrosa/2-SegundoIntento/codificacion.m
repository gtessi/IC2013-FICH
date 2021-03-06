%ETAPA: CODIFICACI�N.
%Consiste en determinar que reglas se activar�n
%Los conjuntos borrosos son: [Bajo MedioBajo MedioAlto Alto]

function [reglas] = codificacion(e)
%----------------------------------------------------
%Salida:

%   reglas=reglas activadas, el dato que tiene es el grado de membresia
%Entrada:
    %e= error;
%----------------------------------------------------

%Vector de Reglas:
reglas = [0 0 0 0];

%Verificamos si el error es:
%positivo -> Aire Acondicionado
%negativo -> Calefactor



% Se prende el aire acondicionado
if e>0 && e<=3
    reglas(1)=min(e, min(1,-e+3)); %Bajo        
end
if e>=1.5 && e<=4.5
    reglas(2)=min(e-1.5 ,min(1, -e+4.5));%Medio Bajo
end
if e>=3 && e<=6
    reglas(3)=min(e-3 ,min(1, -e+6)); %Medio Alto
end
if e>=4.5 
    reglas(4)=min(e-4.5, 1); %Alto
end

% Se prende el calefactor

if e<0 && e>=-3
    reglas(1)=min(-e, min(1,e+3)); %Bajo
end
if e<=-1.5 && e>=-4.5
    reglas(2)=min(-e-1.5 ,min(1, e+4.5));%Medio Bajo
end
if e<=-3 && e>=-6
    eglas(3)=min(-e-3 ,min(1, e+6)); %Medio Alto
end
if e<=-4.5
    reglas(4)=min(-e-4.5, 1);% Alto
end

