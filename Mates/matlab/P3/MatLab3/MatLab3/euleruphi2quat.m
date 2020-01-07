function [q] = euleruphi2quat(u, phi)
% [Q] = EULERUPHI2QUAT(U, PHI)
%
% This function allows to convert from an euler vector
% and angle to a quaternion
%
% INPUTS:
% U   - Vector 3x1
% PHI - Angle (rad)
%
% OUTPUTS:
% Q - Quaternion 4x1

%Checking input
u = u/norm(u);

if abs(phi) > 6*pi
     disp('Your angle was changed from degrees to radians in order to operate')
     phi = phi/180*pi;
end

if  size(u, 1) ~= 3 && size(u, 2) ~= 1
    disp('Your vector was reshaped to a (3, 1) vector in order to operate')
    u = u';
end

%Calculate quaternion
q = [cos(phi/2); u*sin(phi/2)];