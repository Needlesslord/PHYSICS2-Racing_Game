function [o] = quatproduct(q, p)
% [O] = QUATPRODUCT(Q, P)
%
% This function allows to solve for the product
% of two quaternions
%
% INPUTS:
% Q  -  Quaternion 4x1
% P  -  Quaternion 4x1
%
% OUTPUTS:
% O  -  Quaternion 4x1

%checking input
if  size(q, 1) ~= 4 && size(q, 2) ~= 1
    disp('Your quaternion q was reshaped to a (4, 1) vector in order to operate')
    v = v';
end

if  size(p, 1) ~= 4 && size(p, 2) ~= 1
    disp('Your quaternion p was reshaped to a (4, 1) vector in order to operate')
    q = q';
end

%Product
o = quatmat(q)*p;