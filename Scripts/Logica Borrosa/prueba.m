clc
close all
clear all
% -----------------------------------------------

A=[0 0.2 0.3 0.5 0.7 0.9 1];
Ac=complemento(A)
AiAc=interseccion(A,Ac)
AuAc=union(A,Ac)
numerador=cardinalidad(interseccion(AiAc,AuAc))
denominador=cardinalidad(AuAc)
numerador/denominador
B=[0.3 0.4 0.5 0.8 0.9 1]
inclusion(A,B)
B=[0.1 0.3 0.4 0.5 0.8 0.9 1]
inclusion(A,B)
B=[0.1 0.3 0.4 0.5 0.8 0.9 0.5]
inclusion(A,B)
B=[0.1 0.3 0.4 0.5 0.8 0.9 1]
inclusion(AiAc,AuAc)
res=interseccion(AiAc,AuAc)
res==AiAc