#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "ADXL.h"
#include "key.h"  


//ALIENTEK 探索者STM32F407开发板 实验24
//IIC 实验 --库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com  
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK



//要写入到24c02的字符串数组


int main(void)
{ 
	u8 key;
	u8 *temp;
	float temx=0.00;
	float temy=0.00;
	float temz=0.00;
  float a=0.00;	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200);	//初始化串口波特率为115200
	
	LED_Init();					//初始化LED 
 	LCD_Init();					//LCD初始化 
	KEY_Init(); 				//按键初始化  
	ADXL_init();			//IIC初始化 
 	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"IIC TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/6");	 
	while(1)
	{
    
		temp=ADXL_read();
    temx=data_x(temp);
		temy=data_y(temp);
		temz=data_z(temp);
 	  LCD_ShowxNum(30,130,temx,8,16,0);
		
//		LCD_ShowxNum(30,150,temp[0],8,16,0);
//		LCD_ShowxNum(30,170,temp[1],8,16,0);
//		LCD_ShowxNum(30,190,temp[2],8,16,0);
//		LCD_ShowxNum(30,210,temp[3],8,16,0);
//		LCD_ShowxNum(30,230,temp[4],8,16,0);
//		LCD_ShowxNum(30,250,temp[5],8,16,0);
		
		LCD_ShowxNum(30,150,temy,8,16,0);
		LCD_ShowxNum(30,170,temz,8,16,0);
		printf("X:%f    ",temx);
		printf("Y:%f    ",temy);
		printf("Z:%f    ",temz);
	}
	return 0;
}
