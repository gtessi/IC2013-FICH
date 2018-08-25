function [v,c] = defuzzyfication(Yj,Bj,e)
    % ------------------------------------------------------
    % Consiste en "decodificar" la salida borrosa en un valor real
    % ------------------------------------------------------
    % ENTRADA
    % Yj = vector con los centroides de los conjuntos borrosos
    % Bj = vector con las areas de los conjuntos borrosos
    % e = error calculado
    % ------------------------------------------------------
    % SALIDA
    % v = salida real de la tension (aire acondicionado)
    % c = salida real de la corriente (calefactor)
    % ------------------------------------------------------
    
    % y = numerador / denominador; 
    % numerador = suma(Yj * Bj)
    % denominador = suma(Bj)
    
    numerador=0;
    denominador=0;
    
    % Calcula los valores reales a partir de los conjuntos borrosos
    for i=1:length(Bj)
        numerador=numerador+(Yj(i)*Bj(i));
        denominador=denominador+Bj(i);
    end
    
    % Devuelve el valor real segun si el error es positivo (hay mas calor)
    % o negativo (hay menos calor), activando el aire acondicionado o el
    % calefactor respectivamente
    if(denominador==0)
        v=0;
        c=0;
    else
        if (e>0)
            v=numerador/denominador;
            c=0;
        else
            v=0;
            c=numerador/denominador;
        end
    end
end