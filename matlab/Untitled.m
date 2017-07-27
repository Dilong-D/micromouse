wykres(1:1000)=1;
for i=1:1:1000
    wykres(i)=(odp1(i,1)+odp2(i,1)+odp3(i,1)+odp4(i,1)+odp5(i,1))/5;
end
figure(1)
plot(a(:,2),a(:,1),b(:,2),b(:,1),1:1:1000, odp1,1:1:1000, odp2,1:1:1000, odp3,1:1:1000, odp4,1:1:1000, odp5);
xlim([0 150])

figure(2)
plot(a(:,2),a(:,1),b(:,2),b(:,1),1:1:1000, wykres);
xlim([0 50]);

figure(3)
plot(a(:,2),a(:,1),b(:,2),b(:,1)-1,1:1:500, odp1rot);
xlim([0 50]);

figure(4)
plot(1:1:1500, jazda1,1:1:1500, jazda2);
xlim([0 1500]);