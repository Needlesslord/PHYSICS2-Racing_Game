function [R, eulerangles, euleruphi, quaternion, rotvec] = rotation_change(X, c)
% [R, EULERANGLES, EULERUPHI, ROTVEC, QUATERNION] = ROTATION_CHANGE(U, PHI)
%
% This function allows to convert from an expression of rotation
% to all of them
%
% INPUTS:
% X   -   Rotation Matrix 3x3 / Euler Angles 3x1 / 
%         Euler vector and angle 4x1 / Quaternion 4x1 /
%         Rotation Vector 3x1
%
% C   -   Character
%
% OUTPUTS:
% R            -  Rotation Matrix 3x3
% EULERANGLES  -  Euler Angles 3x1
% EULERUPHI    -  Euler vector and angle 4x1
% QUATERNION   -  Quaternion 4x1
% ROTVEC       -  Character

switch c
    case 'r'
        R = X;
        [eulerangles(1), eulerangles(2), eulerangles(3)] = matrix2eulerangles(X);
        eulerangles = eulerangles';
        [euleruphi, euleruphi(4)] = matrix2euleruphi(X);
        quaternion = euleruphi2quat([euleruphi(1) euleruphi(2) euleruphi(3)]', euleruphi(4));
        rotvec = euleruphi2rotvec([euleruphi(1) euleruphi(2) euleruphi(3)], euleruphi(4));
        
    case 'e'
        R = eulerangles2matrix(X(1), X(2), X(3));
        eulerangles = X;
        [euleruphi, euleruphi(4)] = matrix2euleruphi(R);
        quaternion = euleruphi2quat([euleruphi(1) euleruphi(2) euleruphi(3)], euleruphi(4));
        rotvec = euleruphi2rotvec([euleruphi(1) euleruphi(2) euleruphi(3)], euleruphi(4));
        
    case 'p'
        R = euleruphi2matrix([X(1) X(2) X(3)], X(4));
        [eulerangles(1), eulerangles(2), eulerangles(3)] = matrix2eulerangles(R);
        eulerangles = eulerangles';
        euleruphi = X;
        quaternion = euleruphi2quat([X(1) X(2) X(3)], X(4));
        rotvec = euleruphi2rotvec([X(1) X(2) X(3)], X(4));
            
    case 'q'
        [euleruphi, euleruphi(4)] = quat2euleruphi(X);
        R = euleruphi2matrix([euleruphi(1) euleruphi(2) euleruphi(3)], euleruphi(4));
        [eulerangles(1), eulerangles(2), eulerangles(3)] = matrix2eulerangles(R);
        eulerangles = eulerangles';
        quaternion = X;
        rotvec = euleruphi2rotvec([euleruphi(1) euleruphi(2) euleruphi(3)], euleruphi(4));
        
    case 'v'
        [euleruphi, euleruphi(4)] = rotvec2euleruphi(X);
        R = euleruphi2matrix([euleruphi(1) euleruphi(2) euleruphi(3)], euleruphi(4));
        [eulerangles(1), eulerangles(2), eulerangles(3)] = matrix2eulerangles(R);
        eulerangles = eulerangles';
        quaternion = euleruphi2quat([euleruphi(1) euleruphi(2) euleruphi(3)], euleruphi(4));
        rotvec = X;
        
    otherwise
        disp("The input character was not recognized.");
        
end