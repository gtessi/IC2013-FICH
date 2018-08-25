clear all
close all
clc
% --------------------------------------------------------------
% Variable para cada bloque
ncant=20;

% Temperatura externa
Tempe=[20*ones(1,ncant) 15*ones(1,ncant) 20*ones(1,ncant) 10*ones(1,ncant) 20*ones(1,ncant) 25*ones(1,ncant)];
%Tempe=2*sin(2*pi*3*n/tiempo)+20;

% Tiempo total
tiempo=length(Tempe);

% Vector de instantes
n=1:tiempo;

% Define la temperatura de referencia
Tempd=2*square(2*pi*3*n/tiempo)+20;

% Vectores con los estados del aire acondicionado y de la estufa
prendioV=zeros(1,n);
prendioC=zeros(1,n);

% Temperatura interna
Tempi=zeros(1,n);

% *** inicia primera prueba ***
display('*** Inicia primera prueba ***')

% Temperatura interna inicial
Tempi(1)=30;

% Calculo de la temperatura interna en el tiempo
for k=2:tiempo
    % Calcula el error entre la temperatura interna y la deseada
    e=Tempi(k-1)-Tempd(k)
    
    % Proceso completo de los conjuntos borrosos que se activaron a partir
    % del valor del error
    regla=codificacion1(e)
    [yj,bj]=composicion1(e,regla)
    [v,c]=defuzzyfication(yj,bj,e)
    
    % Guarda los estados de los artefactos de control
    prendioV(k)=abs(sign(v));
    prendioC(k)=abs(sign(c));
    
    % Calcula la nueva temperatura interna
    Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    
    display('-------------------------------------------------------')
end

% Graficas
% Variacion de temperatura interna
figure;
hold on;
axis square;
title('Variacion de Temperaturas (primera prueba)');
plot(n,Tempe,'r'); % temp externa
plot(n,Tempi,'b'); % temp interna
plot(n,Tempd,'k'); % temp de referencia
legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Location','NorthEastOutside');
% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
title('Variacion de estados de los artefactos controladores (primera prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

pause;

% *** termina primera prueba ***

% --------------------------------------------------------------

% *** inicia segunda prueba ***
display('*** Inicia segunda prueba ***')

% Temperatura interna inicial
Tempi(1)=30;

% Calculo de la temperatura interna en el tiempo
for k=2:tiempo
    % Calcula el error entre la temperatura interna y la deseada
    e=Tempi(k-1)-Tempd(k)
    
    % Proceso completo de los conjuntos borrosos que se activaron a partir
    % del valor del error
    regla=codificacion2(e)
    [yj,bj]=composicion2(e,regla)
    [v,c]=defuzzyfication(yj,bj,e)
    
    % Guarda los estados de los artefactos de control
    prendioV(k)=abs(sign(v));
    prendioC(k)=abs(sign(c));
    
    % Calcula la nueva temperatura interna
    Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    
    display('-------------------------------------------------------')
end

% Graficas
% Variacion de temperatura interna
figure;
hold on;
axis square;
title('Variacion de Temperaturas (segunda prueba)');
plot(n,Tempe,'r'); % temp externa
plot(n,Tempi,'b'); % temp interna
plot(n,Tempd,'k'); % temp de referencia
legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Location','NorthEastOutside');
% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
title('Variacion de estados de los artefactos controladores (segunda prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

pause;

% *** termina segunda prueba ***

% --------------------------------------------------------------

% *** inicia tercera prueba ***
display('*** Inicia tercera prueba ***')

% Temperatura interna inicial
Tempi(1)=30;

% Calculo de la temperatura interna en el tiempo
for k=2:tiempo
    % Calcula el error entre la temperatura interna y la deseada
    e=Tempi(k-1)-Tempd(k)
    
    % Proceso completo de los conjuntos borrosos que se activaron a partir
    % del valor del error
    regla=codificacion3(e)
    [yj,bj]=composicion3(e,regla)
    [v,c]=defuzzyfication(yj,bj,e)
    
    % Guarda los estados de los artefactos de control
    prendioV(k)=abs(sign(v));
    prendioC(k)=abs(sign(c));
    
    % Calcula la nueva temperatura interna
    Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    
    display('-------------------------------------------------------')
end

% Graficas
% Variacion de temperatura interna
figure;
hold on;
axis square;
title('Variacion de Temperaturas (tercera prueba)');
plot(n,Tempe,'r'); % temp externa
plot(n,Tempi,'b'); % temp interna
plot(n,Tempd,'k'); % temp de referencia
legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Location','NorthEastOutside');
% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
title('Variacion de estados de los artefactos controladores (tercera prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

pause;

% *** termina tercera prueba ***

% --------------------------------------------------------------

% *** inicia cuarta prueba ***
display('*** Inicia cuarta prueba ***')

% Temperatura interna inicial
Tempi(1)=30;

% Calculo de la temperatura interna en el tiempo
for k=2:tiempo
    % Calcula el error entre la temperatura interna y la deseada
    e=Tempi(k-1)-Tempd(k)
    
    % Proceso completo de los conjuntos borrosos que se activaron a partir
    % del valor del error
    regla=codificacion4(e)
    [yj,bj]=composicion4(e,regla)
    [v,c]=defuzzyfication(yj,bj,e)
    
    % Guarda los estados de los artefactos de control
    prendioV(k)=abs(sign(v));
    prendioC(k)=abs(sign(c));
    
    % Calcula la nueva temperatura interna
    Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    
    display('-------------------------------------------------------')
end

% Graficas
% Variacion de temperatura interna
figure;
hold on;
axis square;
title('Variacion de Temperaturas (cuarta prueba)');
plot(n,Tempe,'r'); % temp externa
plot(n,Tempi,'b'); % temp interna
plot(n,Tempd,'k'); % temp de referencia
legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Location','NorthEastOutside');
% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
title('Variacion de estados de los artefactos controladores (cuarta prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

% *** termina cuarta prueba ***

% --------------------------------------------------------------

% faltaria el coso sin control pero despues lo vemos

% --------------------------------------------------------------