#include <REGX52.H>
#include "../Timer.h"
#include "../MatrixKB.h"
#include "../16M16LEDRender.h"

enum CurbState{
	Normal,
	Left,
	Right,
	LeftAndRight
};
enum CurbType{
	SquareCurb,
	LCurb,
	StraightCurb,
	RLCurb,
	TCurb
};
static unsigned char isFinishRender = 0;
static unsigned char isIPTAcquired = 0;
static unsigned char isNeedFall = 0;
xdata unsigned short ActingBuffer[16]={0x0000};
xdata unsigned short StcBuffer[16]={0xFFFF};
void main(){
	//Game init
	LEDInit();

	
	//main loop
	Timer0Init(getMsTick(1));
	while(1){
		//setRenderFlag
		isFinishRender = 0;
		//handle msg
		
		//acculate data
		

		//render loop		
		setBuffer(StcBuffer);
		while(!isIPTAcquired){
			LEDOnRender();
			//set finish flag
			isFinishRender = 1;
		}
	}
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
	}
	if(fallCount >= fallSpeed){
		isNeedFall = 1;
	}
}