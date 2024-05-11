
#include <stdint.h>
extern char scan_code[9];
extern char numc[16];
extern uint8_t led7_seg[4];
extern uint8_t led7_segs[8];
extern uint16_t led14_segs[8];
extern uint16_t led16_led[2];

uint8_t key_read(void);
uint8_t key4x4_read(void);
void delay_us(uint32_t us);
void output_bh(uint8_t  byte);
void lcd_command(char cmd);
void lcd5x8_display(uint8_t data);
void lcdstring_display(uint8_t  *data);
void lcd_goto(uint8_t x, uint8_t y);
void lcd2x3_display(uint8_t  so, uint8_t x,uint8_t y) ;
void lcd3x4_display(uint8_t  so, uint8_t y) ;
void lcd_setup(void);
void put1_byte(uint8_t byte);
void led32_display(void);
void led7seg_display(void);
void led7segs_data(uint8_t pos, uint8_t byte);
void led7segs_display(void);
void led14segs_data(uint8_t pos, uint16_t byte);
void led14segs_display(void);

