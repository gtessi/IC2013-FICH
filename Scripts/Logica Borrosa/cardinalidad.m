function card = cardinalidad(cb)
    % ---------------------------------------------------------
    % Cardinalidad de un conjunto borroso
    % ---------------------------------------------------------
    
    n=length(cb);
    
    card=0;
    
    for t=1:n
        card=card+cb(t);
    end
end