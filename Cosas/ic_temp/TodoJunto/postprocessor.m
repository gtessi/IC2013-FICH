clear all
close all
clc
% ----------------------------------------------------------------------
% script de postprocesamiento para archivos midi, con ventaneo temporal

% carga un archivo csv de entrada
notasXventana=csvread('cancion.csv');

% tama�o de la ventana
vent_size=0.2;

% solapamiento
vent_sol=0.1;

% cantidad de ventanas
cant_vent=size(notasXventana,1);

% cantidad de notas por ventana
cant_notas=size(notasXventana,2);

% carga archivo midi original
midi_data=readmidi('jesu.mid');
notasOriginal=midiInfo(midi_data);

% matriz base
M=zeros(size(notasOriginal,1),6);

% indice
idx=1;

% recorre las ventanas
for k=1:cant_vent
    % recorre las notas
    for l=1:cant_notas
        % nota
        nota=notasXventana(k,l);
        
        % verifica que la nota no sea cero
        if nota~=0
            % agrega la nota a la matriz
            M(idx,3)=nota;
            
            % tiempo inicial
            M(idx,5)=(k-1)*vent_size-(k-1)*vent_sol;
            
            % tiempo final
            M(idx,6)=k*vent_size-k*vent_sol;
            
            % incrementa el contador
            idx=idx+1;
        end
    end
end

% ordena la matriz por notas segun el tiempo inicial
M=sortG(M,3,5);

% elimina las notas que se repiten en ventanas consecutivas
k=2;
tam=size(M,1);

% recorre la matriz
while k<=tam
    % verifica que las notas sean iguales y que el tiempo inicial de la
    % segunda sea menor al tiempo final de la primera
    if M(k,3)==M(k-1,3) && M(k,5)<=M(k-1,6)
        % actualiza el tiempo final
        M(k-1,6)=M(k,6);
        
        % elimina la nota
        M(k,:)=[];
        
        % actualiza el limite
        tam=tam-1;
    else
        % incrementa el contador
        k=k+1;
    end
end

% ordena la matriz segun el tiempo inicial
M=sortG(M,5);

% --- 6 columnas ---
% track number
% channel number
% note number (midi encoding of pitch)
% volume
% start time (seconds)
% end time (seconds)

% define track number, channel number y volume
M(:,1)=1; % todos en track 1
M(:,2)=0; % todos en channel 0
M(:,4)=90; % todos en 90

% normaliza la matriz a formato midi
midi_data=matrix2midi(M);

% nombre del archivo midi
nom='salida.mid';

% crea el archivo midi
writemidi(midi_data,nom);

% ----------------------------------------------------------------------