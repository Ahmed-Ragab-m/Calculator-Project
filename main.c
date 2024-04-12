#include "stand Types.h"
#include "Memory_Map.h"
#include "utils.h"
#include "DIO_Interface.h"
#include "Motor_Interface.h"
#include "LCD_Interface.h"
#include "Keypad_Interface.h"
#include "ADC.h"
#include "Sensors.h"
#include "WDT.h"
#include "NVM.h"
#include "Timers.h"
#include "Timers_Services.h"
#include "Fire_system.h"
#include "RGB.h"
#include "Ultrasonic.h"
#include "UART.h"
#include "UART_Services.h"
#include "SPI.h"
#include "OS.h"
#include "Task.h"


//#include <avr/io.h>

#define F_CPU  8000000
#include <util/delay.h>

static volatile u8 flag = 0 ;
static volatile u16 t1  = 0 ;
static volatile u16 t2  = 0 ;
void UltraSonic(void);


	
int main(void)
{
      u16 time  = 0 ;
      u16 distance = 0 ;
      sei();
      DIO_Init();
      LCD_Init();
      Timer1_Init(TIMER1_NORMAL_MODE,TIMER1_SCALER_8);
      Timer1_ICU_InterruptEnable();
      Timer1_ICU_SetCallBack(UltraSonic);
      LCD_Write_String("UltraSonicDistance"); 

    while (1)
    {
		Timer1_InputCaptureEdge(RISING);
		TCNT1=0;
		DIO_Write_pin(PINC0,HIGH);
		_delay_us(10);
		DIO_Write_pin(PINC0,LOW);
		while(flag < 2);
		time = t2 - t1 ;
		distance = time / 58 ;
		
		LCD_Set_Cursor(1,0);
		
		LCD_Write_Number(distance);
		LCD_Write_String("         ");
		flag = 0 ;
		Timer1_ICU_InterruptEnable();
    }
}

void UltraSonic(void)
{
	if(flag == 0)
	{
		t1= ICR1;
		Timer1_InputCaptureEdge(FALLING);
		flag = 1 ;
	}
	else if(flag == 1)
	{
		t2= ICR1;
		Timer1_ICU_InterruptDisable();
		flag = 2 ;
	}
}

