function h = Cubeplot2(M)

if nargin<1
    M = [ -1  -1 1;   %Node 1
        -1   1 1;   %Node 2
        1   1 1;   %Node 3
        1  -1 1;   %Node 4
        -1  -1 -1;  %Node 5
        -1   1 -1;  %Node 6
        1   1 -1;  %Node 7
        1  -1 -1]; %Node 8
end
x1 = M(:,1);
y1 = M(:,2);
z1 = M(:,3);

%    trisurf(tri,M(:,1),M(:,2),M(:,3), )

con = [1 2 3 4;
    5 6 7 8;
    4 3 7 8;
    1 2 6 5;
    1 4 8 5;
    2 3 7 6]';

x = reshape(x1(con(:)),[4,6]);
y = reshape(y1(con(:)),[4,6]);
z = reshape(z1(con(:)),[4,6]);

c = 1/255*[255 0 0;
    255 171 0;
    0 170 0;
    0 170 255;
    255 255 255;
    255 255 0];

%Create axes

axes1 = axes('YMinorGrid','off','YGrid','on',...
    'XMinorGrid','off','XGrid','on',...
    'ZMinorGrid','off','ZGrid','on',...
    'GridLineStyle',':','MinorGridLineStyle',':',...
    'XColor',[0.5,0.5,0.5],...
    'YColor',[0.5,0.5,0.5],...
    'ZColor',[0.5,0.5,0.5],...
    'xlim', [-2,2],...
    'ylim', [-2,2],...
    'zlim', [-2,2],...
    'Projection','perspective',...
    'DataAspectRatio',[1 1 1],...
    'FontSize',15);
view(axes1,[-61.0361328125 24.8255859375]);

box(axes1,'off');
hold(axes1,'all');

h = fill3(x,y,z, 1:6);

 for q = 1:length(c)
     h(q).FaceColor = c(q,:);
 end

xlabel('$x$','Interpreter','latex');
ylabel('$y$','Interpreter','latex');
zlabel('$z$','Interpreter','latex');
drawnow limitrate;






