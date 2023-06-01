% Define parameters
fs = 1000;              % Sampling frequency (Hz)
T = 1/fs;               % Sampling period (s)
duration = 1;           % Duration of the signal (s)
f = 2;                 % Frequency of the sine wave (Hz)
threshold = 0.5;        % Threshold for PDM (0 to 1)

% Generate time vector
t = 0:T:duration-T;

% Generate sine wave
x = sin(2*pi*f*t);

% Generate PDM waveform
pdm = x >= threshold;

% Plot the sine wave and the PDM waveform
plot(t, x, 'b', t, pdm, 'r');

xlabel('Time (s)');
title('Sine Wave and PDM');
legend('Sine Wave', 'PDM');

% Add key box annotation
boxText = 'Block: 0.2 sec';
annotation('textbox', [0.69, 0.7, 0.2, 0.1], 'String', boxText, 'FitBoxToText', 'on');


% Display the plot
grid on;