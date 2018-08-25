clear all
close all
clc
% ----------------------------------------------------------------------
% script de preprocesamiento para archivos midi, con ventaneo temporal

% nombre del archivo midi
nom='jesu.mid';

% carga el archivo midi
midi_data=readmidi(nom);

% matriz de notas y duracion del midi
[notas,tfin]=midiInfo(midi_data);

% cantidad de notas
cant_notas=size(notas,1);

% delta de tiempo
dt=0.001;

% vector de muestras temporales
t=0:dt:tfin;

% vector de notas acumuladas
acum=t;

% cantidad de muestras
cant_t=length(t);

% busca la cantidad de notas en cada instante de tiempo
for k=1:cant_t
    % contador
    idx=1;
    
    % recorre todas las notas y acumula las mismas si pertenecen al
    % instante de tiempo
    for l=1:cant_notas
        % vector nota (fila l de matriz notas)
        nota=notas(l,:);
        
        % columna 5 = tiempo inicial
        % columna 6 = tiempo final
        
        % verifica si la nota pertenece al instante de tiempo
        if (nota(5)<=t(k) && nota(6)>=t(k))
            % incrementa el contador
            idx=idx+1;
        end
    end
    
    % guarda la cantidad de notas en el instante de tiempo
    acum(k)=idx;
end

% busca la cantidad maxima de notas ejecutadas al mismo tiempo
maximo=max(acum);

% tama�o de la ventana
vent_size=0.2;

% solapamiento
vent_sol=0.1;

% cantidad de ventanas
cant_vent=round((tfin-vent_sol)/(vent_size-vent_sol));

% define la matriz de notas en cada ventana
notasXventana=zeros(cant_vent,maximo);

% recorre todas las ventanas
for k=1:cant_vent
    % vector ventana
    ventana=vent_size.*[(k-1) k]-vent_sol*(k-1);
    
    % contador
    idx=1;
    
    % recorre todas las notas y acumula las mismas si pertenecen a la
    % ventana
    for l=1:cant_notas
        % columna 5 = tiempo inicial
        % columna 6 = tiempo final
        
        % verifica si la nota pertenece a la ventana
        if (notas(l,5)<=ventana(2) && notas(l,6)>=ventana(1))
            % guarda la nota en la matrix
            notasXventana(k,idx)=notas(l,3);
            
            % incrementa el contador
            idx=idx+1;
        end
    end
end

% crea un archivo csv de salida
csvwrite('archivo.csv',notasXventana);

% ----------------------------------------------------------------------