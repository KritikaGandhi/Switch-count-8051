// COUNT NUMBER OF TIMES SWITCH IS PRESSED AND DISPLAY COUNT NUMBER ON SCREEN 


#include<reg52.h> 
sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;
sbit count_t0=P3^4;                      //COUNTER 

void command(unsigned int comvalue);
void senddata(unsigned int datavalue);
void delay(unsigned int time);
unsigned char i;
unsigned int cnt_value;

void main()
{
command(0x38);                          //7*5 matrix created
command(0x0E);                         //screen display on
command(0x01);                         // clr screen
	
	TMOD=0X06;                           // COUNTER 0,MODE 2 
	count_t0=1;                          //input pin set
	while(1)
		
	{
	TH0=0X00;
		TL0=0X00;
		TR0=1;                              //COUNTER RUN ON
		while(!TF0)                        // WHILE TF0=0 CONTINUE
		{
		command(0x80);                    // 1st line
			cnt_value=TL0;
			i=cnt_value/10;                 //10s place calculate
			senddata(i+0x30);               //ascii value send 
			
			i=cnt_value%10;                //0s place
			senddata(i+0x30);              //ascii
			
			if(cnt_value==99)
			{break;
			}
			
			
		}
	TF0=0; 
		TR0=0;
	}
}

void command(unsigned int comvalue)
{
P1=comvalue;
RW=0;
	RS=0;
	E=1;
	delay(10);
	E=0;
}
void senddata(unsigned int datavalue)
{
P1=datavalue;
	RW=0;
	RS=1;
	E=1;
	delay(10);
	E=0;
	
}
void delay(unsigned int time)
{
unsigned int i,j;
	for(i=0;i<time;i++)
	{for(j=0;j<113;j++);}
}
