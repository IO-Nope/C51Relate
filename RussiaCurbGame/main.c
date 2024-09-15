#include <REGX52.H>
#include <stdlib.h>
#include "../Timer.h"
#include "../MatrixKB.h"
#include "../16M16LEDRender.h"
enum CurbType{
	SquareCurb,
	LCurb,
	StraightCurb,
	RLCurb,
	TCurb
};
static unsigned char quit = 0;
static unsigned char isFinishRender = 0;
static unsigned char isPlacing =0;
static unsigned char isIPTAcquired = 0;
static unsigned char isNeedFall = 0;
xdata unsigned char currentCurbType = 100;
xdata unsigned char CurbCenter[2]={0,0};
xdata unsigned short ActingBuffer[16]={0x0000};
xdata unsigned short StcBuffer[16]={0x0000};
void ClearBuffer(unsigned short *buffer){
	int i;
	for(i=0;i<16;i++){
		buffer[i]=0x0000;
	}
}
void NewCurb(){
	int i;
	unsigned char ctype = rand() % 5;
	ClearBuffer(ActingBuffer);
	
	switch (ctype)
	{
	case SquareCurb:
			ActingBuffer[0] = 0x0180;
			ActingBuffer[1] = 0x0180;
			CurbCenter[0] = 1;
			CurbCenter[1] = 8;
		break;
	case LCurb:
			ActingBuffer[0] = 0x0080;
			ActingBuffer[1] = 0x0380;
			CurbCenter[0] = 1;
			CurbCenter[1] = 8;

		break;
	case StraightCurb:
			ActingBuffer[1] = 0x03C0;
			CurbCenter[0] = 1;
			CurbCenter[1] = 8;
		break;
	case RLCurb:
			ActingBuffer[0] = 0x0200;
			ActingBuffer[1] = 0x0380;
			CurbCenter[0] = 1;
			CurbCenter[1] = 8;
		break;
	case TCurb:
		ActingBuffer[0] = 0x0100;
		ActingBuffer[1] = 0x0380;
		CurbCenter[0] = 1;
		CurbCenter[1] = 8;
		break;
	default:
		break;
	}
	isPlacing = 1;
	currentCurbType = ctype;
	for(i=0;i<16;i++){
		if(ActingBuffer[i]&StcBuffer[i]){
			quit = 1;
			return;
		}
	}
}
void MergeCurb(){
	int i;
	for(i=0;i<16;i++){
		StcBuffer[i] = StcBuffer[i] | ActingBuffer[i];
	}
}
void OnFall(){
	int i;
	unsigned short temp;
	//检测到底
	if(ActingBuffer[15]){
		isPlacing = 0;
		MergeCurb();
		ClearBuffer(ActingBuffer);
		return;
	}
	//检测碰撞
	for(i=0;i<15;i++){
		temp = StcBuffer[i+1]&ActingBuffer[i];
		if(temp){
			isPlacing = 0;
			MergeCurb();
			ClearBuffer(ActingBuffer);
			return;
		}
	}
	//下落
	for(i=15;i>0;i--){
		ActingBuffer[i] = ActingBuffer[i-1];
	}
	CurbCenter[0]++;
	ActingBuffer[0] = 0x0000;
	
}
void OnLeft(){
	int i;
	unsigned short temp;
	//检测碰撞+出界检测
	for(i=0;i<16;i++){
		if(ActingBuffer[i]&0x8000){
			return;
		}
		temp = (ActingBuffer[i]<<1) & StcBuffer[i];
		if(temp){
			return;
		}
	}
	//左移
	for(i=0;i<16;i++){
		ActingBuffer[i] = ActingBuffer[i]<<1;
	}
	CurbCenter[1]++;
}
void OnRight(){
	int i;
	unsigned short temp;
	//检测碰撞+出界检测
	
	for(i=0;i<16;i++){
		if(ActingBuffer[i]&0x0001){
		return;
		}
		temp = (ActingBuffer[i]>>1) & StcBuffer[i];
		if(temp){
			return;
		}
	}
	//右移
	for(i=0;i<16;i++){
		ActingBuffer[i] = ActingBuffer[i]>>1;
	}
	CurbCenter[1]--;
}
void OnDown(){
	//检测碰撞
	while(isPlacing){
		OnFall();
	}
}

unsigned char GetBit(unsigned short aim,unsigned char bitNum){
	unsigned short mask = 0x0001<<bitNum; 
	if(aim & mask){
		return 1;
	}
	return 0;
}
unsigned char GetActingBit(unsigned char layer, unsigned char bitNum){
	return GetBit(ActingBuffer[layer],bitNum);
}
void SetBit(unsigned short *aim,unsigned char bitNum,unsigned char value){
	unsigned short mask = 0x0001<<bitNum;
	if(value){
		*aim = *aim | mask;
	}else{
		*aim = *aim & (~mask);
	}
}
void OnSwitch(){
	int i;
	unsigned char c0 = CurbCenter[0];
	unsigned char c1 = CurbCenter[1];
	xdata unsigned short temp[16]={0x0000};
	if(CurbCenter[0] > 15 || CurbCenter[1] >= 15||CurbCenter[1]<=1){
		return;
	}
	if(currentCurbType == SquareCurb){
		return;
	}
	if(currentCurbType == StraightCurb){
		if(c0+2>15||c1-2<0)return;
		if(GetActingBit(c0,c1+1)){
			SetBit(&temp[c0-1],c1,1);
			SetBit(&temp[c0],c1,1);
			SetBit(&temp[c0+1],c1,1);
			SetBit(&temp[c0+2],c1,1);
		}else{
			SetBit(&temp[c0],c1-1,1);
			SetBit(&temp[c0],c1,1);
			SetBit(&temp[c0],c1+1,1);
			SetBit(&temp[c0],c1-2,1);
		}
	}else{
	for(i=0;i<16;i++){
		temp[i] = ActingBuffer[i];
	}
	//右旋
	SetBit(&temp[c0-1],c1,GetActingBit(c0,c1+1));
	SetBit(&temp[c0],c1+1,GetActingBit(c0+1,c1));
	SetBit(&temp[c0],c1-1,GetActingBit(c0-1,c1));
	SetBit(&temp[c0+1],c1,GetActingBit(c0,c1-1));
	SetBit(&temp[c0-1],c1+1,GetActingBit(c0+1,c1+1));
	SetBit(&temp[c0-1],c1-1,GetActingBit(c0-1,c1+1));
	SetBit(&temp[c0+1],c1+1,GetActingBit(c0+1,c1-1));
	SetBit(&temp[c0+1],c1-1,GetActingBit(c0-1,c1-1));
	}
	for(i=0;i<16;i++){
		if(temp[i]&StcBuffer[i]){
			return;
		}
	}
	for(i=0;i<16;i++){
		ActingBuffer[i] = temp[i];
	}

}
void main(){
	//Game init
	int i=0 ,j=0;
	unsigned  msg = 0;
	LEDInit();

	
	//main loop
	Timer0Init(getMsTick(1));
	while(!quit){
		//setRenderFlag
		isIPTAcquired=0;
		isFinishRender = 0;
		if(!isPlacing){
			NewCurb();
		}
		//handle msg
		msg = getMatrixKBNum();
		if(isNeedFall){
			//Fall
			OnFall();
			isNeedFall =0;
		}
		//acculate data
		switch (msg)
		{
		case 2: //right
			OnRight();
			break;
		case 5: //up
			OnSwitch();
			break;
		case 7: //down
			OnDown();
			break;
		case 10: //left
			OnLeft();
			break;
		default:
			break;
		}
		//StcUpdate
		if(!isPlacing){
			unsigned char count = 0;
			for(i=15;i>=0;i--){
				if(StcBuffer[i]==0xFFFF){
					StcBuffer[i]=0x0000;
					count++;
				}
				if(count){
					unsigned short temp[16] = {0x0000};
					unsigned char layer = 15;
					for(j=15;j>=0;j--){
						if(StcBuffer[j]){
							temp[layer] = StcBuffer[j];
							layer--;
						}
					}
					for(j=15;j>=0;j--){
						StcBuffer[j] = temp[j];
					}
				}
			}
		}
		//render loop		
		//LEDInit();
		LEDMergeBuffer(StcBuffer,ActingBuffer);
		while(!isIPTAcquired){
			LEDOnRender();
			//set finish flag
			isFinishRender = 1;
		}
	}
	//Game end
	LEDInit();
}

void Timer0Interrupt() interrupt 1{
	static unsigned int fpsTick = 1000/60;
	static unsigned int fpsCount = 0;
	static unsigned int fallSpeed = 1000;
	static unsigned int fallCount = 0; 

	fpsCount++;
	fallCount++;
	if(fpsCount >= fpsTick){
		if(isFinishRender){
			isIPTAcquired = 1;
		}
		fpsCount = 0;
	}
	if(fallCount >= fallSpeed){
		isNeedFall = 1;
		fallCount = 0;
	}
	TimerReset(getMsTick(1));
}