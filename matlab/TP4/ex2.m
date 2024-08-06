close all;
Tmax = 0.2;
pas=Tmax/numel(x2);
N=numel(x2); %FFT size
tf = fft(x2,N);
X_TF = 1/N*fftshift(tf);
Norm = abs(X_TF);
sampleIndex = -N/2:N/2-1;
f=sampleIndex/Tmax; %f sera l'axe des abscisses
figure;
plot(f,Norm); %magnitudes vs frequences
F=f(find(Norm>0.1));
disp(F);
xlabel('f (Hz)');
ylabel('Amplitude');

phase=atan2(imag(X_TF),real(X_TF))*180/pi; %phase information
figure;
plot(f,phase); %phase vs frequencies
xlabel('f (Hz)');
ylabel('Phase (degres)');
disp(phase(find(phase>10)))

phaser=atan2(imag(X_TF),real(X_TF)); %phase information
figure;
plot(f,phaser); %phase vs frequencies
xlabel('f (Hz)');
ylabel('Phase (radians)');

seuil = max(Norm)/100; %On force un seuil a 1/100eme du max des amplitudes des
%frequences
%Toutes les frequences qui ont une amplitude, dans le spectre des frequences,
%plus petites que 1/100
%de la plus grande amplitude, seront ignorees
phase(Norm<seuil) = 0; %on force a 0 les phases de sinusoides negligeables
figure;
plot(f,phase); %phase vs frequencies
xlabel('f (Hz)');
ylabel('Phase (degres)');