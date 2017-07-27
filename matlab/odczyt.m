clear all;
close all;

b=Bluetooth('HC-06',1);
fopen(b);
x=0
b.ReadAsyncMode = 'continuous';
while(x<1)
if(b.BytesAvailable>=2)
        
        q1=fread(b,1,'char');
        q2=fread(b,1,'char');
        x=2;
end
end

fclose(b);
delete(b);