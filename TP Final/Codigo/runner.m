clear all
close all
clc
% ----------------------------------------------------------------------
% runner que corre todas las etapas del compositor automatico

% nombre del archivo midi a leer
nom1='jesu';
nom2='testout';
nom3='testout3';

% cantidad de archivos a considerar
opcion=1;

% agrega notas aleatorias
aleatoria=0;
cant_aleatoria=3;

% mezcla las ventanas
mezclar=0;

% --- preprocessor ---
disp('--- COMIENZA ETAPA DE PRE PROCESO ---')

% controla la cantidad de archivos a concatenar
switch opcion
    case 1
        nxv=preprocessor(nom1);
        
        % cantidad maxima de notas por ventana
        cant_max=size(nxv,2);
    case 2
        nxv1=preprocessor(nom1);
        nxv2=preprocessor(nom2);
        
        % calcula la cantidad de notas por ventana de cada archivo
        cant_notas1=size(nxv1,2);
        cant_notas2=size(nxv2,2);
        
        % cantidad maxima de notas por ventana
        cant_max=max([cant_notas1 cant_notas2]);
        
        % normaliza la cantidad de notas por ventana
        nxv1=[nxv1 zeros(size(nxv1,1),cant_max-cant_notas1)];
        nxv2=[nxv2 zeros(size(nxv2,1),cant_max-cant_notas2)];
        
        % concatena las matrices
        nxv=[nxv1; nxv2];
    case 3
        nxv1=preprocessor(nom1);
        nxv2=preprocessor(nom2);
        nxv3=preprocessor(nom3);
        
        % calcula la cantidad de notas por ventana de cada archivo
        cant_notas1=size(nxv1,2);
        cant_notas2=size(nxv2,2);
        cant_notas3=size(nxv3,2);
        
        % cantidad maxima de notas por ventana
        cant_max=max([cant_notas1 cant_notas2 cant_notas3]);
        
        % normaliza la cantidad de notas por ventana
        nxv1=[nxv1 zeros(size(nxv1,1),cant_max-cant_notas1)];
        nxv2=[nxv2 zeros(size(nxv2,1),cant_max-cant_notas2)];
        nxv3=[nxv3 zeros(size(nxv3,1),cant_max-cant_notas3)];
        
        % concatena las matrices
        nxv=[nxv1; nxv2; nxv3];
end

% verifica si agrega una ventana con notas aleatorias
if aleatoria==1
    % crea un conjunto de notas aleatorio
    vent_random=zeros(cant_aleatoria,cant_max);
    
    for k=1:cant_aleatoria
        for l=1:cant_max
            vent_random(k,l)=round(random(21,108));
        end
    end
    
    % agrega la ventana en la matriz
    nxv=[nxv; vent_random];
end

% verifica si hay que mezclar las ventanas
if mezclar==1
    % genera un vector de indices
    indices=1:size(nxv,1);
    
    % desordena los indices
    indices=shuffle(indices);
    
    % desordena la matriz
    nxv=nxv(indices,:);
end

% exporta la matriz a un archivo csv
csvwrite('archivo.csv',nxv);

disp('--- TERMINA ETAPA DE PRE PROCESO ---')
% --------------------



% --- processor ---
disp('--- COMIENZA ETAPA DE PROCESO ---')

status=system('processor.exe');

% control
if status==0
    disp('EXITO - Se ejecuto la red.')
else
    disp('ERROR - No se ejecuto la red.')
end

disp('--- TERMINA ETAPA DE PROCESO ---')
% -----------------



% --- postprocessor ---
disp('--- COMIENZA ETAPA DE POS PROCESO ---')

postprocessor('salida');

disp('--- TERMINA ETAPA DE POS PROCESO ---')
% ---------------------


% ----------------------------------------------------------------------