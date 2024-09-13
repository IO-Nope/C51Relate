#include<REGX52.h>
#include"../74HC595.h"
#include"../util.h"
#define LED8 P0
#define LED16 P1
static unsigned short LEDBuffer[16] = 
{0xDDDD,
 0x0000,
 0x0D00,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000,
 0x0000};
void LEDInit(){
	setSCAndSend(0xFFFF,16); //设置全阳
}

void LEDOnRender(){
	int i ;
	addOneBitAndSend(0); 
	for(i = 0;i<16;i++){
		LED8 = (unsigned char)LEDBuffer[i] & 0xff;
		LED16 = (unsigned char)(LEDBuffer[i] >> 8) & 0xff;
		Delay100us();
		Delay100us();
		LED8 = 0x00;
		LED16 = 0x00;
		addOneBitAndSend(1); 
	
	}
}

void setBuffer(unsigned short *buffer ){
    int i;
    for(i = 0;i<16;i++){
        LEDBuffer[i] = buffer[i];
    }
}

