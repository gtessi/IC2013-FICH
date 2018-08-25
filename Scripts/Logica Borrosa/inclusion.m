function val = inclusion(cb1,cb2)
    % ---------------------------------------------------------
    % Inclusion de conjuntos borrosos
    % ---------------------------------------------------------
    
    n1=length(cb1);
    n2=length(cb2);
    
    val=true;
    
    if n1~=n2
        disp('ERROR - Conjuntos de diferente tamaño.')
    else
        c=1;
        while c<=n1
            if cb1(c)>cb2(c)
                val=false;
            end
            c=c+1;
        end
    end
end