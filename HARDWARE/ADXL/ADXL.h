#ifndef __ADXL_H
#define __ADXL_H
#include "myiic.h"
#include "sys.h"


void ADXL_init(void);

void ADXL_WriteOneByte(u8 WriteAddr,u8 DataToWrite);		//指定地址写入一个字节
u8 ADXL_ReadOneByte(u8 ReadAddr);
u8* ADXL_read(void);
float data_x(u8* temp);
float data_y(u8* temp);
float data_z(u8* temp);

#endif