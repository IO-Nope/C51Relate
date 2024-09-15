#include<REGX52.h>
#include"../74HC595.h"
#include"../util.h"
#define LED8 P0
#define LED16 P1
static unsigned short LEDBuffer[16] = 
{0xFFFF,
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
 0x0000,
 0x0000,
 0x0000};
void LEDOnRender(){
	int i ;
	addOneBitAndSend(0); 
	for(i = 0;i<16;i++){
		LED8 = (unsigned char)LEDBuffer[i] & 0xff;
		LED16 = (unsigned char)(LEDBuffer[i] >> 8) & 0xff;
		Delay100us();
		Delay100us();
		Delay100us();
		LED8 = 0x00;
		LED16 = 0x00;
		addOneBitAndSend(1); 
	
	}
}
void LEDShowRender(unsigned short *buffer){
	int i ;
	addOneBitAndSend(0); 
	for(i = 0;i<16;i++){
		LED8 = (unsigned char)buffer[i] & 0xff;
		LED16 = (unsigned char)(buffer[i] >> 8) & 0xff;
		Delay100us();
		Delay100us();
		Delay100us();
		LED8 = 0x00;
		LED16 = 0x00;
		addOneBitAndSend(1); 
	}
}
void LEDInit(){
	int i ;
	setSCAndSend(0xFFFF,16); //设置全阳
	for(i = 0;i<32;i++){
		if(i==16)
		{
			LEDBuffer[0]=~LEDBuffer[0];
		}
		LEDBuffer[i%16] = LEDBuffer[0];
		LEDOnRender();
	}
	LEDBuffer[0]=0x0000;
}



void setBuffer(unsigned short *buffer ){
    int i;
    for(i = 0;i<16;i++){
        LEDBuffer[i] = buffer[i];
    }
}
void LEDMergeBuffer(unsigned short *ABuffer, unsigned short *BBuffer){
	
	int i;
	for(i = 0;i<16;i++){
		LEDBuffer[i] = ABuffer[i] | BBuffer[i];
	}
}
