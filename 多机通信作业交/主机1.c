#include <reg51.h>
#define NODE1_ADDR 1
#define NODE2_ADDR 2

sbit LED1=P3^6;
sbit LED2=P3^7;
unsigned char num[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

void display1(unsigned ch){
	if((ch>=48)&&(ch<=57)) P0=num[ch-48];
	else if((ch>=65)&&(ch<=70)) P0=num[ch-55];
}
void display2(unsigned ch){
	if((ch>=48)&&(ch<=57)) P2=num[ch-48];
	else if((ch>=65)&&(ch<=70)) P2=num[ch-55];
}
void delay(unsigned int time){
	unsigned char i, j;
	for(i=0; i<130; i++)
	       for(j=0; j<time; j++);
}

void main(){
	SCON=0xf0;
	TMOD=0x20;
	TH1=TL1=0xfd;
	TR1=1;
	ES=1;
	EA=1;
	while(1);
}

void receive()interrupt 4{
	RI=0;
	if(RB8==1){
		switch(SBUF){
			case 1:
				SM2=0;
			  LED1=!LED1;
			  delay(20);
			 // return;
			  display1(SBUF);
			  break;
			case 2:
				SM2=0;
			  LED2=!LED2;
			  delay(20);
			 // return;
			  display2(SBUF);
			  break;
		}
		/*if(SBUF==NODE1_ADDR){
			SM2=0;
			LED1=!LED1;
		}
		else if(SBUF==NODE2_ADDR){
			SM2=0;
			LED2=!LED2;
		}
		return;*/
	}
	SM2=1;
}












