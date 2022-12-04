#include<reg51.h>
sbit sensor=P1^0;
sbit rs=P1^1;
sbit rw=P1^2;
sbit en=P1^3;
sbit buzzer=P3^0;
void lcdinit();                //initialize the lcd
void lcddat(unsigned char);    // passing character with this unsigned character
void lcdcmd(unsigned char);    // for command purpose with arguments
void lcddis(unsigned char *);  // text to display on lcd by string pointer
void delay();                  // since user defined function thats why
void main()
{
	buzzer=0;                     // initial buzzer state
	sensor=0;
	back:lcdinit();               //to initialize the lcd
	lcddis(" FIRE ALERT ");       // Display the text on lcd
	lcdcmd(0xc0);                 //to force the command to second line
	lcddis("  SYSTEM  ");         // To display in second line in lcd
	delay();                      // waiting sometime to display the message on lcd
	while(1)
	{
		if(sensor==1)               //sensor value in vice versa with line 15
		{
			lcdcmd(0x01);             // clear the lcd
			lcddis("FIRE DETECTED");  //MESSAGE ON SCREEN
			buzzer=1;                 //buzzer turned on
		}
		goto back;                  //to go again from line16
	}
}                          // need to give all description of the function which is used
void lcdinit()             //lcd initialization fucntion called in main
{ 
	lcdcmd(0x38);             //to send the command
	lcdcmd(0x01);             // clear the screen
	lcdcmd(0x10);             // shift cursor right 
	lcdcmd(0x0c);             // Display cursor on blinking
	lcdcmd(0x80);
}
void lcdcmd(unsigned char val)   // take the command from lcd initialization function
{
	P2=val;  // lcd is connected to port2
	rs=0;
	rw=0;
	en=1;
	delay();
	en=0;
}
void lcddat(unsigned char dat)
{
	P2=dat;
	rs=1;
	rw=0;
	en=1;
	delay();
	en=0;
}
void lcddis(unsigned char *s)
{
	unsigned char w;
	for(w=0;s[w]!='\0';w++)
	{
		lcddat(s[w]);
	}
}
void delay()
{
	unsigned int v1;
	for(v1=0;v1<10000;v1++);
}