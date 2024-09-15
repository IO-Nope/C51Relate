#include"Timer.h"
#include<REGX52.h>
unsigned int getMsTick(unsigned char Tms){
    if(Tms>6){
        return 0;
    }
	return 65536 -1000 * Tms;
}
void Timer0Init(unsigned int Tus){
    if (Tus > 65535)
    {
        Tus =65535;
    }
    TMOD = 0x01;
    //存疑
   TF0 = 0;
   TR0 = 1;
   //高低位分离
   //1tick 1us 1000tick 1ms
   TH0 = Tus/256;
   TL0 = Tus%256;
   ET0=1;
   EA=1;
   PT0 = 0;
}
void TimerReset(unsigned int Tus){
    if (Tus > 65535)
    {
        Tus =65535;
    }
    TH0 = Tus/256;
    TL0 = Tus%256;
}

