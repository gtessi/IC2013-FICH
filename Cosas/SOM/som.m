clear all
clc

radio=1;

patrones=[0.5 0.5; -0.5 0.5; 0.5 -0.5;-0.5 -0.5];

pesos=[0.408225  0.241172 ;
0.0736562  0.499749  ;
-0.270305  -0.437473  ;
-0.015715  -0.176687];

for k=1:4
    for l=1:4
        y(k,l)=distancia(patrones(k,:),pesos(l,:));
    end
end

y

nu=0.2;

for k=1:4
    pesosN(k,:)=pesos(k,:)+nu*(patrones(1,:)-pesos(k,:));
end

pesosN

for k=1:4
    pesosN(k,:)=pesosN(k,:)+nu*(patrones(1,:)-pesosN(k,:));
end

pesosN