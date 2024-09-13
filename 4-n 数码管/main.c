#include <REGX52.H>
#include "../util.h"
#define SSDNum P1
#define SSDLoc P0
void main()
{
    while(1){
			unsigned char i;
		for (i=0; i < 8; i++)
		{
			SSDNum = GetSSDNum(i);
			SSDLoc = GetSSDLoc(i);
			if(i==7) SSDNum += GetSSDNum('.');
			Delay100us();
			SSDLoc = 0xFF;
		}
		
		
    }
}