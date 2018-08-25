function [idx_clases,reasignaciones] = actualizarPatrones(patrones,idx_clases,mu)
    % ------------------------------------------------------
    % Actualiza la clase asociada de cada patron segun su centroide mas
    % cercano
    % ------------------------------------------------------
    % ENTRADA
    % patrones = conjunto de datos
    % idx_clases = vector con los indices y clases asociadas de cada patron
    % mu = centroides de la iteracion anterior
    % ------------------------------------------------------
    % SALIDA
    % idx_clases = vector actualizado con los indices y clases asociadas de
    % cada patron
    % reasignaciones = variable de control de reasignaciones
    % ------------------------------------------------------
    
    % cantidad de patrones
    cant_patrones=size(patrones,1);
    
    % cantidad de entradas
    cant_entradas=size(patrones,2)-1;
    
    % cantidad de clases
    cant_clases=size(mu,1);
    
    % reasignaciones efectuadas
    reasignaciones=0;
    
    % recorre los patrones
    for k=1:cant_patrones
        % indice del patron
        idx=idx_clases(k,1);
        
        % clase del patron
        clase=idx_clases(k,2);
        
        % calcula la distancia entre patron-centroide asociado
        dist_pat_clase=distancia(patrones(idx,1:cant_entradas),mu(clase,:));
        
        % recorre los centroides
        for l=1:cant_clases
            % verifica que la clase del patron no sea la misma que la del
            % centroide
            if l~=idx_clases(k,2);
                % calcula la distancia entre distancia patron-nuevo centroide
                dist_pat_cent=distancia(patrones(idx,1:cant_entradas),mu(l,:));
                
                % compara las distancias
                if dist_pat_cent<dist_pat_clase
                    % actualiza la clase del patron
                    idx_clases(k,2)=l;
                    
                    % actualiza el contador de reasignaciones
                    reasignaciones=reasignaciones+1;
                end
            end
        end
    end
end