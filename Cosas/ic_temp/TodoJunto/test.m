% initialize matrix:
N = 13;  % number of notes
M = zeros(N,6);

M(:,1) = 1;         % all in track 1
M(:,2) = 1;         % all in channel 1
M(:,3) = (60:72)';      % note numbers: one ocatave starting at middle C (60)
M(:,4) = 120;
M(:,5) = (.5:.5:6.5)';  % note on:  notes start every .5 seconds
M(:,6) = M(:,5) + .5;   % note off: each note has duration .5 seconds

midi_new = matrix2midi(M);
writemidi(midi_new, 'testout3.mid');