#include "LCD1602_I2C.h"
#include "I2C_m.h"
#include "sensors.h"

uint8_t val_arr[10],num,i,m;
uint8_t parity_check,TMR0_raw[5];

int  main(){
  I2C_init();
  LCD_Init();
  DH11_init();
  
  while(1){
    DH11_read(TMR0_raw);
    parity_check = TMR0_raw[0]+TMR0_raw[1]+TMR0_raw[2]+TMR0_raw[3];
    if (parity_check != TMR0_raw[4])
    {
      LCD_string("parity error");
      _delay_ms(500);
      clr_dis(); 
      return 1;
    }
    
    LCD_string("Humi: ");
    move_cursor(1,6);
    sprintf(val_arr,"%.2d",TMR0_raw[0]);
    LCD_string(val_arr);
    move_cursor(1,8);
    sprintf(val_arr,".%.2d",TMR0_raw[1]);
    LCD_string(val_arr);
    LCD_string("%");
    move_cursor(2,1);
    LCD_string("Temp: ");
    move_cursor(2,6);
    sprintf(val_arr,"%.2d",TMR0_raw[2]);
    LCD_string(val_arr);
    move_cursor(2,8);
    sprintf(val_arr,".%.2d",TMR0_raw[3]);
    LCD_string(val_arr);
    move_cursor(2,11);sendData(0xDF);
    move_cursor(2,12);sendData(0x43);
    move_cursor(2,13);
    _delay_ms(2000);
    clr_dis(); 
  }
}

