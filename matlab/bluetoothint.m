% clear;
% q=zeros(10,1000);
% qq=zeros(10,1000);
% qqq=zeros(10,1000);
% time=zeros(10,1000);
% jakos=zeros(10,2);
i=1;
j=1;
b=Bluetooth('HC-06',1);


fopen(b);


b.ReadAsyncMode = 'continuous';
%flagi
checkone1 = 0;
checkzero1 = 0;
checkzero2 = 0;
receivedLSB = 0;
receivedMSB = 0;
MSB = 0;
LSB = 0;
val = 0;
while(1 == 1)
    while(b.BytesAvailable < 1)
    end
    while(b.BytesAvailable >= 1)
        temp=fread(b,1,'char');
        if(receivedMSB == 0 && receivedLSB == 1)
            %czynnosci starszy bit
            MSB = temp;
            val = MSB * 256 + LSB;
            val
            %otrzymanie nowej liczby - kasowanie flag
            checkone1 = 0;
            checkzero1 = 0;
            checkzero2 = 0;
            receivedLSB = 0;
            receivedMSB = 0;
            continue;
        end
        'uuuu1';
        if(receivedLSB == 0 && checkzero2 == 1)
            LSB = temp;
            receivedLSB = 1; 
            continue;
        end
        
            'uuuu2';
        if(checkzero2 == 0 && checkzero1 == 1)
            if(temp == 0)
                checkzero2 = 1;
                continue;
            else
               %Otrzymana liczba nie jest zerem (nadal moze byc jedynka)
               checkone1 = 0;
               checkzero1 = 0;
               checkzero2 = 0;
               receivedLSB = 0;
               receivedMSB = 0; 
            end
        end
        
            'uuuu3';
        if(checkzero1 == 0 && checkone1 == 1)
            if(temp == 0)
                checkzero1 = 1;
                continue;
            else
               %Otrzymana liczba nie jest zerem (nadal moze byc jedynka)
               checkone1 = 0;
               checkzero1 = 0;
               checkzero2 = 0;
               receivedLSB = 0;
               receivedMSB = 0; 
            end
        end
        if(checkone1 == 0)
            if(temp == 1)
                checkone1 = 1;
            end
        end
    end

    j = j + 1;
end
fclose(b);
delete(b);