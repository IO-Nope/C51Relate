#include <REGX52.H>
void Delay500us()		//@12.000MHz
{
	unsigned char i, j;

	i = 6;
	j = 211;
	do
	{
		while (--j);
	} while (--i);
}

void main()
{

	while(1){
		P2=0xFE;
		Delay500us();
		P2=0xFF;
	}
}
