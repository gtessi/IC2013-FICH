clear all
close all
clc
% --------------------------------------------------------------

% habitacion de 3x2x2 m
% paredes de 15 cm

% apertura maxima: 10 s

% fuentes
% 1. calor aportado desde el exterior a traves de las paredes
% 2. corriente que circula por la resistencia calefactora
% 3. tension aplicada al sistema de refrigeracion
% 4. calor que ingresa al abrir la puerta

% flujos de calor
% q1(t) = K1*(phie(t)-phii(t)) calor aportado desde el exterior
% K1 = lambda*A/E

% lambda = 0.84 W/mºC conductividad termica del ladrillo
% A = 26 m2 el area es la de las 4 paredes + techo (piso adiabatico)
% A = (3*2)*2 + (2*2)*2 + 3*2 = 26 m2
% E = 0.15 m espesor de las paredes

% K1 = 145.6 W/ºC = 0.1456 kW/ºC

% q2(t)=K2*i^2(t) kW = R*i^2(t) calor aportado por la resistencia
% i(t) = corriente
% R = 1000 ohms resistencia => K2 = 1 kohms (i esta en amperes)

% q3(t) = K3*v(t) calor aportado por el acondicionador
% v(t) = tension

% K3 = -0.02 kW/V define cantidad de calor que se "elimina" por cada volt

% q4(t) = a(t)*K4*(phie(t)-phii(t)) calor generado por el intercambiado con
% el medio debido a la puerta

% K4 >> K1, similar al intercambio de las paredes solo que K4 es mucho
% mayor que K1
% como hay una menor resistencia al paso de calor, K4 = 50*K1

% la apertura de la puerta se modela con elfactor aleatorio a(t), que vale
% 1 cuando la puerta esta abierta y 0 cuando esta cerrada
% la puerta se abre una vez por hora y permanece abierta por 10 s

% ecuacion diferencial final
% C*dphii(t)/dt = (K1+K4*a(t))*(phie(t)-phii(t))+K2*i^2(t)+K3*v(t)

% --------------------------------------------------------------
% datos
% periodo (segundos)
T=10;

% frecuencia de muestreo
fm=1/T;

% tiempo (segundos)
tini=0;
tfin=5*3600;

% muestras
n=tini:fm:(tfin-1);

% cantidad de muestras
cant_n=length(n);

% estados iniciales
% temperatura interna
temp_interna=zeros(1,cant_n);
temp_interna(1)=10;

% temperatura externa, oscila entre un rango de valores
temp_externa=20+5*sin(2*pi*3*n/tfin+pi); % hacer un vector con temperaturas oscilantes, puede ser una senoidal o una triangulo

% temperatura de referencia, iniciada en 20 ºC
% varia entre 18 y 22 ºC cada 60 muestras
temp_referencia=20+2*square(2*pi*3*n/tfin+pi); % *** controlar que varie cada 60 muestras

figure;
hold on;
plot(n,temp_referencia,':r');

% elige si es con controlador o sin controlador
opcion=0; % sin controlador
%opcion=1; % con controlador

% *** calcula sin y con el controlador
if opcion==0
    % *** sin controlador
    % comienza a iterar
    for k=2:cant_n
        % calcula la probabilidad de apertura de la puerta
        %a=random(0,360);
        a=random(0,36);
        %a=random(0,6);
        
        % calcula la temperatura interna
        if a==5
            % puerta abierta
            temp_interna(k)=0.169*temp_interna(k-1)+0.831*temp_externa(k);
            %temp_interna(k)=0;
        else
            % puerta cerrada
            temp_interna(k)=0.912*temp_interna(k-1)+0.088*temp_externa(k);
        end
    end
else
    % *** con controlador
    % comienza a iterar
    for k=2:cant_n
        % calcula la probabilidad de apertura de la puerta
        a=random(0,360);
        %a=random(0,36);
        
        % --- fuzzyficacion
        % calcula el error (entrada)
        % error = temperatura de referencia - temperatura actual
        e=temp_referencia(k-1)-temp_interna(k-1);
        
        % aca tiene que ver que conjuntos se activan, a partir del valor e
        % y en que escala
        
        % --- codificacion
        % aca hay que discretizar los conjuntos de entrada
        % para e < 0
        % muy frio, frio, templado
        % para e > 0
        % templado, caliente, muy caliente
        
        % se pueden utilizar reglas compuestas, ver bien eso para poder
        % activar mas conjuntos de salida a partir de una entrada
        
        
        % *** aca calcula las contribuciones de los conjuntos borrosos
        % segun si el error es positivo (aire acondicionado) o negativo
        % (estufa)
        % ver el tema del mapeo
        
        % c == corriente
        % v == tension
        
        % calcula la temperatura interna
        if a==5
            % puerta abierta
            temp_interna(k)=0.169*temp_interna(k-1)+0.831*temp_externa(k)+0.112*c.^2-0.002*v;
        else
            % puerta cerrada
            temp_interna(k)=0.912*temp_interna(k-1)+0.088*temp_externa(k)+0.604*c.^2-0.0121*v;
        end
    end
end

plot(n,temp_interna,'b');
%plot(n,temp_externa,'-k');

% --------------------------------------------------------------