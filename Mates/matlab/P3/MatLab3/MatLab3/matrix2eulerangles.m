function [roll, pitch, yaw] = matrix2eulerangles(R)
% [ROLL, PITCH, YAW] = MATRIX2EULERANGLES(R)
%
% This function allows to convert from the
% rotation matrix to euler angles
%
% INPUTS:
% R - Rotation Matrix
%
% OUTPUTS:
% ROLL  - Angle X (rad)
% PITCH - Angle Y (rad)
% YAW   - Angle Z (rad)

%checking input
if det(R) > 1 -1.e-6 && det(R) < 1+1.e-6
    dif = inv(R)-transpose(R);
     if sum(abs(dif)) < 1.e-6
         %Calculating Angles
         pitch = asin(-R(3,1));
         if cos(pitch) < -1.e-6 || cos(pitch) > 1.e-6
            roll  = atan2( R(3,2)/cos(pitch), R(3,3)/cos(pitch));
            yaw   = atan2( R(2,1)/cos(pitch), R(1,1)/cos(pitch));
         
            %Change to Degrees
            roll  = roll*180/pi;
            pitch = pitch*180/pi;
            yaw   = yaw*180/pi;
         else
            disp('pitch is equal to pi/2, cannot calculate roll and yaw')
            roll = "NaN";
            pitch = 90;
            yaw = "NaN";
         end
     else
        disp('Your Rotation Matrix is not orthonormal, it is not a rotation')
        roll = "NaN";
        pitch = "NaN";
        yaw = "NaN";
     end
else
    disp('Your Rotation Matrix determinant is not equal to 1, it is not a rotation')
    roll = "NaN";
    pitch = "NaN";
    yaw = "NaN";
end