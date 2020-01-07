function Cubeplot(M)
    
    x = M(:,1);
    y = M(:,2);
    z = M(:,3);
   
%    trisurf(tri,M(:,1),M(:,2),M(:,3), )
   
con = [1 2 3 4;
       5 6 7 8;
       4 3 7 8;
       1 2 6 5;
       1 4 8 5;
       2 3 7 6]';
   
   x = reshape(x(con(:)),[4,6]);
   y = reshape(y(con(:)),[4,6]);
   z = reshape(z(con(:)),[4,6]);
     
    c = 1/255*[255 248 88;
               0 0 0;
               57 183 225;
               57 183 0;
               255 178 0;
               255 0 0];
    
    
figure1 = figure('Color',[1 1 1]);
PS=get(figure1,'PaperPosition');
PS(1)=0;
PS(2)=0;
PS(3)=PS(3)*.5;
PS(4)=PS(4)*.5;
set(figure1,'PaperPosition',PS);
% Create axes

axes1 = axes('Parent',figure1,...
    'YMinorGrid','off','YGrid','on',...
    'XMinorGrid','off','XGrid','on',...
    'ZMinorGrid','off','ZGrid','on',...
    'GridLineStyle',':','MinorGridLineStyle',':',...
    'XColor',[0.25,0.25,0.25],...
    'YColor',[0.25,0.25,0.25],...
    'ZColor',[0.25,0.25,0.25],...
    'xlim', [-2,2],...
    'ylim', [-2,2],...
    'zlim', [-2,2],...
    'Projection','perspective',...
    'CameraViewAngle',11.8382759031214,...
    'CameraUpVector',[-0.25 0.4 0.87],...
    'CameraTarget',[0.15 0 -0.3],...
    'CameraPosition',[14.45 -26.65 16.6],...
    'DataAspectRatio',[1 1 1],...
    'FontSize',16);
    box(axes1,'on');
hold(axes1,'all');

    h = fill3(x,y,z, 1:6);
    
    for q = 1:length(c)
        h(q).FaceColor = c(q,:);
    end
    
   xlabel('$x$','Interpreter','latex');
   ylabel('$y$','Interpreter','latex');
   zlabel('$z$','Interpreter','latex');
    
    
    
    
    