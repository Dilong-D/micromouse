clear;
close all;
q=zeros(10,1000);
u=zeros(10,1000);
qqq=zeros(10,1000);
time=zeros(10,1000);
jakos=zeros(10,2);
i=1;
j=1;
b=Bluetooth('HC-06',1);

fopen(b);


b.ReadAsyncMode = 'continuous';
while(j<2)
    if(b.BytesAvailable>=1 && i<1001)
        temp=fread(b,1,'char');
        if i==1
        u(j,i)=0;
        elseif (i<200)||(i>400 && i<600)||(i>800 && i<1001)
        u(j,i)=50;
        else
           u(j,i)=20; 
        end
        q(j,i)=temp;
        i=i+1;
    end
    if (i==1001)
        x = 1:1000;
        v = q(j,:);
        xq =1:0.25:1000;
        figure('units','normalized','outerposition',[0 0 1 1])
        vq1 = interp1(x,v,xq);%,'spline');
        plot(x,v,'o',xq,vq1,':.');
        hold on
        %plot(1:1000,u(j,:));
        %plot(1:200,q(j,:),'o-',1:200,time(1,:),'o-',1:200,time(1,:),'o-')
        xlim([0 1000])
        %ylim([50 150])
        drawnow;
        j=j+1;
        i=1;
    end
    
end
fclose(b);
delete(b);
data=[q(1,:);u(1,:)];