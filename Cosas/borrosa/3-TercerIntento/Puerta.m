

clear;
clc;

% Vector de instantes
n=1:3600;

% Definimos la fuente
fuente = 2*sin(2*pi*n/3600)+20;

% Inicializamos la temperatura del cuarto
Temp(1)=20;

% Variables auxiliares
    % Abre la puerta ?
    abrir = 0;
    
    % Abrió?
    abrio = 0;

for k=2:3600
    
    % Abrimos la puertita
    abrir = randomP(360)
    
    % Cada 360 instantes hay que permitir que la puertita se abra otra vez
    if(not(mod(k,360)))
        abrio=0;
    end
    
    % Verificamos si alguien abrió la puerta
    if(abrir && not(abrio))
        Temp(k)=0.169*Temp(k-1) + 0.831*fuente(k);
        abrio=1;
    else
        Temp(k)=0.942*Temp(k-1) + 0.088*fuente(k);
        
    end
    
end


plot(n,Temp)

