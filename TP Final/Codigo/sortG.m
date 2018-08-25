function m = sortG(m,col,crit)
    % ------------------------------------------------------
    % Ordena una columna de la matriz segun una columna como criterio
    % ------------------------------------------------------
    % ENTRADA
    % m = matriz a ordenar
    % col = columna a ordenar
    % crit = columna como criterio
    % ------------------------------------------------------
    % SALIDA
    % m = matriz ordenada
    % ------------------------------------------------------
    
    % verifica cuantos argumentos se pasaron
    if nargin==3
        % ordena segun columna con criterio
        for k=1:size(m,1)-1
            for l=k+1:size(m,1)
                % ordena la columna col en forma ascendente
                if m(k,col)>m(l,col)
                    aux=m(k,:);
                    m(k,:)=m(l,:);
                    m(l,:)=aux;
                end
                % ordena la columna crit en forma ascendente
                if m(k,crit)>m(l,crit) && m(k,col)==m(l,col)
                    aux=m(k,:);
                    m(k,:)=m(l,:);
                    m(l,:)=aux;
                end
            end
        end
    else
        % ordena segun columna col
        for k=1:size(m,1)-1
            for l=k+1:size(m,1)
                if m(k,col)>m(l,col)
                    aux=m(k,:);
                    m(k,:)=m(l,:);
                    m(l,:)=aux;
                end
            end
        end
    end
end