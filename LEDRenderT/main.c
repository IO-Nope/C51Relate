#include <REGX52.H>
#include"../74HC595.h"
#include"../16M16LEDRender.h"
void main(){
	LEDInit();
	while(1){
		//单帧渲染
		LEDOnRender();
	}
}