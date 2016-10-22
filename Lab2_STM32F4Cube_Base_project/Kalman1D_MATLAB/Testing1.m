fprintf('>>Simulating 1D Kalman Filter: \n\n'); 
%Global parameters
t=0:1:2648;
% F=200.00;
ADC_value = x1.';
n=length(ADC_value);

% Old Kalman State : Kalman1D( X, Q, R, pp, F, H)
[Y1,K1,P1]=Kalman1D(ADC_value, 0.05, 30, 1000, 1, 1);

f1=figure(1);set(f1,'Name','Testing 1: Inital Kalman State Given in Experiment 1');
subplot(3,1,1), plot(t,ADC_value,'MarkerSize',1.2), title(' original signal '), grid on , axis([0 2649 0.775 0.8]),
subplot(3,1,2), plot(t,Y1,'g'), title(' Filtered signal Q=1 R=1 P=1 F=1 H=1'), grid on, axis([0 2649 0.775 0.8]),
subplot(3,1,3), plot(t,ADC_value,'b--','MarkerSize',0.9), hold on, plot(t,Y1,'r'), hold off,...
title(' Superposition'), legend(' original ',' filtered '), grid on, axis([0 2649 0.775 0.8]);

%fprintf('New Line \n');
% New Kalman State : Kalman1D( X, Q, R, pp, F, H)
[Y2,K2,P2]=Kalman1D(ADC_value, 0.02, 50, 50000, 1, 1);

f2=figure(2);set(f2,'Name','Testing 2: New Kalman State');
subplot(3,1,1), plot(t,ADC_value,'MarkerSize',1.2), title(' original signal '), grid on, axis([0 2649 0.775 0.8]),
subplot(3,1,2), plot(t,Y2,'g'), title(' Filtered signal Q=0.6 R=100 P=690 F=0.95 H=0.8'), grid on, axis([0 2649 0.775 0.8]),
subplot(3,1,3), plot(t,ADC_value,'b--','MarkerSize',0.9), hold on, plot(t,Y2,'r'), hold off, ...
title(' Superposition'), legend(' original ',' filtered '), grid on, axis([0 2649 0.775 0.8]);


