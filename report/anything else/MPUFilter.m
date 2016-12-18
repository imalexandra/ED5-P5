Fs = 153;                    % sample rate in Hz
Fs2 = 675;
N = 4591;                     % number of signal samples
N2 = 20262;
a1 = z(:,[1]);
a2 = z(:,[2]);
a3 = z(:,[3]);
g1 = z(:,[4]);
g2 = z(:,[5]);
g3 = z(:,[6]);

%x = z; % noisy waveform
t = (0:N-1)/Fs;              % time vector
t2 = (0:N2-1)/Fs2; 
Fnorm = 1/(Fs/2);           % Normalized frequency
Fnorm2 = 1/(Fs2/2);
df1 = designfilt('lowpassfir','FilterOrder',10,'CutoffFrequency',Fnorm);
df2 = designfilt('lowpassfir','FilterOrder',10,'CutoffFrequency',Fnorm2);
%grpdelay(df,2048,Fs)   % plot group delay
y1 = filter(df1,a1);
y2 = filter(df1,a2);
y3 = filter(df1,a3);
y4 = filter(df1,g1);
y5 = filter(df1,g2);
y6 = filter(df1,g3);
%D = mean(grpdelay(df)); % filter delay in samples
%y = filter(df,[a1; zeros(D,1)]); % Append D zeros to the input data
%y = y(D+1:end);                  % Shift data to compensate for delay
%D2 = mean(grpdelay(df2)); % filter delay in samples
%y7 = filter(df2,[s1; zeros(D2,1)]); % Append D zeros to the input data
%y7 = y7(D2+1:end);                  % Shift data to compensate for delay

figure
plot(t,a1,t,y1,'r','linewidth',1.5);
title('Filtered Waveforms');
xlabel('Time (s)');
legend('Noisy Waveform', 'Filtered Signal');
grid on
axis tight

figure
plot(t,a2,t,y2,'r','linewidth',1.5);
title('Filtered Waveforms');
xlabel('Time (s)');
legend('Noisy Waveform', 'Filtered Signal');
grid on
axis tight

figure
plot(t,a3,t,y3,'r','linewidth',1.5);
title('Filtered Waveforms');
xlabel('Time (s)');
legend('Noisy Waveform', 'Filtered Signal');
grid on
axis tight

figure
plot(t,g1,t,y4,'r','linewidth',1.5);
title('Filtered Waveforms');
xlabel('Time (s)');
legend('Noisy Waveform', 'Filtered Signal');
grid on
axis tight

figure
plot(t,g2,t,y5,'r','linewidth',1.5);
title('Filtered Waveforms');
xlabel('Time (s)');
legend('Noisy Waveform', 'Filtered Signal');
grid on
axis tight

figure
plot(t,g3,t,y6,'r','linewidth',1.5);
title('Filtered Waveforms');
xlabel('Time (s)');
legend('Noisy Waveform', 'Filtered Signal');
grid on
axis tight

%figure
%plot(t2,s1,t2,y7,'r','linewidth',1.5);
%title('Filtered Waveforms');
%xlabel('Time (s)');
%legend('Noisy Waveform', 'Filtered Signal');
%grid on
%axis tight

%Y = fft(a1);
%plot(t,Y)
%a1=a1-mean(a1);
%Y = detrend(x,'constant');
%m = abs(Y);
%p = angle(Y);
%f = (0:length(Y)-1)*50/length(Y);
%figure
%subplot(2,1,1)
%plot(f,m)
%title('Magnitude')

%subplot(2,1,2)
%plot(f,rad2deg(p))
%title('Phase')

figure
subplot(2,1,1)
plot(t,a1)
xlabel('Time (s)');
ylabel('Reading');
title('Accelerometer x-axis')

subplot(2,1,2)
plot(t,g1)
xlabel('Time (s)');
ylabel('Reading');
title('Gyroscope x-axis')