s=serial('COM3');
set(s,'BaudRate',9600,'DataBits', 8, 'Parity', 'none','StopBits', 1, 'FlowControl', 'none','Terminator','CR');
set(s,'Timeout',1);
a=scanf(s);