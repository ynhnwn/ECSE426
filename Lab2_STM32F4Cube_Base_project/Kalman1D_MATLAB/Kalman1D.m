function [Y,KK,P]= Kalman1D( X, Q, R, pp, F, H)

%Input's length
N=length(X);
X(isinf(X))=[];
X(isnan(X))=[];

% Filter parameters Initial States
% Q    = 0.1;             % variance noise process
% R    = 0.05;            % variance noise measurements
P    = zeros(1,N);        %variance matrix
P(1) = pp;                % initialization
% F    = 0.8;             % Transition matrix
% H    = 1.2;             % Command matrix

Y    = zeros(1,N);      % Estimated vector
Y(1) = 0.00 ;           % initialization
KK   = zeros(1,N);      % Kalman gain vector

% begin
for i=2:N   
   % time update
   X_temp =Y(i-1);
   P_temp =(F*P(i-1)*F')+Q;
   %fprintf('%f \n',P_temp);
   K      = (P_temp*H)./((H*P_temp*H') + R);
   % measurment update
   Y(i)   = X_temp + (K*(X(i)-H*X_temp));
   P(i)   = (1-(K*H)) * P_temp;
   % storing Gain's value
   KK(i)  = K ;
end



    
