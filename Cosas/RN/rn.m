mu=0.1;

disp('primer patron')

x=[-1 1.0097 0.97999]
yd=-1

pesos11=[ 0.11091  0.272634  0.50665]'
pesos12=[-0.155223  0.516355  -0.575573]'
pesos21=[-0.00997955  -0.350493  -0.475668]'

y11=sig(x*pesos11)
y12=sig(x*pesos12)

y1=[-1 y11 y12];

y21=sig(y1*pesos21)

disp('termina propagacion hacia adelante')

error=yd-y21;

delta21=0.5*error*(1+y21)*(1-y21)

disp('entra en capa oculta')
disp('neurona 1')

sumatoria=delta21*pesos21(2);

delta11=sumatoria*0.5*(1+y11)*(1-y11)

disp('neurona 2')

sumatoria=delta21*pesos21(3);

delta12=sumatoria*0.5*(1+y12)*(1-y12)

disp('termina propagacion hacia atras')

pesos11=pesos11+mu*delta11*x'
pesos12=pesos12+mu*delta12*x'
pesos21=pesos21+mu*delta21*y1'

disp('termina actualizacion pesos')

disp('segundo patron')

x=[-1 1.0302 -1.0076]
yd=1

y11=sig(x*pesos11)
y12=sig(x*pesos12)

y1=[-1 y11 y12];

y21=sig(y1*pesos21)

disp('termina propagacion hacia adelante')

error=yd-y21;

delta21=0.5*error*(1+y21)*(1-y21)

disp('entra en capa oculta')
disp('neurona 1')

sumatoria=delta21*pesos21(2);

delta11=sumatoria*0.5*(1+y11)*(1-y11)

disp('neurona 2')

sumatoria=delta21*pesos21(3);

delta12=sumatoria*0.5*(1+y12)*(1-y12)

disp('termina propagacion hacia atras')

pesos11=pesos11+mu*delta11*x'
pesos12=pesos12+mu*delta12*x'
pesos21=pesos21+mu*delta21*y1'

disp('termina actualizacion pesos')

