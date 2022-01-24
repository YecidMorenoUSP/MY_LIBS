clc
clear all
close all

data = load('out.txt');

t = data(:,1);
Fx = data(:,2);
Fy = data(:,3);
Fz = data(:,4);
Tx = data(:,5);
Ty = data(:,6);
Tz = data(:,7);

fig = figure(1);
% fig.GraphicsSmoothing = 'off';

ax = axes(fig);

hold on

plot(t,Fx)
plot(t,Fy)
plot(t,Fz)
plot(t,Tx)
plot(t,Ty)
plot(t,Tz)

legend("Fx","Fy","Fz","Tx","Ty","Tz")

hold off
xlabel("Time [ s ] ")
ylabel("Amplitude [ u ]")
title("Axia80M50 Sensor Data")
grid on
grid minor