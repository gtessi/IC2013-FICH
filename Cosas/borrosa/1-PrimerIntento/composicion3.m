%ETAPA_ Composicion
%Consiste en componer todas auqellas reglas activadas.
%Los conjuntos borrosos son: [Bajo MedioBajo MedioAlto Alto]
function [ yc Bj ] = composicion3(e, regla)
%----------------------------------------------------
%Salida:
%   yc = centroides de cada conjunto
%   Bj = area de cada conjunto.
%Entrada:
    %e = error
    %reglas = reglas activadas
%----------------------------------------------------

%Para cada regla activada calculamos el centroide de cada grupo y su area:
yc=zeros(1,length(regla));
Bj=zeros(1,length(regla));

%Nota: El centroide de un Triangulo Rectangulo es (2/3*b , 1/3*h)


if e>0 %Aire Acondicionado
        if regla(1)~=0
            centroide= 45;
            area= regla(1)*((30*1/2)*2+30*1);

            yc(1) = centroide;
            Bj(1) = area;
        end
        if regla(2)~=0
            centroide= 90;
            area= regla(2)*((30*1/2)*2+30*1);

            yc(2) = centroide;
            Bj(2) = area;
        end
        if regla(3)~=0
            centroide= 135;
            area= regla(3)*((30*1/2)*2+30*1);

            yc(3) = centroide;
            Bj(3) = area;
        end
        if regla(4)~=0
            centroide= ((135+40*2/3)+207.5)/2;
            area= regla(4)*((30*1/2)+(65*1));

            yc(4) = centroide;
            Bj(4) = area;
        end
else %Calefactor
        if regla(1)~=0
            centroide= 0.75;
            area= regla(1)*((30*1/2)*2+30*1);

            yc(1) = centroide;
            Bj(1) = area;
        end
        if regla(2)~=0
            centroide= 1.5;
            area= regla(2)*((30*1/2)*2+30*1);

            yc(2) = centroide;
            Bj(2) = area;
        end
        if regla(3)~=0
            centroide= 2.25;
            area= regla(3)*((30*1/2)*2+30*1);

            yc(3) = centroide;
            Bj(3) = area;
        end
        if regla(4)~=0
            centroide= (0.5*2/3+2.25+3.375)/2;
            area= regla(4)*((30*1/2)+(65*1));

            yc(4) = centroide;
            Bj(4) = area;
        end
end
