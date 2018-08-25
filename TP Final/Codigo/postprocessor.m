function postprocessor(nom)
    % ------------------------------------------------------
    % Posprocesa archivos csv para convertirlos a formato midi
    % ------------------------------------------------------
    % ENTRADA
    % nom = nombre del archivo midi
    % ------------------------------------------------------
    % SALIDA
    % ------------------------------------------------------
    
    % carga un archivo csv de entrada
    notas=csvread('cancion.csv');
    
    % cantidad de notas
    cant_notas=size(notas,1);
    
    % inicializa matriz M
    M=zeros(cant_notas,6);
	
    % recorre las notas
    for k=1:cant_notas
        % agrega la nota a la matriz
        M(k,3)=notas(k,1);
        
        % tiempo inicial
        M(k,5)=notas(k,2);
        
        % tiempo final
        M(k,6)=notas(k,3);
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
    M(:,4)=120; % todos en 120
    
    % normaliza la matriz a formato midi
    midi_data=matrix2midi(M);
    
    % nombre del archivo midi
    name=[nom,'.mid'];
    
    % crea el archivo midi
    writemidi(midi_data,name);
    
    % grafica
    % calcula el piano-roll
    [PR,t,nn]=piano_roll(M);
    
    % grafica el piano-roll
    figure;
    imagesc(t,nn,PR);
    axis xy;
    title('MIDI generado');
    xlabel('Tiempo (s)');
    ylabel('Numero de nota');
end