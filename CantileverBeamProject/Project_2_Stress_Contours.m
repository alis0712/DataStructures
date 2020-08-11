for i = 1:1600
    sigma(i,1) = i;
end
sigma2 = zeros(451,2);
cord = zeros(451,2);

cord2 = xlsread('stresses');
sigma(:,2) = cord2(:,3);
dx = 10/40;
dy = 1/10;

p = 1;
for i = 0:40
    for j = 0:10
    cord(p,1) = 0+dx*i;
    cord(p,2) = 0+dy*j;
    p=p+1;
    end
end

j = [1;4;8;12;16;20;24;28;32;36;40];
k = [1562;1566;1570;1574;1578;1582;1586;1590;1594;1598;1599];
l = [441;442;443;444;445;446;447;448;449;450;451];

q = 1;
for i = 1:40;
    for p = 1:11
    sigma2(q,2) = sigma(j(p)+40*(i-1),2);
    q = q+1;
    end 
end

    for p = 1:11
    sigma2(l(p),2) = sigma(k(p),2);
    end 

for i = 1:451
    sigma2(i,1) = i;
end


x=min(cord(:,1)):(max(cord(:,1))-min(cord(:,1)))/200:max(cord(:,1));
y=min(cord(:,2)):(max(cord(:,2))-min(cord(:,2)))/200:max(cord(:,2));

[X, Y] = meshgrid(x,y);
Z =griddata(cord(:,1),cord(:,2),sigma2(:,2),X,Y);
contour(X,Y,Z,100)
title('Non-Dimensional Stress Contours')
xlabel('Non-dimenisonal Displacements in x')
ylabel('Nondimensional Displacements in Y')
