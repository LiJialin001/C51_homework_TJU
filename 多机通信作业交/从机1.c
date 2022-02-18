#include <reg51.h>
#define NODE1_ADDR 1

unsigned char pointer_1=0;
unsigned char str[]={"0123456789ABCDEF"};
unsigned char num[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};

void display(unsigned char ch){
	if((ch>=48)&&(ch<=57)) P2=num[ch-48];
	else if((ch>=65)&&(ch<=70)) P2=num[ch-55];
}
void delay(unsigned int time){
	unsigned char i, j;
	for(i=0; i<130; i++)
	       for(j=0; j<time; j++);
}
void proc_key(unsigned char node_number){
	delay(200);
	TB8=1;
	SBUF=node_number;
	while(TI==0);
	TI=0;
	TB8=0;
  SBUF=str[pointer_1];
	display(str[pointer_1++]);
	if(pointer_1>=16)pointer_1=0;
	while(TI==0);
	TI=0;
}

void main(){
	SCON=0xe0;
	TMOD=0x20;
	TH1=TL1=0xfd;
	TR1=1;
	ES=1;
	EA=1;
	EX0=1;
	IT0=1;
	while(1);
}

void button1() interrupt 0{
	EX0=0;
	delay(20);
	EX0=1;
	proc_key(NODE1_ADDR);
}







