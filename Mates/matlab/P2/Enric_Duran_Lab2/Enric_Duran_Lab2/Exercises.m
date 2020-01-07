%% Exercise 1
% Create and test a function that given euler axis/angle information
% returns the rotation matrix.
% Do the next verifications:
%   - Calculate the determinant
%   - Ensure that the transpose operation is equivalent to the inverse
%   - Observe what happens to a vector parallel to the axis direction
%   - Observe what happens to a vector perpendicular to the axis direction
disp('EX1')
u = [1 2 1]';
R = euleruphi2matrix(u, 45)
determinant = det(R)
inverse = inv(R)
transposed = transpose(R)
disp('parallel vector: ')
v = 5*u
disp('when rotated: ')
w = R*v
disp('perpendicular vector: ')
y=1;z=1;x=(-u(2)*y-u(3)*z)/u(1);
v= [x y z]'
disp('when rotated: ')
w = R*v

%% Exercise 2
% Use the past function and the function Cubeplot/Cubeplot2 to transform the
% orientation of the cube given by M
% Find the rotation vectors that makes:
%    - The green face points in the positive z direction and the orange
%    face in the -y direction
%    - The orange face points in the -z direction and the blue face into
%    the +y direction
%    - The red face points on the -x direction and the blue face into 
%    the -y direction.


M = [    -1  -1 1;   %Node 1
    -1   1 1;   %Node 2
    1   1 1;   %Node 3
    1  -1 1;   %Node 4
    -1  -1 -1;  %Node 5
    -1   1 -1;  %Node 6
    1   1 -1;  %Node 7
    1  -1 -1]; %Node 8

% Call to Cubeplot
Cubeplot(M);

R = euleruphi2matrix([0 1 0]', 90);
N = R*M';
% Call to Cubeplot
Cubeplot(N');

R = euleruphi2matrix([1 1 1]', 120);
N = R*M';
% Call to Cubeplot
Cubeplot(N');

R = euleruphi2matrix([1 -1 0]', 180);
N = R*M';
% Call to Cubeplot
Cubeplot(N');

%% Exercise 3
% Create a function that implements the quaternion multiplication.
% Create a function that given a vector and a quaternion, return the vector
% rotated by the attitude encoded in the quaternion using quaternion
% multiplications.
% Test it an argument/demonstrate why your function is well implemented.
disp('EX3')
v = [1 0 0];
q = [sqrt(2)/2 0 0 sqrt(2)/2];
w = rotquat (v, q)

%% Exercise 4
% Create a large set of rotation matrices (at least 100) for which the euler axis may be 
% random (not necessarily random, but not the same) and the euler angle in
% increasing order form 0 to 6 pi. (Use a FOR LOOP)
% Make a plot of the trace of this matrices with the value of the angle in
% the x axis i.e. Trace(R(phi,e)) vs. \phi . Explain what you observe.
disp('EX4')
ang = [];
tr = [];
for  phi = 0:0.1:6*pi
    ang = [ang; phi];
    v = rand(3, 1);
    R = euleruphi2matrix(v, phi);
    tr = [tr; trace(R)];
end
figure;
plot(ang, tr);
fprintf('We can see that no matter the axis, the trace follows a sinusoidal path as the angle is\naugmented, then we can assume that it only depends on the angle.')

%% Exercise 5
% Create a function that given a set of euler angles, return its respective
% rotation matrix.
% Create also a function that given a rotation matrix return the
% respective rotation angles.
% 	-Ensure that the case for which theta = pi/2 + k*pi with k=1,2,.. is
% 	   well implemented
disp('EX5')
R = eulerangles2matrix(90, 0, 45)
[roll, pitch, yaw] = matrix2eulerangles(R)

R = eulerangles2matrix(0, 90, 0)
[roll, pitch, yaw] = matrix2eulerangles(R)
