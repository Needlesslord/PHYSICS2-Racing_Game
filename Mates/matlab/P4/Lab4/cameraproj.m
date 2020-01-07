function [ Pt ] = cameraproj(CAW,f,P)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

Np = length(P(1,:)); %Number of points

P = [P; ones(1,Np)]; % Homogeneus coordinates

Pt = zeros(2,Np);

for q = 1: Np
    dummy = CAW*P(:,q); %Points on the camera frame
    Pt(:,q) = dummy(1:2)/dummy(3)*f; %Points on the image plane

end

