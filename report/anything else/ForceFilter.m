Fs = 500;                    % sample rate in Hz
N = 82351;                     % number of signal samples
x = VarName1; % noisy waveform
x = x+0.29; %compensate for the non-normalized measurements
t = (0:N-1)/Fs;              % time vector

Fnorm = 1/(Fs/2);           % Normalized frequency
df = designfilt('lowpassfir','FilterOrder',500,'CutoffFrequency',Fnorm);
y = filter(df,x);
%grpdelay(df,2048,Fs)   % plot group delay
%D = mean(grpdelay(df)) % filter delay in samples
%y = filter(df,[x; zeros(D,1)]); % Append D zeros to the input data
%y = y(D+1:end);                  % Shift data to compensate for delay

figure
plot(t,x,t,y,'r','linewidth',1.5);
title('Force Measurements');
xlabel('Time (s)');
ylabel('Force (N)');
legend('Original Signal','Filtered Signal');
grid on
axis tight
save my_data.out y -ASCII;