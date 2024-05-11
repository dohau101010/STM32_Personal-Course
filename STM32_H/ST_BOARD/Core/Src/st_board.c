#include "st_board.h"
#include "stm32f1xx_hal.h"

char scan_code[9]= {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe,0xff}; 
char numc[16]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uint8_t led7_seg[4] = {0xff, 0xff, 0xff, 0xff};
uint8_t led7_segs[8] = {0xff, 0xff, 0xff, 0xff,0xff, 0xff, 0xff, 0xff};
uint16_t led14_segs[8] = {0xffff, 0xffff, 0xffff, 0xffff,0xffff, 0xffff, 0xffff, 0xffff};
uint16_t  led16_led[2];

uint8_t key_read(void)
{
    uint8_t mp = 0xff;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0)      mp = 0;
    else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0) mp = 1;
    else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0) mp = 2;
   else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0) mp = 3;
   
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0)      mp = 4;
    else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0) mp = 5;
    else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0) mp = 6;
   else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0) mp = 7;
   
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0)      mp = 8;
    else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0) mp = 9;
    else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0) mp = 10;
   else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0) mp = 11;
    
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0)      mp = 12;
    else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0) mp = 13;
    else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 0) mp = 14;
   else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == 0) mp = 15;
    
    
   return mp;
}

uint8_t key4x4_read(void)
{
   uint8_t mp1, mp2;
   mp1 = key_read();
   if(mp1 != 0xff)
   {
      HAL_Delay(20);
      mp1 = key_read();
    do
      {
         HAL_Delay(5);
         mp2 = key_read();
      } while(mp2 == mp1);
   }
    return mp1;
}


void delay_us(uint32_t us) {
 uint32_t loops = us * (8000000 / 1000000) / 10;  

    for (uint32_t i = 0; i < loops; ++i) {
    }
}

void output_bh(uint8_t  byte)
{
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, (GPIO_PinState) (byte&128));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (GPIO_PinState) (byte&64));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (GPIO_PinState) (byte&32));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (GPIO_PinState) (byte&16));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (GPIO_PinState) (byte&8));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (GPIO_PinState) (byte&4));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (GPIO_PinState) (byte&2));
   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (GPIO_PinState) (byte&1));
}
void lcd_command(char cmd)
{
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);    
  output_bh(cmd);
  
  delay_us(200);
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);   
  delay_us(200);
}
void lcd5x8_display(uint8_t data)
{
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);   
   output_bh(data);
  
   delay_us(20);
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);   
   delay_us(20);
}
void lcdstring_display(uint8_t  *data)
{
   while(*data)
   {
      lcd5x8_display(*data);
      data ++ ;
   }
}

void lcd_goto(uint8_t x, uint8_t y)
{
   char lcd_pos[] ={0x80, 0xc0, 0x94, 0xd4};
   lcd_command(lcd_pos[x] + y);
}

const uint8_t   lcd_so_to[10][6] ={
                  0,1,2,4,3,5,    // so 0
                  1,2,32,3,7,3,   // so 1
                  6,6,2,4,3,3,    // so 2
                  6,6,2,3,3,5,    // so 3
                  7,3,7,32,32,7,  // so 4
                  7,6,6,3,3,5,    // so 5                               
                  0,6,6,4,3,5,    // so 6
                  1,1,7,32,32,7,  // so 7
                  0,6,2,4,3,5,    // so 8
                  0,6,2,3,3,5};   // so 9
const uint8_t  lcd_ma_8doan[] = {
   0x07,0x0f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan f - 0
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x00,0x00,  //doan a - 1
   0x1c,0x1e,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,  //doan b - 2
   0x00,0x00,0x00,0x00,0x00,0x1f,0x1f,0x1f,  //doan d - 3
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x0f,0x07,  //doan e - 4
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1e,0x1c,  //doan c - 5      
   0x1f,0x1f,0x1f,0x00,0x00,0x00,0x1f,0x1f,  //doan g+d-6 
   0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}; //doan i  -7  


void lcd2x3_display(uint8_t  so, uint8_t x,uint8_t y) 
{                        
   uint8_t i;
   lcd_goto(x,y);
   for(i=0;i<6;i++)
   {                                                           
      if(i==3) lcd_goto(x+1,y);
      lcd5x8_display(lcd_so_to[so][i]);
   }                        
} 
const uint8_t LCD_SO_X1[11][12] ={   //Font 3x4 
0,1,2,7,32,7,7,32,7,5,3,4,   //0
1,2,32,32,7,32,32,7,32,3,7,3,   //1
1,1,2,3,3,7,7,32,32,5,3,3,   //2
0,1,2,32,3,4,32,32,2,5,3,4,   //3
7,32,7,5,3,7,32,32,7,32,32,7,   //4
7,1,1,7,3,3,32,32,7,5,3,4,   //5
0,1,2,7,3,3,7,32,7,5,3,4,   //6
1,1,7,32,32,4,32,0,32,32,7,32,   //7
0,1,2,5,3,4,0,32,2,5,3,4,   //8
0,1,2,5,3,7,32,32,7,5,3,4,   //9
32,32,32,32,32,32,32,32,32,32,32,32};//XOA
void lcd3x4_display(uint8_t  so, uint8_t y) 
{                        
   uint8_t i;
   lcd_goto(0,y);
   for(i=0;i<12;i++)
   {                                                           
      if(i==3)      lcd_goto(1,y);
        else if(i==6) lcd_goto(2,y);
        else if(i==9) lcd_goto(3,y);
      lcd5x8_display(LCD_SO_X1[so][i]);
   }                        
}
void lcd_setup(void)
{
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
   lcd_command(0x38);
   HAL_Delay(1);
   lcd_command(0x0c);
   lcd_command(0x01);
   HAL_Delay(2);
   lcd_command(0x06);
   uint8_t  i;
  lcd_command(0x40);
  for(i=0;i<64;i++)  
  lcd5x8_display(lcd_ma_8doan[i]); 
}

//********************************************************


void put1_byte(uint8_t byte)
{
      for(uint8_t i = 0; i < 8; i++)
   {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, (GPIO_PinState) (byte&(0x80 >> i)));
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_SET );
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET );
   }
}
void led7seg_display(void)
{
   put1_byte(led7_seg[3]);
   put1_byte(led7_seg[2]);
   put1_byte(led7_seg[1]);
   put1_byte(led7_seg[0]);
   
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET );
   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET );
}
void led7segs_data(uint8_t pos, uint8_t byte)
{
   put1_byte(scan_code[pos]);
   put1_byte(byte);
   
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET );
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET );   
}
void led7segs_display(void)
{
      for(uint8_t i = 0; i< 8; i++)
   {
      led7segs_data(i, led7_segs[i]);
      HAL_Delay(5);
      led7segs_data(8, 0xff);   
   }
}
void led14segs_data(uint8_t pos, uint16_t byte)
{
   put1_byte(scan_code[pos]);
   put1_byte(byte>>8);
   put1_byte(byte);
   
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET );
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET );
}
void led14segs_display(void)
{
      for(uint8_t i = 0; i< 8; i++)
   {
      led14segs_data(i, led14_segs[i]);
      HAL_Delay(1);
      led14segs_data(8, 0xffff);   
   }
}
void led32_display(void)
{
   put1_byte(led16_led[1]>>8);
   put1_byte(led16_led[1]);
   put1_byte(led16_led[0]>>8);
   put1_byte(led16_led[0]);
   
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET );
   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET );    
}

//****************************RTC***********************
// RTC_TimeTypeDef sTime;
// RTC_DateTypeDef DateToUpdate;
// uint8_t sec, min, hour, date, day, mon, year;
//void RTC_getvalue()
//{    
//      HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BCD);
//      HAL_RTC_GetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD);
//       sec = sTime.Seconds;
//       min = sTime.Minutes;
//       hour = sTime.Hours;
//       
//       day = DateToUpdate.Date;
//       mon = DateToUpdate.Month;
//       year = DateToUpdate.Year;
//       date = DateToUpdate.WeekDay;
//}

//**********************************************************

