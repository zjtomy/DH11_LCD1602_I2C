#include "LCD1602_I2C.h"
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include "I2C_m.h"


uint8_t bitmask = 0x08;
uint8_t arr[]={0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x41,
0x72, 0x64, 0x75, 0x69, 0x6e, 0x6f, 0x20, 0x3a, 0x29, 0x20,
0x57, 0x68, 0x61, 0x74, 0x27, 0x73, 0x20, 0x75, 0x70,
0x21, 0x20, 0x48, 0x6f, 0x77, 0x27, 0x73, 0x20, 0x63,
0x6f, 0x64, 0x69, 0x6e, 0x67, 0x20, 0x74, 0x6f, 0x64, 0x61,
0x79, 0x20, 0x3a, 0x29};
uint8_t arr_size=sizeof(arr);


void lcdCMD_read (void)
{
  I2C_start(LCDadd_WR);            // write PCF8574 address
  I2C_tx(bitmask = 0x0B);          // RS, RW = 1 read data
  I2C_tx(bitmask |= (1<<E));
  I2C_tx(bitmask &= ~(1<<E));
  I2C_stop();
  I2C_start(LCDadd_RD);           // read PCF8574 address
  bitmask = I2C_rx();             // receive I2C and get TWDR
  //while (!(TWDR == (bitmask & (bitmask<<7))));  // This function never ends
  I2C_stop();
}
void LCD_Init(void)
{
  
  sendCMD(0x02);
  sendCMD(0x28);
  sendCMD(0x0F);
  sendCMD(0x01);
  sendCMD(0x80);
  _delay_ms(2);
}

void sendCMD(uint8_t CMD)
{
  bitmask = 0x08;
  I2C_start(LCDadd_WR);
  I2C_tx(bitmask = CMD & 0xF0 | 0x08);
  I2C_tx(bitmask |= (1<<E));
  I2C_tx(bitmask &= ~(1<<E));
  I2C_tx(bitmask = (CMD<<4) & 0xF0 | 0x08);
  I2C_tx(bitmask |= (1<<E));
  I2C_tx(bitmask &= ~(1<<E));
  I2C_stop();
}

void sendData(uint8_t data)
{
  bitmask = 0x08;
  I2C_start(LCDadd_WR);
  I2C_tx(bitmask = data & 0xF0 | 0x08 | (1<<RS));
  I2C_tx(bitmask |= (1<<E));
  I2C_tx(bitmask &= ~(1<<E));
  I2C_tx(bitmask = (data<<4) & 0xF0 | 0x08 | (1<<RS));
  I2C_tx(bitmask |= (1<<E));
  I2C_tx(bitmask &= ~(1<<E));
  I2C_stop();
}

uint8_t BF(void)
{
  I2C_start(LCDadd_WR);
  I2C_tx(bitmask &= ~(1<<RS));
  I2C_tx(bitmask |= (1<<RW));
  I2C_stop();
  I2C_start(LCDadd_RD);
  I2C_rx();
  while (!(TWDR == (bitmask & (bitmask<<3))));
  I2C_stop();
  I2C_start(LCDadd_WR);
  I2C_tx(bitmask |= (1<<RS));
  I2C_tx(bitmask &= ~(1<<RS));
  I2C_stop();
}

void move_cursor (uint8_t row, uint8_t col)
{
  if (row==1)
  sendCMD(first_row+(col-1));
  if (row==2)
  sendCMD(0xC0+(col-1));
}

void clr_dis(void)
{
	sendCMD(clear_display);
	_delay_ms(2);
}


void LCD_string(uint8_t *msg)
{
  uint8_t cnt=1;
  while(*msg)
  {
    sendData(*msg);
    msg++;cnt++;
    if (cnt==ddram_after_char16){
    sendCMD(second_row);msg--;}
    if (cnt==ddram_after_char32){
	msg--;sendCMD(clear_display);cnt=0;}
  }
}
