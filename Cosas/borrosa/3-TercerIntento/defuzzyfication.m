%ETAPA: Defuzzyfication
%Consiste en "decodificar" la salida borrosa en un valor real, conocido.
function [ v c ] = defuzzyfication( Yj ,Bj ,e)
%----------------------------------------------------
%Salida:
%   y = salida real
%Entrada:
%   Yj = centroides
%   Bj = areas;

%----------------------------------------------------
%y = numerador / denominador; 
%    numerador= suma( Yj * Bj)
%    denominador = suma(Bj)
numerador=0;
denominador=0;

for i=1:length(Bj)
    numerador=numerador+(Yj(i)*Bj(i));
    denominador=denominador+Bj(i);
end

if(denominador==0)
    v=0;
    c=0;
    return;
end

if(e>0)
    v=numerador/denominador;
    c=0;
    return;
end

v=0;
c=numerador/denominador;

end

