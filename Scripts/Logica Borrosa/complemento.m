function cbc = complemento(cb)
    % ---------------------------------------------------------
    % Complemento de un conjunto borroso
    % ---------------------------------------------------------
    
    n=length(cb);
    
    cbc=zeros(1,n);
    
    for t=1:n
        cbc(t)=1-cb(t);
    end
end