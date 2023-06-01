% Define parameters
fs = 1000;              % Sampling frequency (Hz)
T = 1/fs;               % Sampling period (s)
duration = 1;           % Duration of the signal (s)
f = 2;                 % Frequency of the sine wave (Hz)
threshold = 0.5;        % Threshold for PDM (0 to 1)
snapshots = 100;        % Number of discrete-time snapshots

% Generate time vector
t = (0:snapshots-1) * (T);
len_t2 = length(t2);
scaling_factor = t2(len_t2) / t(end);
t = t * scaling_factor;


t2 = 0:T:duration-T ;%;

% Generate discrete-time sine wave
x = sin(2*pi*f*t);
x2 = sin(2*pi*f*t2)

% Generate PDM waveform
pdm = x2 >= threshold;

% Plot the sine wave and the PDM waveform
%subplot(2,1,1);
stem(t, x, 'b', 'filled', 'MarkerSize', 3);
hold on;
xlabel('Time (s)');
%ylabel('Amplitude');
%title('Discrete-Time Sine Wave');

%subplot(2,1,2);
plot(t2, pdm, 'r');
xlabel('Time (s)');
%ylabel('PDM Value');
%title('PDM');

% Adjust the plot layout
xlabel('Time (s)');
title('PCM and PDM');
legend('PCM', 'PDM');


% Add key box annotation
boxText = 'Block: 0.2 sec';
annotation('textbox', [0.69, 0.7, 0.2, 0.1], 'String', boxText, 'FitBoxToText', 'on');
hold off;

% Display the plot
grid on;