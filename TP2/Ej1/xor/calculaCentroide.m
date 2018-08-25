function centroide = calculaCentroide(patrones,idx_clases,clase)
    % ------------------------------------------------------
    % Calcula el centroide de un conjunto de patrones a partir de un vector
    % de indices y clases asociadas, para una clase determinada
    % ------------------------------------------------------
    % ENTRADA
    % patrones = conjunto de datos
    % idx_clases = vector con los indices y clases asociadas de cada patron
    % clase = clase a considerar
    % ------------------------------------------------------
    % SALIDA
    % centroide = valor promedio del conjunto de patrones de la clase
    % ------------------------------------------------------
    
    % cantidad de patrones
    cant_patrones=size(patrones,1);
    
    % cantidad de entradas
    cant_entradas=size(patrones,2)-1;
    
    % define el centroide
    centroide=zeros(1,cant_entradas);
    
    % variables temporales para el promedio
    suma=centroide;
    reasignaciones=0;
    
    % recorre los patrones
    for k=1:cant_patrones
        % si el patron corresponde a la clase a considerar, lo acumula
        if idx_clases(k,2)==clase
            suma=suma+patrones(idx_clases(k,1),1:cant_entradas);
            reasignaciones=reasignaciones+1;
        end
    end
    
    % verifica si la division es por cero
    if reasignaciones~=0
        % calcula el promedio de los patrones acumulados
        centroide=suma/reasignaciones;
    end
end