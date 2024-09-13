#ifndef _74HC595_H_
#define _74HC595_H_
void setSCAndSend(unsigned short num , unsigned char length);

void SendSC();

void SendSE();

void addOneBitAndSend(unsigned char num);

#endif