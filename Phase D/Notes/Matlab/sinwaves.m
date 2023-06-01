% Define the parameters
x = 2;    % Length of the sine wave
y = 1.5;     % Cutoff point
freq = 2;  % Frequency of the sine wave (lowered)

% Generate the x-axis values
t = linspace(0, x, 1000);

% Generate the sine wave
sin_wave = sin(2*pi*freq*t);
% Plot the first sine wave
figure;
plot(t, sin_wave, 'LineWidth', 2);   % Increase line width
box off;            % Remove figure borders
set(gca, 'Visible', 'off');   % Hide axis
title('');
xlabel('');
ylabel('');

% Generate the second wave with cutoff at y
sin_wave_cutoff = sin_wave;
sin_wave_cutoff(t > y) = 0;

% Plot the second sine wave with cutoff
figure;
plot(t, sin_wave_cutoff, 'LineWidth', 2);   % Increase line width
box off;            % Remove figure borders
set(gca, 'Visible', 'off');   % Hide axis
title('');
xlabel('');
ylabel('');

% Generate the third wave from y to x
sin_wave_partial = sin_wave;
sin_wave_partial(t < y | t > x) = 0;

% Plot the third sine wave from y to x
figure;
plot(t, sin_wave_partial, 'LineWidth', 2);   % Increase line width
box off;            % Remove figure borders
set(gca, 'Visible', 'off');   % Hide axis
title('');
xlabel('');
ylabel('');