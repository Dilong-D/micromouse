x = 1:400;
v = q(8,:);
xq =1:0.25:400;
figure('units','normalized','outerposition',[0 0 1 1])
vq1 = interp1(x,v,xq);%,'spline');
plot(x,v,'o',xq,vq1,':.');
xlim([85 95])