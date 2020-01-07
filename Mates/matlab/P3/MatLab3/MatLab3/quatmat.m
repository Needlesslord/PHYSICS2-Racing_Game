function [R] = quatmat(q)
% [R] = QUATMAT(Q)
%
% This function allows to convert a
% quaternion to its multiplication matrix
%
% INPUTS:
% Q  -  Quaternion 4x1
%
% OUTPUTS:
% R  -  Matrix 4x4

%Multipication Matrix
R = [
    q(1) -q(2) -q(3) -q(4);
    q(2) q(1) -q(4) q(3);
    q(3) q(4) q(1) -q(2);
    q(4) -q(3) q(2) q(1)
    ];
