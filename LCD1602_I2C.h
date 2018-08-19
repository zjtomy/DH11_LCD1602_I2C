#include <inttypes.h>

#define E   2   // E  bit
#define RW  1   // RW bit
#define RS  0   // RS bit
#define function_set1 0x33
#define function_set2 0x32
#define function_set3 0x28
#define display_control 0x0F
#define clear_display 0x01
#define first_row 0x80
#define second_row 0xBF

#define ddram_before_char1  0xD0
#define ddram_after_char16  0x11
#define ddram_before_char16  0x10
#define ddram_before_char17 0xBF
#define ddram_after_char32  0x22

#define LCDadd_WR  0x4E
#define LCDadd_RD  0x4F

extern uint8_t i, bitmask, arr_size;
extern uint8_t arr[];

// LCD prototypes
void LCD_Init(void);
void sendCMD(uint8_t CMD);
void sendData(uint8_t data);
void LCD_string(uint8_t *msg);
void move_cursor (uint8_t row, uint8_t col);
void lcdCMD_read (void);
void clr_dis(void);
