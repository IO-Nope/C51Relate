#include <REGX52.H>
#include <string.h>
#include "../LCD1602.h"
#include "../Timer.h"
static unsigned char T0ms = 1;
static unsigned char T0s = 1;
static unsigned char TimeDisplay[3] = {0, 0, 0};
static int T0counter=0;
void main(){
	Timer0Init(getMsTick(T0ms));
	LCD_Init();	
	while(1){
		
		
	}
}
void Timer0_Routine() interrupt 1{

    TH0 = getMsTick(T0ms)/256;
    TL0 = getMsTick(T0ms)%256;
    T0counter++;
    if(!(T0counter>=1000*T0s))return;
    T0counter=0;
	TimeDisplay[2]++;
	if(TimeDisplay[2]>=60){
		TimeDisplay[2]=0;
		TimeDisplay[1]++;
		if(TimeDisplay[1]>=60){
			TimeDisplay[1]=0;
			TimeDisplay[0]++;
			if(TimeDisplay[0]>=24){
				TimeDisplay[0]=0;
			}
		}
	}
	LCD_ShowNum(1,1,TimeDisplay[0],2);
	LCD_ShowChar(3,1,':');
	LCD_ShowNum(4,1,TimeDisplay[1],2);
	LCD_ShowChar(6,1,':');
	LCD_ShowNum(7,1,TimeDisplay[2],2);
}