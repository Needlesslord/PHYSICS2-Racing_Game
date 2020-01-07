function [r] = euleruphi2rotvec(u, phi)
% [R] = EULERUPHI2ROTVEC(U, PHI)
%
% This function allows to convert from an euler vector
% and angle to a rotation vector
%
% INPUTS:
% U   - Vector 3x1
% PHI - Angle (rad)
%
% OUTPUTS:
% R - Rotation Vector 3x1

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

%Calculate rotation vector
r = phi*u;