function [Yc,Bj] = composicion5(e,reglas)
    % ------------------------------------------------------
    % Composicion
    % Compone todas las reglas que se hayan activado
    % Los conjuntos borrosos son [Bajo MedioBajo MedioAlto Alto]
    % ------------------------------------------------------
    % ENTRADA
    % e = error
    % reglas = vector con las reglas activadas y su grado de membresia
    % ------------------------------------------------------
    % SALIDA
    % Yc = vector con los centroides de cada conjunto
    % Bj = vector con las areas de cada conjunto
    % ------------------------------------------------------
    
    % Para cada regla activada, se calcula el centroide de cada grupo y su
    % area
    Yc=zeros(1,length(reglas));
    Bj=zeros(1,length(reglas));
    
    % Nota: el centroide de un Triangulo Rectangulo es (2/3*b,1/3*h)
    
    % Aire Acondicionado
    if e>0
        % Bajo
        if reglas(1)~=0
            centroide=60;
            area=reglas(1)*(90);
            
            Yc(1)=centroide;
            Bj(1)=area;
        end
        % MedioBajo
        if reglas(2)~=0
            centroide=120;
            area=reglas(2)*(90);
            
            Yc(2)=centroide;
            Bj(2)=area;
        end
        % MedioAlto
        if reglas(3)~=0
            centroide=180;
            area=reglas(3)*(90);
            
            Yc(3)=centroide;
            Bj(3)=area;
        end
        % Alto
        if reglas(4)~=0
            centroide=240;
            area=reglas(4)*90;
            
            Yc(4)=centroide;
            Bj(4)=area;
        end
    % Calefactor
    else
        % Bajo
        if reglas(1)~=0
            centroide=1;
            area=reglas(1)*1.5;
            
            Yc(1)=centroide;
            Bj(1)=area;
        end
        % MedioBajo
        if reglas(2)~=0
            centroide=2;
            area=reglas(2)*1.5;
            
            Yc(2)=centroide;
            Bj(2)=area;
        end
        % MedioAlto
        if reglas(3)~=0
            centroide=3;
            area=reglas(3)*1.5;
            
            Yc(3)=centroide;
            Bj(3)=area;
        end
        % Alto
        if reglas(4)~=0
            centroide=4;
            area=reglas(4)*1.5;
            
            Yc(4)=centroide;
            Bj(4)=area;
        end
    end
end