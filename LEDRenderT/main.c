#include <REGX52.H>
#include"../74HC595.h"
#include"../16M16LEDRender.h"
void main(){
	unsigned short Testify[16]={0xffff,0xffff,0xffff};
	LEDInit();
	setBuffer(Testify);
	while(1){
		//单帧渲染
		LEDOnRender();
	}
}