#include <reg51.h>
sbit key1=P1^0;
sbit key2=P1^1;
sbit key3=P1^2;
sbit key4=P1^3;
sbit ns_green=P2^0;
sbit ew_green=P2^3;
sbit ns_yellow=P2^1;
sbit ew_yellow=P2^4;
sbit ns_red=P2^2;
sbit ew_red=P2^5;
sbit red_1=P3^0;
sbit red_2=P3^1;
sbit buzzer=P3^5;
sbit set=P3^2;
sbit plus=P3^6;
sbit minus=P3^7;
unsigned char flag_buzzer=0, flag_green_ns=0, flag_green_ew=0, flag_yellow_ns=0, flag_yellow_ew=0;
unsigned char flag_setting1=0,flag_setting2=0,flag_set=0;
unsigned char s[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xd8,0x80,0x90};
unsigned char n1=15,n2=15;
unsigned char timer_ns, timer_ew;


void delay(unsigned char a){    
	unsigned char i,j;
	while(a--){
		for(i=0;i<2;i++){
			for(j=0;j<122;j++);
		}
	}
}

void display(void){                         
	char a,b;
	a=timer_ns/10; b=timer_ns%10;
	key1=0; key2=0; key3=0; key4=0;
	P0=s[b];
	key2=1;
	delay(2);
	key2=0;
	P0=s[a];
	key1=1;
	delay(2);
	key1=0;
	a=timer_ew/10; b=timer_ew%10;	
	P0=s[b];
	key4=1;
	delay(2);
	key4=0;
	P0=s[a];
	key3=1;
	delay(2);
	key3=0;
}

void display_set(void){
  char a,b;
	a=n2/10; b=n2%10;
	key1=0; key2=0; key3=0; key4=0;
	P0=s[b];
	key2=1;
	delay(2);
	key2=0;
	P0=s[a];
	key1=1;
	delay(2);
	key1=0;
	a=n1/10; b=n1%10;	
	P0=s[b];
	key4=1;
	delay(2);
	key4=0;
	P0=s[a];
	key3=1;
	delay(2);
	key3=0;
}
void display_set1(void){
  char a,b;
	a=n1/10; b=n1%10;	
	P0=s[b];
	key4=1;
	delay(2);
	key4=0;
	P0=s[a];
	key3=1;
	delay(2);
	key3=0;
}

void display_set2(void){
  char a,b;
	a=n2/10; b=n2%10;
	key1=0; key2=0; key3=0; key4=0;
	P0=s[b];
	key2=1;
	delay(2);
	key2=0;
	P0=s[a];
	key1=1;
	delay(2);
	key1=0;
}

void EXINT0() interrupt 0{
	EX0=0;  delay(30); EX0=1;
	if(flag_set<2){
		if(flag_setting1==0){
			flag_setting1=1;
			flag_setting2=0;
		}
		else{
			flag_setting1=0;
			flag_setting2=1;
		}
		flag_set++;
	}
	else
		flag_set=0;
}

void timer0() interrupt 1
{
	static unsigned char i=0;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	i++;
	if(flag_set==0){
		if(i==10){
			if(flag_buzzer==1){
				buzzer=~buzzer;
			}
			if(flag_green_ns==1){
				ns_green=~ns_green;
			}
			if(flag_green_ew==1){
				ew_green=~ew_green;
			}
			if(flag_yellow_ns==1){
				ns_yellow=~ns_yellow;
			}
			if(flag_yellow_ew==1){
				ew_yellow=~ew_yellow;
			}
		}
		if(i==20){
			if(flag_buzzer==1){
				buzzer=~buzzer;
			}
			if(flag_green_ns==1){
				ns_green=~ns_green;
			}
			if(flag_green_ew==1){
				ew_green=~ew_green;
			}
			if(flag_yellow_ns==1){
				ns_yellow=~ns_yellow;
			}
			if(flag_yellow_ew==1){
				ew_yellow=~ew_yellow;
			}
			timer_ns=timer_ns-1;
			timer_ew=timer_ew-1;
			i=0;
		}
	}
	else{
		if(i<=10){
			display_set();
		}
		else if(i<20){
			if(flag_setting1==1){
				key3=0; key4=0;
				display_set2();
			}
			else{
				key1=0; key2=0;
				display_set1();
			}
		}
		else{
			i=0;
			display_set();
		}
	}
}

int main(void){
	P1=0x00;
	P0=0x00;
	timer_ns=n1;
	timer_ew=n1+3;
	
	EA=1;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	EA=1;
	EX0=1;
	IT0=1;
	ET0=1;
	TR0=1;
	
	while(1){
		P2=0x00;
		red_1=0;
	  red_2=0;
		buzzer=0;
		timer_ns=n1;
	  timer_ew=n1+3;
		TR0=1;
		while(flag_set){
			//display_set();
			if(flag_setting1==1){
				if(plus==0&&n1<20){
					while(!plus);
					n1++;
				}
				if(minus==0&&n1>10){
					while(!minus);
					n1--;
				}
			}
			else
				if(plus==0&&n2<20){
					while(!plus);
					n2++;
				}
				if(minus==0&&n2>10){
					while(!minus);
					n2--;
				}
		}
		while(timer_ns>3&&flag_set==0){
			display();
			ns_green=1;
			ew_red=1;
			red_2=1;
		}
		while(timer_ns>0&&flag_set==0){
			display();
			flag_buzzer=1;
			flag_green_ns=1;
		}
		flag_buzzer=0;
		flag_green_ns=0;
		timer_ns+=3;
		while(timer_ew>0&&flag_set==0){
			display();
			ns_green=0;
			red_1=1;
			flag_yellow_ns=1;
		}
		flag_yellow_ns=0;
		timer_ns=n2+3;
	  timer_ew=n2;
		P2=0x00;
		red_1=0;
	  red_2=0;
		while(timer_ew>3&&flag_set==0){
			display();
			ew_green=1;
			ns_red=1;
			red_1=1;
		}
		while(timer_ew>0&&flag_set==0){
			display();
			flag_buzzer=1;
			flag_green_ew=1;
		}
		flag_buzzer=0;
		flag_green_ew=0;
		timer_ew+=3;
		while(timer_ns>0&&flag_set==0){
			display();
			ew_green=0;
			red_2=1;
			flag_yellow_ew=1;
		}
		flag_yellow_ew=0;
	}
}	