%%
%%  Make signal for filtering
%%

Fs = 50e3;              % Sampling frequency (1MHz)
T = 1/Fs;               % Sampling period
L = 256;               % Length of signal
t = (0:L-1)*T;          % Time vector

Fs1 = 2000;             % 2kHz
Fs2 = 10000;            % 10kHz

tic

X = sin(2*pi*Fs1*t) + sin(2*pi*Fs2*t);

figure(1);
plot(t.*1000,X);
title('Signal');
xlabel('t (milliseconds)');
ylabel('X(t)');

Y = fft(X);

P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;

figure(2);
plot(f,P1);
title('Single-Sided Amplitude Spectrum of X(t)');
xlabel('f (Hz)');
ylabel('|P1(f)|');

%%
%% Make filter (LP)
%%

N   = 120;
Fs  = 50e3;
Fp  = 8e3;
Ap  = 0.01;
Ast = 80;

Rp  = (10^(Ap/20) - 1)/(10^(Ap/20) + 1);
Rst = 10^(-Ast/20);

NUM = firceqrip(N,Fp/(Fs/2),[Rp Rst],'passedge');
fvtool(NUM,'Fs',Fs);

% filter signal using FILTER function provided by MATLAB

timeVal1 = toc;
Z = filter(NUM, 1, X);
timeVal2 = toc;

disp(['Filter function MATLAB:', num2str(timeVal2-timeVal1)]);        % print time for using embedded MATLAB function
%for filtering

figure(4);
plot(t.*1000,Z);
title('Filtered Signal');
xlabel('t (milliseconds)');
ylabel('Z(t)');

Y = fft(Z);

P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;

figure(5);
plot(f,P1);
title('Single-Sided Amplitude Spectrum of Z(t)');
xlabel('f (Hz)');
ylabel('|P1(f)|');

% filter signal using FFT of signal and filter coefficients

N = length(X) + length(NUM) - 1;
timeVal1 = toc;
Y = fft(X,N);
F = fft(NUM,N);
Z = Y.*F;
z = ifft(Z);
timeVal2 = toc;

disp(['FFT filtering MATLAB:', num2str(timeVal2-timeVal1)]);        % print time for using FFT filtering

P2 = abs(Z/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;

figure(6);
plot(f,P1);
title('Single-Sided Amplitude Spectrum of Z(t) (fft)');
xlabel('f (Hz)');
ylabel('|P1(f)|');

figure(7);
plot(t.*1000, z(1:length(t)));
title('Signal after fft filtering');
xlabel('t (milliseconds)');
ylabel('z(t)');

samples_file = fopen('samples_float.bin','wb');
X_Single = single(X);
%nbytes = fprintf(samples_file, '%f\n', single(X));
fwrite(samples_file, single(X), 'single');
fclose(samples_file);

filter_file = fopen('filterNorm_float.bin','wb');
NUM_Single = single(NUM);
%nbytes = fprintf(samples_file, '%f\n', single(NUM));
fwrite(filter_file, single(NUM), 'single');
fclose(filter_file);