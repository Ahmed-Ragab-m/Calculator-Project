#include "stand Types.h"
#include "DIO_Interface.h"
#include "Keypad_Interface.h"
#include "LCD_Interface.h"
#include "Calculator.h"

#define F_CPU  8000000
#include <util/delay.h>

void calculator(void)
{
	DIO_Init();
	Keypad_Init();
	LCD_Init();
	s8 key, operation_flag = 0, minus_flag =0, plus_flag = 0, times_flag = 0, divded_flag = 0, first_itration = 0, negativ_flag = 0;
	s32 num=0, answer=0;
	LCD_Set_Cursor(0,0);
	LCD_Write_String("calculator project");
	_delay_ms(2000);
	LCD_Clear();
	
	while(1)
	{
		key=keypad_key();
		if(key!=no_key)
		{
			if ((answer > 0 || answer < 0 ) && (operation_flag == 1) && ((key == '/')||(key == '*')||(key == '+')||(key == '-')))
			{
				LCD_Clear();
				LCD_Set_Cursor(0,0);
				LCD_Write_Number(answer);
				operation_flag=0;
			}
			
			else if((answer > 0 || answer < 0 ) && (operation_flag == 1) && (key >= '0' && key <= '9'))
			{
				LCD_Clear();
				num = 0;
				answer =0 ;
				first_itration = 0 ;
				divded_flag =0 ;
				times_flag = 0;
				minus_flag = 0 ;
				plus_flag = 0 ;
				operation_flag =0 ;
				continue;
			}
			
			LCD_Write_char(key);
			
			if(key >= '0' && key <= '9')
			{
				num = num * 10 + (key -'0');
			}
			
			else if (key == '/')
			{
				divded_flag = 1 ;
				first_itration = 1;
			}
			
			else if (key == '*')
			{
				times_flag = 1 ;
				first_itration = 1 ;
			}
			
			else if (key == '-')
			{
				if((num == 0 ) && (answer == 0))
				{
					negativ_flag = 1 ;
					first_itration = 0  ;
				}
				else
				{
					minus_flag = 1 ;
					first_itration = 1  ;
				}
			}
			
			else if (key == '+' )
			{
				plus_flag = 1 ;
				first_itration = 1 ;
			}
			
			else if (key == '=')
			{
				if(divded_flag == 1)
				{
					if(num == 0)
					{
						LCD_Clear();
						LCD_Write_String("Math Error");
						_delay_ms(500);
						LCD_Clear();
						num = 0;
						answer =0 ;
						first_itration = 0 ;
						divded_flag =0 ;
						times_flag = 0;
						minus_flag = 0 ;
						plus_flag = 0 ;
						operation_flag =0 ;
						continue;
					}
					else
					{
						answer = answer / num ;
						divded_flag = 0;
					}
				}
				
				else if(times_flag  == 1)
				{
					answer = answer * num ;
					times_flag = 0;
				}
				else if(minus_flag == 1 )
				{

					answer = answer - num ;
					minus_flag = 0;
				}
				else if(plus_flag == 1)
				{
					answer = answer + num ;
					plus_flag = 0;
				}
				LCD_Set_Cursor(1,0);
				LCD_Write_Number(answer);
				operation_flag = 1 ;
				num = 0;
			}
			
			else if (key == 'C')
			{
				LCD_Clear();
				num = 0;
				answer =0 ;
				first_itration = 0 ;
				divded_flag =0 ;
				times_flag = 0;
				minus_flag = 0 ;
				plus_flag = 0 ;
				operation_flag = 0 ;
			}
			
			if((first_itration == 1) && (answer == 0))
			{
				if (negativ_flag == 1)
				{
					num = num * (-1);
					negativ_flag = 0 ;
				}
				answer = num ;
				num = 0;
				first_itration = 2 ;
			}
			
			
		}
		
		
	} 
}

