x = 0:pi/4:2*pi;
v = sin(x);
xq =1:0.1:2*pi;
figure
vq1 = interp1(x,v,xq);
plot(x,v,'o',xq,vq1,':.');
xlim([0 2*pi]);