



N = 256;
M = 129;
n = (1:N)'-1; %'# define the time index
x = sin(2*pi*1.5*n/N); %# input with 1.5 cycles per 1024 points
h = hanning(M) .* sinc(0.25*(-64:1:64)'); %'# windowed sinc LPF, Fc = pi/4
h = h./sum(h); %# normalize DC gain

y = ifft(fft(x) .* fft(h,N)); %# inverse FT of product of sampled spectra
%y = real(y); %# due to numerical error, y has a tiny imaginary part
%# Depending on your FT/IFT implementation, might have to scale by N or 1/N here
figure; plot(x), hold on, plot(y);

load XFFT.mat

X_FFT = fftshift(xx_F);

Fs = 4.166e6;
f_scale = 0:Fs/256:Fs-Fs/256;
figure; plot(f_scale,abs(X_FFT)), hold on, plot(f_scale,abs(X_FFT .* fft(h,N))), plot(f_scale,abs(fft(h,N)));

figure; plot(f_scale,abs(fftshift(X_FFT))), hold on, plot(f_scale,abs(fftshift(X_FFT .* fft(h,N)))), plot(f_scale,abs(fftshift(fft(h,N))));


y1 = ifft(fft(x,N+M-1) .* fft(h,N+M-1));
figure; plot(x), hold on, plot(y1(65:end-64));