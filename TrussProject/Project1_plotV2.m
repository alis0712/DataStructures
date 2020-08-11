
%%
%Syed Ali ENME815 Truss Project 1
%%

cord = importdata('cordxy.txt');
ielmn = importdata('ielmnxy.txt');
disp = importdata('displace.txt');
deformed_cord = zeros(82,2);

for l = 2:3 %Calling Rows 2 and 3 in the Element Connectivity Matrix
    for m = 1:82 %From nodes 1-82
       deformed_cord(m,(l-1)) = (cord(m,l)) +  ((disp(m,l))/600);
    end
end

figure; grid on;
set(gca,'Fontsize',20);
for i = 1:length(ielmn)
    x = [cord(ielmn(i,2),2),cord(ielmn(i,3),2)];
    y = [cord(ielmn(i,2),3),cord(ielmn(i,3),3)];
    plot(x,y,'k'); hold on;
    xlim([0 2.5]);
    ylim([-.25 .5]);

    xd = [deformed_cord(ielmn(i,2),1),deformed_cord(ielmn(i,3),1)];
    yd = [deformed_cord(ielmn(i,2),2),deformed_cord(ielmn(i,3),2)];
    plot(xd,yd,'r--'); hold on;
    title('Deformed and undeformed 82 noded Truss')
    xlabel('non-dimensional Length')
    ylabel('Non-dimensional Height')
    legend('Undeformed Truss', 'Deformed Truss')
end