cord =  xlsread('cord');
ielmn = xlsread('ielmn'); 
disp = xlsread('displacements'); 
defcord = zeros(451,2); 

for j = 2:3
    for k = 1:451
       defcord(k,(j-1)) = (cord(k,(j-1))) + ((disp(k,j))/5000);
    end
end


for i = 1:length(ielmn)
    xu = [cord(ielmn(i,1),1),cord(ielmn(i,2),1)];
    yu = [cord(ielmn(i,1),2),cord(ielmn(i,2),2)];
    plot(xu,yu,'k'); hold on;
    xlim([0 10.5]);
    ylim([-.5 1.5]);

    xd = [defcord(ielmn(i,1),1),defcord(ielmn(i,2),1)];
    yd = [defcord(ielmn(i,1),2),defcord(ielmn(i,2),2)];
    plot(xd,yd,'c'); hold on;
end


for i = 1:length(ielmn)
    xu = [cord(ielmn(i,2),1),cord(ielmn(i,3),1)];
    yd = [cord(ielmn(i,2),2),cord(ielmn(i,3),2)];
    plot(xu,yd,'k'); hold on;

    xd = [defcord(ielmn(i,2),1),defcord(ielmn(i,3),1)];
    yd = [defcord(ielmn(i,2),2),defcord(ielmn(i,3),2)];
    plot(xd,yd,'c'); hold on;
end


for i = 1:length(ielmn)
    xu = [cord(ielmn(i,3),1),cord(ielmn(i,4),1)];
    yu = [cord(ielmn(i,3),2),cord(ielmn(i,4),2)];
    plot(xu,yu,'k'); hold on;

    xd = [defcord(ielmn(i,3),1),defcord(ielmn(i,4),1)];
    yd = [defcord(ielmn(i,3),2),defcord(ielmn(i,4),2)];
    plot(xd,yd,'c'); hold on;
end


for i = 1:length(ielmn)
    xu = [cord(ielmn(i,4),1),cord(ielmn(i,1),1)];
    yu = [cord(ielmn(i,4),2),cord(ielmn(i,1),2)];
    plot(xu,yu,'k'); hold on;

    xd = [defcord(ielmn(i,4),1),defcord(ielmn(i,1),1)];
    yd = [defcord(ielmn(i,4),2),defcord(ielmn(i,1),2)];
    plot(xd,yd,'c'); hold on;
end

title('Cantilever Beam subjected to Distributed Load and Force at tip')
xlabel('Non-Dimensional Displacements in the x')
ylabel('Non-Dimensional Displacements in the y')
legend('Undeformed','Deformed')




