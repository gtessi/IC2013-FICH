clear all
close all
clc
% ------------------------------------------------------

% *** declara variables
nom_archi='or.csv';

ejemplos=1000;
pruebas=200;

epocas=10;
error=99;
nu=0.05;

% *** crea los archivos y los vectores y matrices
[entradas_ent,salidas_ent]=genEjemplos(nom_archi,ejemplos);
entradas_pru=genPruebas(nom_archi,pruebas);

% *** entrenamiento
w=entrenamiento(entradas_ent,salidas_ent,epocas,error,nu);

% *** pruebas
salidas_pru=prueba(entradas_pru,w);

disp([entradas_pru salidas_pru])