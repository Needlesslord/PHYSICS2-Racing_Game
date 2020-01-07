
% From Lab 2 we have two functions:
%
% *  Given principal Euler axis/angle, returns the rotation matrix.
% *  Given a set of Euler angles, returns the rotation matrix.
%
% We used the past functions and the function Cubeplot/Cubeplot2 to transform the
% orientation of the cube given by M
%

M = [    -1  -1 1;   %Node 1
    -1   1 1;   %Node 2
    1   1 1;   %Node 3
    1  -1 1;   %Node 4
    -1  -1 -1;  %Node 5
    -1   1 -1;  %Node 6
    1   1 -1;  %Node 7
    1  -1 -1]'; %Node 8

%
% Now it is time to complete all the transformations, 
% adding also the quaternions representation
%
% If not completed in Lab 2:
%
%% Exercise 0
% Create a function that implements the quaternion multiplication.
% Create a function that given a vector and a quaternion, returns the vector
% rotated by the attitude encoded in the quaternion using quaternion
% multiplications.
% Test it an argument/demonstrate why your function is well implemented.

disp("EX0")

v = [0, 1, 0];
q = [sqrt(2)/2 0 0 sqrt(2)/2];
rotquat(v, q)

%
%% Exercise 1
% Create functions that:
%
% *  Given a rotation matrix, returns the Euler rotation angles.
% *  Given a rotation matrix, returns the principal Euler axis/angle.
% *  Given principal Euler axis/angle, returns the quaternion.
% *  Given a quaternion, returns the principal Euler axis/angle.
% *  Given principal Euler axis/angle, returns the rotation vector.
% *  Given the rotation vector, returns principal Euler axis/angle.
%
% Check the past functions and the function Cubeplot/Cubeplot2 to transform the
% orientation of the cube given by M

disp("EX1")

R = [-1 0 0; 0 0 1; 0 1 0];
[roll, pitch, yaw] = matrix2eulerangles(R)
R = eulerangles2matrix(roll, pitch, yaw)
N = R*M;
Cubeplot(N');

R = [1 0 0; 0 0 1; 0 -1 0];
[u, phi] = matrix2euleruphi(R)
R = euleruphi2matrix(u, phi)
N = R*M;
Cubeplot(N');

u = [0; 1; 0]
phi = 90;
q = euleruphi2quat(u, phi)
N(:, 1) = rotquat(M(:, 1), q);
N(:, 2) = rotquat(M(:, 2), q);
N(:, 3) = rotquat(M(:, 3), q);
N(:, 4) = rotquat(M(:, 4), q);
N(:, 5) = rotquat(M(:, 5), q);
N(:, 6) = rotquat(M(:, 6), q);
N(:, 7) = rotquat(M(:, 7), q);
N(:, 8) = rotquat(M(:, 8), q);
Cubeplot(N');

q = [0 1 0 0]';
[u, phi] = quat2euleruphi(q)
R = euleruphi2matrix(u, phi)
N = R*M;
Cubeplot(N');

u = [1, 0, 0];
phi = 90;
r = euleruphi2rotvec(u, phi)
[u, phi] = rotvec2euleruphi(r)
R = euleruphi2matrix(u, phi)
N = R*M;
Cubeplot(N');

%
%% Exercise 2
% Create a function that:
%
% *  Given {a rotation matrix or Euler rotation angles
%    or principal Euler axis/angle or quaternion or rotation vector},
%    returns {a rotation matrix and Euler rotation angles
%    and principal Euler axis/angle and quaternion and rotation vector}
%
% Hint: use a letter 'r,e,p,q,v' to inform the function which are the
%       input arguments. 
%

disp("EX2")
R = [0 0 -1; 0 1 0; 1 0 0];
[R, eulerangles, euleruphi, quaternion, rotvec] = rotation_change(R, 'r')

roll = 0;
pitch = 90;
yaw = 90;
[R, eulerangles, euleruphi, quaternion, rotvec] = rotation_change([roll, pitch, yaw]', 'e')

u = [0 0 -1]';
phi = 90;
[R, eulerangles, euleruphi, quaternion, rotvec] = rotation_change([u; phi], 'p')

q = [0 0 1 0]';
[R, eulerangles, euleruphi, quaternion, rotvec] = rotation_change(q, 'q')

u = [-1 0 0]';
phi = 180;
r = euleruphi2rotvec(u, phi);
[R, eulerangles, euleruphi, quaternion, rotvec] = rotation_change(r, 'v')