#include <reg51.h>
#defind FREG 12000000
#defind SPEED 100 

sbit SPEAKER = P^2;

unsigned char *pmsc;

unsigned char tune_TH, tnue_TL;

unsigned char dura_TH, dura_TL;

unsigned char new_note;

unsigned char repeat;

unsigned char code musicdata[]={
	0x15,0x08, 0x13,0x04, 0x15,0x04, 0x21,0x0c,
	0x17,0x04, 0x16,0x08, 0x21,0x08, 0x15,0x10,
	0x15,0x08, 0x11,0x04, 0x12,0x04, 0x13,0x08,
	0x12,0x04, 0x11,0x04, 0x12,0x20,
	0x15,0x08, 0x13,0x04, 0x15,0x04, 0x21,0x0c,
	0x17,0x04, 0x16,0x08, 0x21,0x08, 0x15,0x10,
	0x15,0x08, 0x12,0x04, 0x13,0x04, 0x14,0x0c,
	0x07,0x04, 0x11,0x20,
	0x16,0x08, 0x21,0x08, 0x21,0x10, 0x17,0x08,
	0x16,0x04, 0x17,0x04, 0x21,0x10,
	0x16,0x04, 0x17,0x04, 0x21,0x04, 0x16,0x04,
	0x16,0x04, 0x15,0x04, 0x13,0x04, 0x11,0x04,
	0x12,0x20,
	0x15,0x08, 0x13,0x04, 0x15,0x04, 0x21,0x0c,
	0x17,0x04, 0x16,0x08, 0x21,0x08, 0x15,0x10,
	0x15,0x08, 0x12,0x04, 0x13,0x04, 0x14,0x0c,
	0x07,0x04,0x11,0x20,
	0x00,0x00
};

unsigned char code music_freq_tab[64]={
	0xff, 0xea,
	255-FREQ/24/131/256, 256-FREQ/24/131%256, 
	255-FREQ/24/147/256, 256-FREQ/24/147%256, 
	255-FREQ/24/165/256, 256-FREQ/24/165%256, 
	255-FREQ/24/175/256, 256-FREQ/24/175%256, 
	255-FREQ/24/196/256, 256-FREQ/24/196%256, 
	255-FREQ/24/221/256, 256-FREQ/24/221%256, 
	255-FREQ/24/248/256, 256-FREQ/24/248%256, 
	
	0xff, 0xea,
  255-FREQ/24/262/256, 256-FREQ/24/262%256, 
	255-FREQ/24/294/256, 256-FREQ/24/294%256,
	255-FREQ/24/330/256, 256-FREQ/24/330%256, 
	255-FREQ/24/350/256, 256-FREQ/24/350%256, 
	255-FREQ/24/393/256, 256-FREQ/24/393%256, 
	255-FREQ/24/441/256, 256-FREQ/24/441%256, 
	255-FREQ/24/495/256, 256-FREQ/24/495%256, 

  0xff, 0xea,
	255-FREQ/24/525/256, 256-FREQ/24/525%256, 
	255-FREQ/24/589/256, 256-FREQ/24/589%256, 
	255-FREQ/24/661/256, 256-FREQ/24/661%256, 
	255-FREQ/24/700/256, 256-FREQ/24/700%256, 
	255-FREQ/24/786/256, 256-FREQ/24/786%256, 
	255-FREQ/24/882/256, 256-FREQ/24/882%256, 
	255-FREQ/24/990/256, 256-FREQ/24/990%256, 

  0xff, 0xea,
  255-FREQ/24/1049/256, 256-FREQ/24/1049%256, 
	255-FREQ/24/1178/256, 256-FREQ/24/1178%256, 
	255-FREQ/24/1322/256, 256-FREQ/24/1322%256, 
	255-FREQ/24/1400/256, 256-FREQ/24/1400%256, 
	255-FREQ/24/1572/256, 256-FREQ/24/1572%256, 
	255-FREQ/24/1665/256, 256-FREQ/24/1665%256, 
	255-FREQ/24/1869/256, 256-FREQ/24/1869%256, 
};

unsigned char code music_frequp_tab[64]={
	0xff, 0xea,
	255-FREQ/24/139/256, 256-FREQ/24/139%256,
	255-FREQ/24/156/256, 256-FREQ/24/156%256,
	255-FREQ/24/175/256, 256-FREQ/24/175%256, 
	255-FREQ/24/185/256, 256-FREQ/24/185%256, 
	255-FREQ/24/208/256, 256-FREQ/24/208%256, 
	255-FREQ/24/234/256, 256-FREQ/24/234%256, 
	255-FREQ/24/262/256, 256-FREQ/24/262%256,

	0xff, 0xea,
	255-FREQ/24/278/256, 256-FREQ/24/278%256,
	255-FREQ/24/312/256, 256-FREQ/24/312%256, 
	255-FREQ/24/350/256, 256-FREQ/24/350%256, 
	255-FREQ/24/371/256, 256-FREQ/24/371%256, 
	255-FREQ/24/416/256, 256-FREQ/24/416%256, 
	255-FREQ/24/467/256, 256-FREQ/24/467%256, 
	255-FREQ/24/525/256, 256-FREQ/24/525%256,

	0xff, 0xea,
	255-FREQ/24/556/256, 256-FREQ/24/556%256, 
	255-FREQ/24/624/256, 256-FREQ/24/624%256, 
	255-FREQ/24/700/256, 256-FREQ/24/700%256, 
	255-FREQ/24/742/256, 256-FREQ/24/742%256, 
	255-FREQ/24/833/256, 256-FREQ/24/833%256, 
	255-FREQ/24/935/256, 256-FREQ/24/935%256, 
	255-FREQ/24/1049/256, 256-FREQ/24/1049%256, 
	
	0xff, 0xea,
	255-FREQ/24/1112/256, 256-FREQ/24/1112%256,
	255-FREQ/24/1248/256, 256-FREQ/24/1248%256, 
	255-FREQ/24/1400/256, 256-FREQ/24/1400%256, 
	255-FREQ/24/1484/256, 256-FREQ/24/1484%256,
	255-FREQ/24/1618/256, 256-FREQ/24/1618%256, 
	255-FREQ/24/1764/256, 256-FREQ/24/1764%256, 
	255-FREQ/24/1968/256, 256-FREQ/24/1968%256, 
};
	
void delay(unsigned int);
void music_play(void);

void main(void){
	TMOD=0x11;
	EA=1;
	ET0=1;
	ET1=1;
	TR0=0;
	TR1=0;
	repeat=10000/SPEED;
	
	while(1){
		music_play();
		delay(2000);
	}
}

void delay(unsigned int ms){
	unsigned char i, j;
	while(ms--)
		for(i=0; i<2; i++)
	      for(j=0; j<122; j++);
}

void decoding(unsigned char *p){
	unsigned char tunenote;
	unsigned char duration;
	unsigned char badu;
	unsigned char yinfu;
	bit shenghao=0;
	tunenote=*p;
	duration=*(p+1);
	shenghao=tunenote>>7;
	badu=(tunenote&0x30)>>4;
	yinfu=tunenote&0x0f;
	if(shenghao){
		tune_TH=music_frequp_tab[badu*16+yinfu*2];
		tune_TL=music_frequp_tab[badu*16+yinfu*2+1];
  }
	else{
		tune_TH=music_freq_tab[badu*16+yinfu*2];
		tune_TL=music_freq_tab[badu*16+yinfu*2+1];
  }
	dura_TH=(65536-duration*1000)/256;
	dura_TL=(65536-duration*1000)%256;
}

void music_play(){
	pmsc=musicdata;
	new_note=1;
	TH1=0xff;
	TL1=0xff;
	TR1=1;
	
	while(*pmsc != 0x00);
	TR0=0;
	TR1=0;
	SPEAKER=0;
}

void music_tune(void) interrupt 1{
		SPEAKER=~SPEAKER;
		TH0=tune_TH;
		TL0=tune_TL;
}
void music_dura(void) interrupt 3{
	unsigned char i;
	if(new_note) {
		decoding(pmsc);
		TH0=tune_TH;
		TL0=tune_TL;
		TR0=1;
		new_note=0;
		i=0;
	}
	else i++; 
	if(i>=repeat){ 
		TR0=0; 
		pmsc+=2; 
		new_note=1;
		}
	  TH1=dura_TH; 
		TL1=dura_TL;
	}

	
	
		




















	
