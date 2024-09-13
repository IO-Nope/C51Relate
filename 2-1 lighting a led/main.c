#include <REGX52.H>
void main()
{

	int i =0;
	while(1)
	{
		if(!(i%60))
		{
			P2=0xFE;
		}
		else 
		{
			P2=0x55;
		}
		i+=1;
	}
}
