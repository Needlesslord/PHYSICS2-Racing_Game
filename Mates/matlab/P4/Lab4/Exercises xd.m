%% Exercise 1
% The point p has coordinates
p_A = [3, 4]';
% on a frame A and coordinates
p_B = [-2.5, 0.5]';
% on a frame B

%It is known that the angle between x axis of frame {A} and the y axes from
%Frame{B} is 30 deg counterclockwise.

% 1.1 Which are the coordinates of the origin of A seen from B?
% 1.2 Which are the coordinates of the origin of B seen from A?
% 1.3 Which are the coordinates of a point q expressed in A if
q_B = [3,1]'; %?

%% Exercise 2

% Let {A}, {B} and {C}, be 3 different reference frames. From them we know
% that:
%      - The origin of B with respect A is
oAB = [3,1,-2]';
%      - The origin of C with respect B is
oBC = [-3, 1,-2]';

% The three frames has different orientations in space.
% In fact:
%       -The set of Euler angles stored in eta as eta = (psi,theta,phi)
eta = [25;145;30]; % Expressed in degrees
%            represents 3 consecutive rotations about z, y, and x
%            respectively that allows to transform from {A} to {B}
%
%       - The quaternion
q = 1/7*[-sqrt(3)*3.5;3;-1;-1.5];
%         will allows to express in {B} a vector defined in {C}, if {C} and {B}
%         had the same origin

%   -Let in addition v1 and v2 to be points which coordinates are known in
%   {C}.
v1_C = [0;2;0];
v2_C = [0;2;5];

% With the information provided above determine:
%
%   2.1- The affine expression (no matrix here!) that allows to relate a vector originally given
%       in {C} to {B}.
%
%   2.2 The affine matrix that allows to express a vector originally given
%       in {C} to {A}.
%
%   2.3 The vectors v1_C and v2_C forms a segment. Make a 3d plot (plot3() in
%   matlab), representing how the segment is seen on {A} in red, on {B} in
%   blue and on {C} in green.

% Make use of the provided function quatmult to multiply quaternions.


%% Exercise 3.

% The points described by the columns of the matrix A
 
A = load('AEx3.mat');
A = A.A;

% are points contained into a circle, and they are defined in a world frame W.

% A camera is situated at point

cc = [1; 6; 1];

% defined in the world frame. Moreover the orientation of this camera frame
% is achieved by rotating the world frame -90 degs about its y axis followed by -20
% degrees about the resulting z axis.

%If the camera has a focal length of 1/34 m:

% 3.1 Make a plot with the view of the points of the circle projected into the camera plane.
%
% 3.2 Make also a 3D plot where all the scene is drawn in the world
% coordinates. The scene must contain the 2 reference frames (2 orthogonal sets of vectors)
% and the circle points. You can use the provided function cameraproj.


%% Exercise 4

%The columns of the next matrix, represents the coordinates od 4 points
%defined in a world frame.

A = load('AEx4.mat');
A = A.A;

%From this 4 points, two segments are defined. The segment one, goes from
% the point defined by the first column to the point defined by the second
% column. The second segment is defined by the other two points.

% A camera frame is seeing the scene. The origin of the world frame seen
% from the camera frame is given by the vector

wc = [4.665;3.735;-0.5395];


%And the orientation of the camera frame is obtained after rotating the
%world frame -170 degs about the direction
u = [0.01;-.2;1];


% With the data provided determine:
%
% 4.1 The minimum angle that both segments forms (hint, they intersect)
%
% 4.2 The angle that both segments forms in the image plane
%
% 4.3 Deliver a 3D representation of the scene with all the coordinates
% refered to the world frame
%
% 4.4 Deliver the 3D scene representations but with all the coordinates
% refered to the camera frame


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% (c)p(b) -> p se ve desde (b) para pasar a (c)
%
% (cp)p -> p proyectado en el plano de la cámara
% (cp)p = ( X/Z * f; Y/Z * f) -> X,Y,Z posición del punto en referencia de la cámara (c), f distancia focal (distancia del origen de C al plano)
%
% Transformaciones:
% Matriz:
% R1   R2   R3   t1       (           )  ( )
% R4   R4   R6   t2       (     R     )  (t)
% R7   R8   R9   t3   =   (           )  ( )
% 0    0    0    1         0    0    0    1
%
% x' = Rx + t
%
% donde R es una rotación (matriz), t una traslación (distancia, d)
%
% inverse:
% (           )  ( )
% ( R transp  )  (*)
% (           )  ( )
%  0    0    0    1 
%
% * -R transp * t
%
% to translate a vector x we need the augmented vector ^x = (x, 1)
%
% ^x' = 
%  1   0   0   t1       x1
%  0   1   0   t2       x2
%  0   0   1   t3   *   x3
%  0   0   0   1        1
%
% to translate a vector x we need the augmented vector ^x = (x, 1)
%
% ^x' = 
% R1   R2   R3   0       x1
% R4   R4   R6   0       x2
% R7   R8   R9   0   *   x3
% 0    0    0    1       1
%
% (a)p = (a)R(b)*(b)p + (a)d(a->b); p en (a) = rot de (b) a (a) * p en (b) + displacement de (a) a (b) en (a)
%
% (a)p = (a)R(b)*(b)p + (a)d(a->b) -> (b)p = (a)R^(-1)(b) * ((a)p - (a)d(a->b)) - > (b)p = (a)R^(-1)(b) * (a)p - (a)R^(-1)(b) * (a)d(a->b)
%
% llavors:
% (a)R^(-1)(b) = (a)(R transpo)(b) = (b)R(a) 
% -(b)R(a) * (a)d(a->b) = (b)d(b->a)
%
%
% Matriu és rot si det(A) = 1, A=A^(-1) o A*Atransp = Atransp*A = I
%
% Inv amb gauss:
%
% (A | I) ~ (I | Ainv)
%
% Posibles rotaciones:
%
% Rot matrix
% Euler axis (vec) + ang
% rot vec
% euler ang
% quaternions
%
% quaternion (vec de 4 componentes)
% ºq = (q0 q1 q2 q3); q0 es la scalar part, q es la vector part
% tiene conjugado:
% ~ºq = (q0 -q1 -q2 -q3)
%
% producto de quaterniones:
% ºq*ºp = ( q0*p0 - qtrasp*p ; q0*p + p0*q + (qxp) ) -> (qxp) producte vectorial
%
% quaternion matrices:
%
% ºQ = ºq = ( q0 -q1 -q2 -q3 ; q1 q0 -q3 q2 ; q2 q3 q0 -q1 ; q3 -q2 q1 q0 ) 
% se pueden multiplicar tal cual las matrices de quaterniones
%
% tienen norma:
% ||ºq||^(2) = ºq*~ºq = q0^(2) + qtraspo*q
%
% pure quaternion: q0 = 0 ; identity quaternion = (1 0 0 0); 
%
% Matriz rot quaternion R(ºq):
% q0^2+q1^2-q^2-q3^2   2q1q2-2q0q3           2q1q3+2q0q2
% 2q1q2+2q0q3          q0^2-q1^2-q2^2-q3^2   2q2q3-2q0q1
% 2q1q3-2q0q2          2q2q3+2q0q1           q0^2-q1^2-q2^2+q3^2
%
% w = R(ºq)*v ; w is vector v rotated
%
% ºq = ( cos(ang/2) ; u*sin(ang/2) ) ; if ||u|| = 1
%
% també: w = ºq*ºv*~ºq 
% 2 rot de quatern seguides es poden fer amb ºq*ºp
%
% Rtrasp(ºq) = Rinv(ºq) ; w = R(ºq)*v ; v = Rtrasp(ºq)w ; Q(~ºq) = Q(ºq)trasp ; ~Q(~ºq) = ~Q(ºq)trap
%
% traza = suma comp diagonal matriz
%
% euler matrix: la columna que sigui (0 ; 1 ; 0) és la que està relacionada amb cada angle en qüestió (angle de rotació, i n'hi ha tres, cada columna és z y x*) *no n'estic segura
%
% para más fórmulas, mira los matlabs, que también tienen fórmulas en sí, así como procedimientos. Yo ya no sé qué más poner.
%
%
%
%
%
%
%
%
%
%
%
%
%
%
%
%

