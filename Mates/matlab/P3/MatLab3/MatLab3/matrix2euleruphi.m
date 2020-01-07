function [u, phi] = matrix2euleruphi(R)
% [U, PHI] = MATRIX2EULERUPHI(R)
%
% This function allows to convert from the
% rotation matrix to an euler vector and angle
%
% INPUTS:
% R - Rotation Matrix
%
% OUTPUTS:
% U   - Vector Nx1
% PHI - Angle (rad)

%Checking input
if det(R) > 1 -1.e-6 && det(R) < 1+1.e-6
    dif = inv(R)-transpose(R);
     if sum(sum(abs(dif))) < 1.e-6
         %Calculating phi
         phi = acos((trace(R)-1)/2);
         %Calculating [u]_x
         ux = (R-transpose(R))/2*sin(phi);
         %output
         u = [ux(3,2); ux(1,3); ux(2,1)];
         phi = phi*180/pi;
     else
        disp('Your Rotation Matrix is not orthonormal, it is not a rotation')
        u = "NaN";
        phi = "NaN";
     end
else
    disp('Your Rotation Matrix determinant is not equal to 1, it is not a rotation')
    u = "NaN";
    phi = "NaN";
end