/*
 * LCD.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Ahmed Hassan
 */

#ifndef LCD_H_
#define LCD_H_
void lcd_vid_write_charachter (u8 data);
void lcd_vid_write_command (u8 command);
void lcd_vid_init(void);
void lcd_vid_write_string(u8 str[]);
void lcd_vid_write_number(s32 number);
void lcd_vid_set_position(u8 row, u8 col);
void lcd_vid_clear_screan (void);


#endif /* LCD_H_ */
