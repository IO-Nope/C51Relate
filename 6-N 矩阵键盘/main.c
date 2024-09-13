#include <REGX52.H>
#include <stdbool.h>
#include "../util.h"
#include "../LCD1602.h"
#include "../MatrixKB.h"

#define MatrixKB P1

void main()
{
    LCD_Init();
    LCD_ShowNum(1, 1, 0, 2);
    while (1)
    {
        unsigned char keyNum;
        keyNum = getMatrixKBNum();
        if (keyNum)
        {
            LCD_ShowNum(1, 1, keyNum, 2);
        }
    }
}