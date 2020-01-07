function [ r ] = quatmult( p,q )
% [ r ] = quatmult( p,q )
%   quatmult performs the quaternion multiplication of p by q.
%   p and q must be 4x1 arrays;

 r = [p(1)*q(1) - p(2)*q(2) - p(3)*q(3) - p(4)*q(4);
 p(1)*q(2) + p(2)*q(1) + p(3)*q(4) - p(4)*q(3);
 p(1)*q(3) + p(3)*q(1) - p(2)*q(4) + p(4)*q(2);
 p(1)*q(4) + p(2)*q(3) - p(3)*q(2) + p(4)*q(1)];
 
 
end

