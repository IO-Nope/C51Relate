#include <REGX52.H>
#include "../util.h"
#include "../74HC595.h"

int main(){
	while(1){
		int i = 0;
		for(i=0;i<8;i++){
			setSCAndSend(i%2,1);
			DelayNms(100);
		}
	}
}

