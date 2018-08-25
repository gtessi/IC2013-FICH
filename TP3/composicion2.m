function [Yc,Bj] = composicion2(e,reglas)
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
            centroide=45;
            area=reglas(1)*((30*1/2)*2+30*1);
            
            Yc(1)=centroide;
            Bj(1)=area;
        end
        % MedioBajo
        if reglas(2)~=0
            centroide=90;
            area=reglas(2)*((30*1/2)*2+30*1);
            
            Yc(2)=centroide;
            Bj(2)=area;
        end
        % MedioAlto
        if reglas(3)~=0
            centroide=135;
            area=reglas(3)*((30*1/2)*2+30*1);
            
            Yc(3)=centroide;
            Bj(3)=area;
        end
        % Alto
        if reglas(4)~=0
            centroide=((135+40*2/3)+207.5)/2;
            area=reglas(4)*((30*1/2)+(65*1));
            
            Yc(4)=centroide;
            Bj(4)=area;
        end
    % Calefactor
    else
        % Bajo
        if reglas(1)~=0
            centroide=0.75;
            area=reglas(1)*((30*1/2)*2+30*1);
            
            Yc(1)=centroide;
            Bj(1)=area;
        end
        % MedioBajo
        if reglas(2)~=0
            centroide=1.5;
            area=reglas(2)*((30*1/2)*2+30*1);
            
            Yc(2)=centroide;
            Bj(2)=area;
        end
        % MedioAlto
        if reglas(3)~=0
            centroide=2.25;
            area=reglas(3)*((30*1/2)*2+30*1);
            
            Yc(3)=centroide;
            Bj(3)=area;
        end
        % Alto
        if reglas(4)~=0
            centroide=(0.5*2/3+2.25+3.375)/2;
            area=reglas(4)*((30*1/2)+(65*1));
            
            Yc(4)=centroide;
            Bj(4)=area;
        end
    end
end