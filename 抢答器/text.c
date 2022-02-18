#include<reg51.h>
static unsigned char num[8]={0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80};
void EXINT0() interrupt 0
{
	switch(P2){
		case 0xfe: P1=0xfe,P0=num[0]; break;
		case 0xfd: P1=0xfd,P0=num[1]; break;
		case 0xfb: P1=0xfb,P0=num[2]; break;
		case 0xf7: P1=0xf7,P0=num[3]; break;
		case 0xef: P1=0xef,P0=num[4]; break;
		case 0xdf: P1=0xdf,P0=num[5]; break;
		case 0xbf: P1=0xbf,P0=num[6]; break;
		case 0x7f: P1=0x7f,P0=num[7]; break;
	}
	P3=0xff;
}

void main()
{
	P1=0xff;
	P2=0xff;
	P0=0xff;
	while(1){
	while(1){
		if(P3==0xfe){
		EA=1;
	  EX0=1;
	  IT0=1;
		P3=0x05;
		P1=0xff;
	  P2=0xff;
	  P0=0xff;
	  }
		if(P1!=0xff){
			EA=0;
			EX0=0;
			P3=0xff;
			break;
		}
	}
}
}
