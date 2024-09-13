#include "74HC595.h"
#include <REGX52.h>

sbit RC = P3^5;  //移位寄存to显示寄存
sbit SC = P3^6; //储存to移位寄存
sbit SE = P3^7;  //储存值

void setSCAndSend(unsigned short num , unsigned char length){
	int i ;
	unsigned short aim = num;
	for(i=0;i<length;i++){
		SE = aim %2;
		aim = aim >> 1;
		SendSE();
	}
	SendSC();
}

void SendSC(){
    RC = 0;
    RC = 1;
}
void SendSE(){
    SC = 0;
    SC = 1;
}

void addOneBitAndSend(unsigned char num){
    SE = num%2;
    SendSE();
    SendSC();
}
