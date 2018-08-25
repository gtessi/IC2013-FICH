
clear all;
close all;
clc;

cancion=[];

% Leemos el archivo
cancion = csvread('cancionMidi.csv'); %,cancion);

% normaliza la matriz a formato midi
midi_data=matrix2midi(cancion);

% nombre del archivo midi
nom='salidaMidi2.mid';

% crea el archivo midi
writemidi(midi_data,nom);
