#include "ADXL.h"
#include "delay.h"
#include "lcd.h"


void ADXL_init(void)
{
  IIC_Init();//IIC初始化
	ADXL_WriteOneByte(0x31,0x0b);
	ADXL_WriteOneByte(0x2c,0x08);
	ADXL_WriteOneByte(0x2d,0x08);
	ADXL_WriteOneByte(0x2e,0x80);
	ADXL_WriteOneByte(0x1e,0x00);
	ADXL_WriteOneByte(0x1f,0x00);
	ADXL_WriteOneByte(0x20,0x05);
}

u8 ADXL_ReadOneByte(u8 ReadAddr)
{
	u8 temp=0;
	IIC_Start();
	IIC_Send_Byte(0XA6);	   //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(ReadAddr);
	IIC_Wait_Ack();	    
	IIC_Start();  
	IIC_Send_Byte(0XA7);           //进入接收模式	
	IIC_Wait_Ack();	
	temp=IIC_Read_Byte(0);		   
  IIC_Stop();//产生一个停止条件	    
	return temp;
}

void ADXL_WriteOneByte(u8 WriteAddr,u8 DataToWrite)
{
	IIC_Start(); 
	IIC_Send_Byte(0XA6);	    //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(WriteAddr);
	IIC_Wait_Ack();	
	IIC_Send_Byte(DataToWrite);
	IIC_Wait_Ack();  		    	   
  IIC_Stop();//产生一个停止条件 
	
}

u8* ADXL_read(void)
{ 
	int i=0;
	u8* BUFF;
	IIC_Start();
	IIC_Send_Byte(0XA6);	   //发送写命令
	IIC_Wait_Ack();
	IIC_Send_Byte(0x32);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(0XA7);           //进入接收模式	
	IIC_Wait_Ack();
 
	for( i=0;i<6;i++)
  {
     
		 if(i==5)
		 {
			 //IIC_NAck();
			 BUFF[i]=	IIC_Read_Byte(0);
		 }
		 else
		 {
			 //IIC_Ack();
			 BUFF[i]=	IIC_Read_Byte(1);
		 }
	 }
	  IIC_Stop();//产生一个停止条件
	 return BUFF;
 }

float data_x(u8* temp)
{
	float tem=0;
	int final=0;
	u16 data=(((temp[1]<<8)|temp[0]));
	if(data<0xf000)
	{
		data=(data&0x0fff);
		tem=(float)(data)*3.9;
		//LCD_ShowString(30,110,200,16,16,"X:");
		//LCD_ShowxNum(30,130,tem,8,16,0);
		//LCD_ShowString(80,130,200,16,16,"mg");
	}
	else
	{
		data=(data&0x0fff);
		data=(0x1000-data);
	  tem=(float)(data)*3.9;
		tem=-tem;
	}
//	if(data<0)
//	{
//		data=-data;
//	}
	
	//tem/=1000;
	return tem;
}

float data_y(u8* temp)
{
	float tem=0;
	int final=0;
	u16 data=(((temp[3]<<8)|temp[2]));
	if(data<=0xf000)
	{
		data=(data&0x0fff);
		tem=(float)(data)*3.9;
		//LCD_ShowString(30,110,200,16,16,"X:");
		//LCD_ShowxNum(30,130,tem,8,16,0);
		//LCD_ShowString(80,130,200,16,16,"mg");
	}
	else
	{
		data=(data&0x0fff);
		data=(0x1000-data);
	  tem=(float)(data)*3.9;
		tem=-tem;
	}
	return tem;
}

float data_z(u8* temp)
{
	float tem=0;
	int final=0;
	u16 data=(((temp[5]<<8)|temp[4]));
	if(data<=0xf000)
	{
		data=(data&0x0fff);
		tem=(float)(data)*3.9;
		//LCD_ShowString(30,110,200,16,16,"X:");
		//LCD_ShowxNum(30,130,tem,8,16,0);
		//LCD_ShowString(80,130,200,16,16,"mg");
	}
	else
	{
		data=(data&0x0fff);
		data=(0x1000-data);
	  tem=(float)(data)*3.9;
		tem=-tem;
	}
	return tem;
}