clear all;
close all;
a=[];
ba=[];
c=[];
d=[];
a1=[];
b1=[];
c1=[];
d1=[];
a2=[];
b2=[];
c2=[];
d2=[];

b=Bluetooth('HC-06',1);
fopen(b);
x=1
b.ReadAsyncMode = 'continuous';
while(x<400)
if(b.BytesAvailable>=7)
        a1(x)=fread(b,1,'char');
        a2(x)=fread(b,1,'char');
        b1(x)=fread(b,1,'char');
        b2(x)=fread(b,1,'char');
        c1(x)=fread(b,1,'char');
        c2(x)=fread(b,1,'char');
        d1(x)=fread(b,1,'char');
        d2(x)=fread(b,1,'char');
        e1(x)=fread(b,1,'char');
        e2(x)=fread(b,1,'char');
%         f1(x)=fread(b,1,'char');
%         f2(x)=fread(b,1,'char');
        x=x+1
end
end
x
for(x=1:size(b1,2))
    a(x,1)=a2(x)*256+a1(x);
    a(x,2)=b2(x)*256+b1(x);
    a(x,3)=c2(x)*256+c1(x);
    a(x,4)=d2(x)*256+d1(x);
    a(x,5)=e1(x);
    a(x,6)=e2(x)-20;
%     a(x,6)=f2(x)*256+f1(x);
end

subplot(4,1,1)
plot(a(:,5),a(:,1));
subplot(4,1,2)
plot(a(:,5),a(:,2));
subplot(4,1,3)
plot(a(:,5),a(:,3));
subplot(4,1,4)
plot(a(:,5),a(:,4));
figure()
plot(a(:,5),a(:,6));
grid on;
% subplot(4,1,1)
% plot(a(:,1));
% subplot(4,1,2)
% plot(a(:,2));
% subplot(4,1,3)
% plot(a(:,3));
% subplot(4,1,4)
% plot(a(:,4));
% figure()
% plot(a(:,5),a(:,6));

fclose(b);
delete(b);