function [u, phi] = rotvec2euleruphi(r)
% [U, PHI] = ROTVEC2EULERUPHI(R)
%
% This function allows to convert from a
% rotation vector to an euler vector and angle
%
% INPUTS:
% R - Rotation Vector 3x1
%
% OUTPUTS:
% U   - Vector 3x1
% PHI - Angle (rad)

%Checking input
if  size(r, 1) ~= 3 && size(r, 2) ~= 1
    disp('Your rotation vector was reshaped to a (3, 1) vector in order to operate')
    u = u';
end

%Calculate phi
phi = norm(r);

%Calculate u
u = r/norm(r);

%Output
phi = phi*180/pi;