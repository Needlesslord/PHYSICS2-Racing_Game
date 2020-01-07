function [R] = eulerangles2matrix(roll, pitch, yaw)
% [R] = EULERANGLES2MATRIX(ROLL, PITCH, YAW)
%
% This function allows to convert from euler angles
% to the rotation matrix
%
% INPUTS:
% ROLL  - Angle X (rad)
% PITCH - Angle Y (rad)
% YAW   - Angle Z (rad)
%
% OUTPUTS:
% R - Rotation Matrix

%checking input
if roll > 2*pi
     disp('Your roll angle was changed from degrees to radians in order to operate')
     roll = roll/180*pi;
end

if pitch > 2*pi
     disp('Your pitch angle was changed from degrees to radians in order to operate')
     pitch = pitch/180*pi;
end

if yaw > 2*pi
     disp('Your yaw angle was changed from degrees to radians in order to operate')
     yaw = yaw/180*pi;
end

%Calculate Matrix
R = [
    cos(pitch)*cos(yaw) cos(yaw)*sin(pitch)*sin(roll)-cos(roll)*sin(yaw) cos(roll)*cos(yaw)*sin(pitch)+sin(yaw)*sin(roll);
    cos(pitch)*sin(yaw) sin(yaw)*sin(pitch)*sin(roll)+cos(roll)*cos(yaw) sin(yaw)*sin(pitch)*cos(roll)-cos(yaw)*sin(roll);
    -sin(pitch)         cos(pitch)*sin(roll)                             cos(pitch)*cos(roll)
    ];
