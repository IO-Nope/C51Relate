#ifndef __16M16LEDRENDER_H__
#define __16M16LEDRENDER_H__

void LEDInit();
void LEDOnRender();
void setBuffer(unsigned short *buffer);
void LEDMergeBuffer(unsigned short *ABuffer, unsigned short *BBuffer);



#endif // __16M16LEDRENDER_H__