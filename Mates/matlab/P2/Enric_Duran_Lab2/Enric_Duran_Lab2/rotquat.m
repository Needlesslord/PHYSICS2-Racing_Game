function [w] = rotquat(v, q)
% [W] = ROTQUAT(V, Q)
%
% This function allows to rotate a vector using
% a quaternion
%
% INPUTS:
% V  -  Vector 3x1
% Q  -  Quaternion 4x1
%
% OUTPUTS:
% W  -  Vector 3x1

%checking input
if  size(v, 1) ~= 3 && size(v, 2) ~= 1
    disp('Your vector was reshaped to a (3, 1) vector in order to operate')
    v = v';
end

if  size(q, 1) ~= 4 && size(q, 2) ~= 1
    disp('Your quaternion was reshaped to a (4, 1) vector in order to operate')
    q = q';
end

if norm(q) ~= 1
     disp('The quaternion norm is different from 1')
     q = q/norm(q);
end

%quaternion v
v = [0; v];

%conjugate q
qcon = [q(1); -q(2); -q(3); -q(4)];

%product
w = quatproduct(q, quatproduct(v, qcon));
w = [w(2); w(3); w(4)];