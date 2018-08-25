function cb = interseccion(cb1,cb2)
    % ---------------------------------------------------------
    % Interseccion de conjuntos borrosos
    % ---------------------------------------------------------
    
    n1=length(cb1);
    n2=length(cb2);
    
    cb=zeros(1,n1);
    
    if n1~=n2
        disp('ERROR - Conjuntos de diferente tamaño.')
    else
        for t=1:n1
            cb(t)=min(cb1(t),cb2(t));
        end
    end
end