clear all;
close all;

b=Bluetooth('HC-06',1);
fopen(b);
b.ReadAsyncMode = 'continuous';

j=1;
while(j<2)
    x=0
    q1=[];
    q2=[];
    figure(j)
    while(x<200)
    
    if(b.BytesAvailable>=2 && x<201)
        x=x+1;
        q1(x)=fread(b,1,'char');
        q2(x)=fread(b,1,'char');
        drawnow;
        plot(q1,q2,'r--o','linewidth',1)
        grid on;
        hold on;
    end 
    end
    j=j+1;
    
end


fclose(b);
delete(b);
