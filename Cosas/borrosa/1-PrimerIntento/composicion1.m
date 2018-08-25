%ETAPA_ Composicion
%Consiste en componer todas auqellas reglas activadas.
%Los conjuntos borrosos son: [Bajo MedioBajo MedioAlto Alto]
function [Yc,Bj] = composicion1(e,regla)
%----------------------------------------------------
%Salida:
%   Yc=centroides de cada conjunto
%   Bj=area de cada conjunto.
%Entrada:
    %e=error
    %reglas=reglas activadas
%----------------------------------------------------

%Para cada regla activada calculamos el centroide de cada grupo y su area:
Yc=zeros(1,length(regla));
Bj=zeros(1,length(regla));

%Nota: El centroide de un Triangulo Rectangulo es (2/3*b , 1/3*h)


if e>0 %Aire Acondicionado
        if regla(1)~=0
            centroide=100*(1/3);
            area=regla(1)*(100*1)/2;

            Yc(1)=centroide;
            Bj(1)=area;
        end
        if regla(2)~=0
            centroide=100;
            area=regla(2)*2*(100*1)/2;

            Yc(2)=centroide;
            Bj(2)=area;
        end
        if regla(3)~=0
            centroide=250;
            area= regla(3)*(2*(100*1)/2)+(100*1);

            Yc(3)=centroide;
            Bj(3)=area;
        end
        if regla(4)~=0
            centroide=((150*(2/3)+300)+475)/2;
            area=regla(4)*((150*1)/2+(50*1));

            Yc(4)=centroide;
            Bj(4)=area;
        end
else %Calefactor
        if regla(1)~=0
            centroide=1*(1/3);
            area=regla(1)*(1*1)/2;

            Yc(1)=centroide;
            Bj(1)=area;
        end
        if regla(2)~=0
            centroide=1;
            area=regla(2)*2*(2*1)/2;

            Yc(2)=centroide;
            Bj(2)=area;
        end
        if regla(3)~=0
            centroide=2.5;
            area=regla(3)*(2*(2*1)/2)+(1*1);

            Yc(3)=centroide;
            Bj(3)=area;
        end
        if regla(4)~=0
            centroide=(1.5*(2/3)+3+4.75)/2;
            area=regla(4)*((1.5*1)/2+(0.5*1));

            Yc(4)=centroide;
            Bj(4)=area;
        end
end