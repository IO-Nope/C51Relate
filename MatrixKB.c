#include "MatrixKB.h"
#include <REGX52.H>

// 矩阵键盘串口设置
#define MatrixKB P2
// 获取矩阵键盘按键编号
// 返回值：按键编号
// 0：无按键按下
unsigned char getMatrixKBNum()
{
    unsigned char i, j;
    unsigned char keyNum = 0;
    unsigned char mask;
    unsigned char temp;
    for (i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            MatrixKB = 0xFE;
            break;
        case 1:
            MatrixKB = 0xFD;
            break;
        case 2:
            MatrixKB = 0xFB;
            break;
        case 3:
            MatrixKB = 0xF7;
            break;
        default:
            break;
        }
        keyNum = 4 * i + 1;
        for (j = 0; j < 4; j++)
        {
            switch (j)
            {
            case 0:
                mask = 0x10;
                break;
            case 1:
                mask = 0x20;
                break;
            case 2:
                mask = 0x40;
                break;
            case 3:
                mask = 0x80;
                break;
            }
            temp = MatrixKB & mask;
            if (!temp)
            {
                ReduceButtonStrike();
                keyNum += j;
                temp = MatrixKB & mask;
                while (!temp)
                {
                    ReduceButtonStrike();
                    temp = MatrixKB & mask;
                }
                return keyNum;
            }
        }
    }
    return 0;
}