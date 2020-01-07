function [u, phi] = quat2euleruphi(q)
% [U, PHI] = QUAT2EULERUPHI(Q)
%
% This function allows to convert from the
% rotation matrix to an euler vector and angle
%
% INPUTS:
% Q - Quaternion 4x1
%
% OUTPUTS:
% U   - Vector 3x1
% PHI - Angle (rad)

%Checking input
q = q/norm(q);

if  size(q, 1) ~= 4 && size(q, 2) ~= 1
    disp('Your quaternion was reshaped to a (4, 1) vector in order to operate')
    q = q';
end

%Calculate phi
phi = 2*acos(q(1));

%Calculate u
u = [q(2)/sin(phi/2); q(3)/sin(phi/2); q(4)/sin(phi/2)];

%Output
phi = phi*180/pi;