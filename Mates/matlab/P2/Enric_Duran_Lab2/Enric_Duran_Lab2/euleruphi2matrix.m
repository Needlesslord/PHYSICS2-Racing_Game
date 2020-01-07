function [R] = euleruphi2matrix(u, phi)
% [R] = EULERUPHI2MATRIX(U, PHI)
%
% This function allows to convert from euler vectors
% to the rotation matrix
%
% INPUTS:
% U   - Vector Nx1
% PHI - Angle (rad)
%
% OUTPUTS:
% R - Rotation Matrix
%
% Rodrigues formula
%
% R = I * cos(phi) + (1 - cos(phi)) * u * ut + [u]_x * sin(phi)

%checking input
u = u/norm(u);

if phi > 6*pi
     disp('Your angle was changed from degrees to radians in order to operate')
     phi = phi/180*pi;
end

if  size(u, 1) ~= 3 && size(u, 2) ~= 1
    disp('Your vector was reshaped to a (3, 1) vector in order to operate')
    u = u';
end

%calculate [u]_x
ux = [0 -u(3) u(2); u(3) 0 -u(1); -u(2) u(1) 0];

%apply Rodrigues formula
R = eye(3)*cos(phi) + (1-cos(phi))*(u*u') + ux*sin(phi);


%v = R*u;
%quiver(u, u, u, v, v, v);

%plot
%origin = [0 0 0]';
%quiver3(origin(1,:), origin(2,:), origin(3,:), v(1,:), v(2,:), v(3,:));
%hold on
%quiver3(origin(1,:), origin(2,:), origin(3,:), u(1,:), u(2,:), u(3,:));