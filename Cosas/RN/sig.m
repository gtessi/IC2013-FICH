function y = sig(z)
    alfa=1;
    
    y=(1-exp(-alfa*z))/(1+exp(-alfa*z));
end