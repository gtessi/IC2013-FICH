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

% Temperatura interna
Tempi=zeros(1,n);

% Variable de control de la puerta
abierta=0; % si la puerta esta abierta

% Vector con los estados de la puerta
estadoP=zeros(1,n);

% Vectores con los estados del aire acondicionado y de la estufa
prendioV=zeros(1,n);
prendioC=zeros(1,n);

% --------------------------------------------------------------

% *** inicia prueba sin control ***
disp('*** Inicia prueba sin control ***')

% Temperatura interna inicial
Tempi(1)=30;

% Calculo de la temperatura interna en el tiempo
for k=2:tiempo
    % Abre la puerta
    abrir=randomP(15)
    
    % Cada 36 instantes hay que permitir que la puerta se abra otra vez
    if(not(mod(k,15)))
        abierta=0;
    end
    
    % Verifica si la puerta esta cerrada
    if(abrir && not(abierta))
        % Puerta abierta
        % Actualiza la temperatura interna
        Tempi(k)=0.169*Tempi(k-1)+0.831*Tempe(k);
        
        % Guarda el estado de la puerta
        estadoP(k)=1;
        
        % Actualiza el estado de la puerta
        abierta=1;
    else
        % Puerta cerrada
        % Actualiza la temperatura interna
        Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k);
    end
    
    disp('-------------------------------------------------------')
end

% Graficas
% Variacion de temperatura interna
figure;
hold on;
axis square;
title('Variacion de Temperaturas (sin control)');
plot(n,Tempe,'r'); % temp externa
plot(n,Tempi,'b'); % temp interna
plot(n,Tempd,'k'); % temp de referencia

for k=1:length(estadoP)
    if estadoP(k)==1
        estadoP(k)=Tempi(k);
        plot(k,estadoP(k),'s','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',10);
    end
end

legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Puerta loca','Location','NorthEastOutside');

% *** termina prueba sin control ***
disp('*** Termina prueba sin control ***')

pause;

% --------------------------------------------------------------

% *** inicia primera prueba ***
disp('*** Inicia primera prueba ***')

% Estado inicial de la puerta
abierta=0;
estadoP=zeros(1,n);

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
    
    % Abre la puerta
    abrir=randomP(15)
    
    % Cada 360 instantes hay que permitir que la puerta se abra otra vez
    if(not(mod(k,15)))
        abierta=0;
    end
    
    % Verifica si la puerta esta cerrada
    if(abrir && not(abierta))
        % Puerta abierta
        % Actualiza la temperatura interna
        Tempi(k)=0.169*Tempi(k-1)+0.831*Tempe(k)+0.112*c^2-0.002*v;
        
        % Guarda el estado de la puerta
        estadoP(k)=1;
        
        % Actualiza el estado de la puerta
        abierta=1;
    else
        % Puerta cerrada
        % Actualiza la temperatura interna
        Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    end
    
    disp('-------------------------------------------------------')
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

for k=1:length(estadoP)
    if estadoP(k)==1
        estadoP(k)=Tempi(k);
        plot(k,estadoP(k),'s','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',10);
    end
end

legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Puerta loca','Location','NorthEastOutside');

% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
axis([0 length(n) -0.5 1.5]);
title('Variacion de estados de los artefactos controladores (primera prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

% *** termina primera prueba ***
disp('*** Termina primera prueba ***')

pause;

% --------------------------------------------------------------

% *** inicia segunda prueba ***
disp('*** Inicia segunda prueba ***')

% Estado inicial de la puerta
abierta=0;
estadoP=zeros(1,n);

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
    
    % Abre la puerta
    abrir=randomP(15)
    
    % Cada 360 instantes hay que permitir que la puerta se abra otra vez
    if(not(mod(k,15)))
        abierta=0;
    end
    
    % Verifica si la puerta esta cerrada
    if(abrir && not(abierta))
        % Puerta abierta
        % Actualiza la temperatura interna
        Tempi(k)=0.169*Tempi(k-1)+0.831*Tempe(k)+0.112*c^2-0.002*v;
        
        % Guarda el estado de la puerta
        estadoP(k)=1;
        
        % Actualiza el estado de la puerta
        abierta=1;
    else
        % Puerta cerrada
        % Actualiza la temperatura interna
        Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    end
    
    disp('-------------------------------------------------------')
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

for k=1:length(estadoP)
    if estadoP(k)==1
        estadoP(k)=Tempi(k);
        plot(k,estadoP(k),'s','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',10);
    end
end

legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Puerta loca','Location','NorthEastOutside');

% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
axis([0 length(n) -0.5 1.5]);
title('Variacion de estados de los artefactos controladores (segunda prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

% *** termina segunda prueba ***
disp('*** Termina segunda prueba ***')

pause;

% --------------------------------------------------------------

% *** inicia tercera prueba ***
disp('*** Inicia tercera prueba ***')

% Estado inicial de la puerta
abierta=0;
estadoP=zeros(1,n);

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
    
    % Abre la puerta
    abrir=randomP(15)
    
    % Cada 360 instantes hay que permitir que la puerta se abra otra vez
    if(not(mod(k,15)))
        abierta=0;
    end
    
    % Verifica si la puerta esta cerrada
    if(abrir && not(abierta))
        % Puerta abierta
        % Actualiza la temperatura interna
        Tempi(k)=0.169*Tempi(k-1)+0.831*Tempe(k)+0.112*c^2-0.002*v;
        
        % Guarda el estado de la puerta
        estadoP(k)=1;
        
        % Actualiza el estado de la puerta
        abierta=1;
    else
        % Puerta cerrada
        % Actualiza la temperatura interna
        Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    end
    
    disp('-------------------------------------------------------')
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

for k=1:length(estadoP)
    if estadoP(k)==1
        estadoP(k)=Tempi(k);
        plot(k,estadoP(k),'s','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',10);
    end
end

legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Puerta loca','Location','NorthEastOutside');

% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
axis([0 length(n) -0.5 1.5]);
title('Variacion de estados de los artefactos controladores (tercera prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

% *** termina tercera prueba ***
disp('*** Termina tercera prueba ***')

pause;

% --------------------------------------------------------------

% *** inicia cuarta prueba ***
disp('*** Inicia cuarta prueba ***')

% Estado inicial de la puerta
abierta=0;
estadoP=zeros(1,n);

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
    
    % Abre la puerta
    abrir=randomP(15)
    
    % Cada 360 instantes hay que permitir que la puerta se abra otra vez
    if(not(mod(k,15)))
        abierta=0;
    end
    
    % Verifica si la puerta esta cerrada
    if(abrir && not(abierta))
        % Puerta abierta
        % Actualiza la temperatura interna
        Tempi(k)=0.169*Tempi(k-1)+0.831*Tempe(k)+0.112*c^2-0.002*v;
        
        % Guarda el estado de la puerta
        estadoP(k)=1;
        
        % Actualiza el estado de la puerta
        abierta=1;
    else
        % Puerta cerrada
        % Actualiza la temperatura interna
        Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    end
    
    disp('-------------------------------------------------------')
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

for k=1:length(estadoP)
    if estadoP(k)==1
        estadoP(k)=Tempi(k);
        plot(k,estadoP(k),'s','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',10);
    end
end

legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Puerta loca','Location','NorthEastOutside');

% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
axis([0 length(n) -0.5 1.5]);
title('Variacion de estados de los artefactos controladores (cuarta prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

% *** termina cuarta prueba ***
disp('*** Termina cuarta prueba ***')

pause;

% --------------------------------------------------------------

% *** inicia quinta prueba ***
disp('*** Inicia quinta prueba ***')

% Estado inicial de la puerta
abierta=0;
estadoP=zeros(1,n);

% Temperatura interna inicial
Tempi(1)=30;

% Calculo de la temperatura interna en el tiempo
for k=2:tiempo
    % Calcula el error entre la temperatura interna y la deseada
    e=Tempi(k-1)-Tempd(k)
    
    % Proceso completo de los conjuntos borrosos que se activaron a partir
    % del valor del error
    regla=codificacion5(e)
    [yj,bj]=composicion5(e,regla)
    [v,c]=defuzzyfication(yj,bj,e)
    
    % Guarda los estados de los artefactos de control
    prendioV(k)=abs(sign(v));
    prendioC(k)=abs(sign(c));
    
    % Abre la puerta
    abrir=randomP(15)
    
    % Cada 360 instantes hay que permitir que la puerta se abra otra vez
    if(not(mod(k,15)))
        abierta=0;
    end
    
    % Verifica si la puerta esta cerrada
    if(abrir && not(abierta))
        % Puerta abierta
        % Actualiza la temperatura interna
        Tempi(k)=0.169*Tempi(k-1)+0.831*Tempe(k)+0.112*c^2-0.002*v;
        
        % Guarda el estado de la puerta
        estadoP(k)=1;
        
        % Actualiza el estado de la puerta
        abierta=1;
    else
        % Puerta cerrada
        % Actualiza la temperatura interna
        Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    end
    
    disp('-------------------------------------------------------')
end

% Graficas
% Variacion de temperatura interna
figure;
hold on;
axis square;
title('Variacion de Temperaturas (quinta prueba)');
plot(n,Tempe,'r'); % temp externa
plot(n,Tempi,'b'); % temp interna
plot(n,Tempd,'k'); % temp de referencia

for k=1:length(estadoP)
    if estadoP(k)==1
        estadoP(k)=Tempi(k);
        plot(k,estadoP(k),'s','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',10);
    end
end

legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Puerta loca','Location','NorthEastOutside');

% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
axis([0 length(n) -0.5 1.5]);
title('Variacion de estados de los artefactos controladores (quinta prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

% *** termina quinta prueba ***
disp('*** Termina quinta prueba ***')

pause;

% --------------------------------------------------------------

% *** inicia sexta prueba ***
disp('*** Inicia sexta prueba ***')

% Estado inicial de la puerta
abierta=0;
estadoP=zeros(1,n);

% Temperatura interna inicial
Tempi(1)=30;

% Calculo de la temperatura interna en el tiempo
for k=2:tiempo
    % Calcula el error entre la temperatura interna y la deseada
    e=Tempi(k-1)-Tempd(k)
    
    % Proceso completo de los conjuntos borrosos que se activaron a partir
    % del valor del error
    regla=codificacion6(e)
    [yj,bj]=composicion6(e,regla)
    [v,c]=defuzzyfication(yj,bj,e)
    
    % Guarda los estados de los artefactos de control
    prendioV(k)=abs(sign(v));
    prendioC(k)=abs(sign(c));
    
    % Abre la puerta
    abrir=randomP(15)
    
    % Cada 360 instantes hay que permitir que la puerta se abra otra vez
    if(not(mod(k,15)))
        abierta=0;
    end
    
    % Verifica si la puerta esta cerrada
    if(abrir && not(abierta))
        % Puerta abierta
        % Actualiza la temperatura interna
        Tempi(k)=0.169*Tempi(k-1)+0.831*Tempe(k)+0.112*c^2-0.002*v;
        
        % Guarda el estado de la puerta
        estadoP(k)=1;
        
        % Actualiza el estado de la puerta
        abierta=1;
    else
        % Puerta cerrada
        % Actualiza la temperatura interna
        Tempi(k)=0.912*Tempi(k-1)+0.088*Tempe(k)+0.604*c^2-0.0121*v;
    end
    
    disp('-------------------------------------------------------')
end

% Graficas
% Variacion de temperatura interna
figure;
hold on;
axis square;
title('Variacion de Temperaturas (sexta prueba)');
plot(n,Tempe,'r'); % temp externa
plot(n,Tempi,'b'); % temp interna
plot(n,Tempd,'k'); % temp de referencia

for k=1:length(estadoP)
    if estadoP(k)==1
        estadoP(k)=Tempi(k);
        plot(k,estadoP(k),'s','MarkerEdgeColor','k','MarkerFaceColor','g','MarkerSize',10);
    end
end

legend('Temp. Externa','Temp. Interna','Temp. de Referencia','Puerta loca','Location','NorthEastOutside');

% Activacion  y desactivacion del calefactor y del aire acondicionado
figure;
hold on;
axis square;
axis([0 length(n) -0.5 1.5]);
title('Variacion de estados de los artefactos controladores (sexta prueba)');
plot(prendioV,'.b'); % estados aire acondicionado
plot(prendioC,'.r'); % estados calefactor
legend('A. Acond.','Calefactor','Location','NorthEastOutside');

% *** termina sexta prueba ***
disp('*** Termina sexta prueba ***')

% --------------------------------------------------------------