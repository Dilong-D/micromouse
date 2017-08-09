figure()
x1=1;
x2=3;
y1=1;
y2=1;
lab[][];
for x=1:sizeof(lab,1)
    for y=1:sizeof(lab,2)
        x1=x-0.5;
        x2=x+0.5;
        y1=y-0.5;
        y2=y-0.5;
        line([x1 x2],[y1 y2],'Color','g')
        hold on
    end
end