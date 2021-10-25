function x = point_pinv( )%#codegen
%FUNCPINV Summary of this function goes here
%   Detailed explanation goes here
A=[1 2 3 ; 4 5 6; 7 8 9; 10 11 12];
b=A(:,2);
x=A\b;

end

