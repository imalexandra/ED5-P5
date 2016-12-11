Fs = 500;                    % sample rate in Hz
N = 82351;                     % number of signal samples
x = VarName2; % noisy waveform
t = (0:N-1)/Fs;              % time vector

Fnorm = 1/(Fs/2);           % Normalized frequency
df = designfilt('lowpassfir','FilterOrder',500,'CutoffFrequency',Fnorm);

%grpdelay(df,2048,Fs)   % plot group delay
D = mean(grpdelay(df)) % filter delay in samples
y = filter(df,[x; zeros(D,1)]); % Append D zeros to the input data
y = y(D+1:end);                  % Shift data to compensate for delay

figure
plot(t,x,t,y,'r','linewidth',1.5);
plot(t,y)
title('Filtered Waveforms');
xlabel('Time (s)');
legend('Filtered Signal');
grid on
axis tight
save my_data.out y -ASCII;