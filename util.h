#ifndef _UTIL_H_
#define _UTIL_H_
#include <REGX52.H>
void Delay1ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

void DelayNms(unsigned int n) {
    if(n==0)return;
    while (n--) {
        Delay1ms();
    }
}

void ReduceButtonStrike()
{
    unsigned char i;
    for (i = 0; i < 20; i++)
    {
        Delay1ms();
    }
}
void Delay100us(){
	unsigned char i, j;
	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}

unsigned char GetSSDNum( unsigned char n){
    unsigned char ans;
    switch(n){
        case 0: ans = 0x3F; break;
        case 1: ans = 0x06; break;
        case 2: ans = 0x5B; break;
        case 3: ans = 0x4F; break;
        case 4: ans = 0x66; break;
        case 5: ans = 0x6D; break;
        case 6: ans = 0x7D; break;
        case 7: ans = 0x07; break;
        case 8: ans = 0x7F; break;
        case 9: ans = 0x6F; break;
        case '.': ans = 0x80; break;
        default: ans = 0x79; break;
    }
    return ans;
}

unsigned char GetSSDLoc(unsigned char n){
    unsigned char ans;
    switch (n)
    {
    case 0:
        ans = 0xFE;
        break;
    case 1:
        ans = 0xFD;
        break;
    case 2:
        ans = 0xFB;
        break;
    case 3:
        ans = 0xF7;
        break;
    case 4:
        ans = 0xEF;
        break;
    case 5:
        ans = 0xDF;
        break;
    case 6:
        ans = 0xBF;
        break;
    case 7:
        ans = 0x7F;
        break;
    default:
        ans = 0xFF;
        break;
    }
    return ans;
}





#endif // _UTIL_H_