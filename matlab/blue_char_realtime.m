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
        x=x+1
        q1(x)=fread(b,1,'char')-100;
        q2(x)=fread(b,1,'char')-50;
        drawnow;
        plot(q1,'r--o','linewidth',1)
        grid on;
        hold on;
        plot(q2,'b--o','linewidth',1)
    end 
    end
    plot(q1,'r--o','linewidth',1)
    grid on;
    hold on;    
    plot(q2,'b--o','linewidth',1)
    title({['srednia sum=' num2str(sum(q1)/200)];['roznica roz=' num2str(sum(q2)/200)]})
    legend('q1','q2')
    j=j+1;
    
end


fclose(b);
delete(b);
