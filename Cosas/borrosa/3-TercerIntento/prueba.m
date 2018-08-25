



hold off;
close all;
clear;
clc;

% Variable para cada bloque
ncant=20;

% Temperatura deseada
fuente=20*ones(1,ncant);
fuente=[fuente 15*ones(1,ncant)];
fuente=[fuente 20*ones(1,ncant)];
fuente=[fuente 10*ones(1,ncant)];
fuente=[fuente 20*ones(1,ncant)];
fuente=[fuente 25*ones(1,ncant)];

% Tiempo total
tiempo = length(fuente);

% Vector de instantes
n=1:tiempo;

% Definimos la fuente
Tempd = 2*square(2*pi*3*n/tiempo)+20;


% Temperatura inicial
Temp(1)=30;

c=0;
prendioV=[];
prendioC=[];

for k=2:tiempo
    
    e=Temp(k-1)-Tempd(k)
    
    regla = codificacion(e)
    [yj bj]=composicion(e,regla)
    [v c]=defuzzyfication(yj,bj,e)
    %v=0; c=0;
    
    prendioV = [prendioV, abs(sign(v))];
    prendioC = [prendioC, abs(sign(c))];
    
    Temp(k)=0.912*Temp(k-1) + 0.088*fuente(k) + 0.604*c^2 -0.0121*v ;
    
    display('-------------------------------------------------------')
    
end

figure(1)
plot(n,fuente,'r') % temp externa
hold on
plot(n,Temp) % temp interna
plot(n,Tempd,'k')% temp de referencia

figure(2)
plot(prendioV,'.r');
hold on
plot(prendioC,'.k');