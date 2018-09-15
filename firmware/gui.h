#ifndef _GUI_
#define _GUI_

#define SDL
#define DBG

#ifdef DBG
#ifdef SDL
#define DEBUG(x) (printf("%s\n", x))
#define OUTPUT
#define HIGH
#define digitalWrite(x,a)
#define analogWrite(x,d)
#define millis(x) 0
#define pinMode(x,a)
#define map(x,i,j,z,r) 0
#else
#define DEBUG(x) (Serial.println(x))
#endif // SDL
#else
#define DEBUG(x)
#endif // DBG

#ifdef SDL
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define delay(x) (usleep(x * 1000))
#else
#include "Arduino.h"
#include <EEPROM.h>
#endif // SDL

#define BRIGHTNESS_PIN 3
#define OLED_PIN 2
#define LED_FAN_PIN 6
#define UV_LED_PIN 9

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SDL_SCREEN_UPDATE_DELAY 20

void draw_main();
void display_intro();

#ifdef SDL
extern U8GLIB u8g;
#else
//extern U8GLIB_SSD1306_128X64 u8g;
extern U8GLIB_SH1106_128X64_2X u8g;
#endif // SDL

#define MAX_TIMER (60 * 60)
#define MAX_BRIGHTNESS 90

typedef __attribute__((__packed__)) struct {
	int brightness;
	unsigned char mute;
	int timers[3];
} settings_t;

typedef enum {
	Timer,
	Light,
	Sound,
} screen_type_t;

#define MAX_SCREENS 5

// *** INTRO DEFS
#define WARNING_ICON_Y_POS 4
#define WARNING_ICON_WIDTH 50
#define WARNING_ICON_HEIGHT 44
#define WARNING_ICON_FINAL_X_EDGE 4

#define INTRO_PHASE1_DELAY 2000
#define INTRO_ANIMATION_DELAY 0
#define INTRO_WARNING_TEXT_DELAY 4000

typedef enum {
	Started,
	MovingAnimation,
	ShowingText,
	Finished
} intro_phase_t;

// *** END OF INTRO DEFS

#define TITLE_ICON_WIDTH 40
#define TITLE_ICON_HEIGHT 40

const uint8_t SOUND_ICON[] U8G_PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x03,
	0x00, 0x00, 0x00, 0x00, 0x06,
	0x00, 0x00, 0x08, 0x00, 0x0C,
	0x00, 0x00, 0x0C, 0x00, 0x08,
	0x00, 0x00, 0x0E, 0x00, 0x18,
	0x00, 0x80, 0x0F, 0x30, 0x10,
	0x00, 0xC0, 0x0C, 0x60, 0x30,
	0x00, 0x60, 0x0C, 0x60, 0x20,
	0x00, 0x30, 0x0C, 0xC0, 0x60,
	0x00, 0x1C, 0x8C, 0xC1, 0x60,
	0xFE, 0x07, 0x0C, 0x81, 0x40,
	0xFE, 0x03, 0x0C, 0x83, 0x41,
	0x02, 0x00, 0x0C, 0x02, 0xC1,
	0x02, 0x00, 0x0C, 0x06, 0xC1,
	0x02, 0x00, 0x0C, 0x06, 0xC1,
	0x02, 0x00, 0x0C, 0x06, 0xC1,
	0x02, 0x00, 0x0C, 0x06, 0xC1,
	0x02, 0x00, 0x0C, 0x06, 0xC1,
	0x02, 0x00, 0x0C, 0x06, 0xC1,
	0x02, 0x00, 0x0C, 0x06, 0xC1,
	0x02, 0x00, 0x0C, 0x02, 0xC1,
	0x02, 0x00, 0x0C, 0x82, 0xC1,
	0xFE, 0x03, 0x0C, 0x83, 0x41,
	0x00, 0x0E, 0x8C, 0x81, 0x40,
	0x00, 0x18, 0x0C, 0xC1, 0x60,
	0x00, 0x30, 0x0C, 0xC0, 0x20,
	0x00, 0x60, 0x0C, 0x60, 0x20,
	0x00, 0xC0, 0x0D, 0x20, 0x30,
	0x00, 0x00, 0x0F, 0x30, 0x10,
	0x00, 0x00, 0x0E, 0x00, 0x18,
	0x00, 0x00, 0x0C, 0x00, 0x0C,
	0x00, 0x00, 0x08, 0x00, 0x0C,
	0x00, 0x00, 0x00, 0x00, 0x06,
	0x00, 0x00, 0x00, 0x00, 0x02,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t LIGHT_ICON[] U8G_PROGMEM = {
	0x00, 0x00, 0x3E, 0x00, 0x00,
	0x00, 0xC0, 0xFF, 0x01, 0x00,
	0x00, 0x70, 0x00, 0x07, 0x00,
	0x00, 0x18, 0x00, 0x0C, 0x00,
	0x00, 0x0C, 0x00, 0x18, 0x00,
	0x00, 0x06, 0x00, 0x30, 0x00,
	0x00, 0x03, 0x00, 0x60, 0x00,
	0x80, 0x01, 0x00, 0xC0, 0x00,
	0x80, 0x00, 0x00, 0x80, 0x00,
	0x80, 0x00, 0x00, 0x80, 0x00,
	0xC0, 0x00, 0x00, 0x80, 0x01,
	0x40, 0x00, 0x1C, 0x00, 0x01,
	0x40, 0x00, 0x3E, 0x00, 0x01,
	0x40, 0x00, 0x22, 0x00, 0x01,
	0x40, 0x00, 0x22, 0x00, 0x01,
	0x40, 0x00, 0x3E, 0x00, 0x01,
	0x40, 0x00, 0x08, 0x00, 0x01,
	0xC0, 0x00, 0x08, 0x80, 0x01,
	0x80, 0x00, 0x08, 0x80, 0x00,
	0x80, 0x01, 0x08, 0xC0, 0x00,
	0x00, 0x01, 0x08, 0x40, 0x00,
	0x00, 0x03, 0x08, 0x60, 0x00,
	0x00, 0x06, 0x08, 0x30, 0x00,
	0x00, 0x0C, 0x08, 0x18, 0x00,
	0x00, 0x18, 0x08, 0x0C, 0x00,
	0x00, 0x30, 0x08, 0x06, 0x00,
	0x00, 0x20, 0x08, 0x03, 0x00,
	0x00, 0x60, 0x08, 0x03, 0x00,
	0x00, 0x40, 0x08, 0x01, 0x00,
	0x00, 0x40, 0x08, 0x01, 0x00,
	0x00, 0x40, 0x08, 0x01, 0x00,
	0x00, 0x40, 0x08, 0x01, 0x00,
	0x00, 0x40, 0x08, 0x01, 0x00,
	0x00, 0xC0, 0xFF, 0x01, 0x00,
	0x00, 0x40, 0x00, 0x01, 0x00,
	0x00, 0x40, 0x00, 0x01, 0x00,
	0x00, 0x40, 0x00, 0x01, 0x00,
	0x00, 0x40, 0x00, 0x01, 0x00,
	0x00, 0xC0, 0xFF, 0x01, 0x00,
	0x00, 0xC0, 0xFF, 0x01, 0x00,
};

const uint8_t STOPWATCH_ICON[] U8G_PROGMEM = {
	0xE0, 0x1F, 0x00, 0xF8, 0x07,
	0xF8, 0x1F, 0x00, 0xF8, 0x1F,
	0x1C, 0x1C, 0x00, 0x38, 0x38,
	0x06, 0x0E, 0x00, 0x70, 0x60,
	0x06, 0x07, 0x00, 0xE0, 0x60,
	0x83, 0x83, 0xFF, 0xC1, 0xC1,
	0xC3, 0xF1, 0xC3, 0x8F, 0xC3,
	0xE3, 0x38, 0x00, 0x1C, 0xC7,
	0x73, 0x0E, 0x00, 0x70, 0xCE,
	0x3B, 0x07, 0x00, 0xE0, 0xDC,
	0x9F, 0x01, 0x18, 0x80, 0xF9,
	0xCF, 0x00, 0x18, 0x00, 0xF3,
	0x67, 0x00, 0x18, 0x00, 0xE6,
	0x60, 0x00, 0x18, 0x00, 0x06,
	0x30, 0x00, 0x18, 0x00, 0x0C,
	0x30, 0x00, 0x18, 0x00, 0x0C,
	0x18, 0x00, 0x18, 0x00, 0x18,
	0x18, 0x00, 0x18, 0x00, 0x18,
	0x08, 0x00, 0x18, 0x00, 0x18,
	0x08, 0x00, 0x18, 0x00, 0x10,
	0x0C, 0x00, 0x18, 0x00, 0x30,
	0x0C, 0x00, 0x18, 0x00, 0x30,
	0x0C, 0xFC, 0x1F, 0x00, 0x30,
	0x0C, 0xFC, 0x1F, 0x00, 0x30,
	0x08, 0x00, 0x00, 0x00, 0x10,
	0x08, 0x00, 0x00, 0x00, 0x10,
	0x08, 0x00, 0x00, 0x00, 0x18,
	0x18, 0x00, 0x00, 0x00, 0x18,
	0x18, 0x00, 0x00, 0x00, 0x08,
	0x30, 0x00, 0x00, 0x00, 0x0C,
	0x30, 0x00, 0x00, 0x00, 0x0C,
	0x60, 0x00, 0x00, 0x00, 0x06,
	0xC0, 0x00, 0x00, 0x00, 0x03,
	0xC0, 0x00, 0x00, 0x80, 0x03,
	0xC0, 0x03, 0x00, 0xC0, 0x03,
	0x60, 0x07, 0x00, 0xE0, 0x06,
	0x60, 0x0C, 0x00, 0x38, 0x06,
	0x30, 0x78, 0x00, 0x1E, 0x0C,
	0x18, 0xE0, 0xFF, 0x07, 0x18,
	0x08, 0x00, 0xFF, 0x00, 0x10,
};


const uint8_t TIMER_ICON[] U8G_PROGMEM = {
	0x00, 0xFE, 0x00, 0x00,
	0xC0, 0x01, 0x07, 0x00,
	0x60, 0x10, 0x0C, 0x00,
	0x90, 0x10, 0x12, 0x00,
	0x88, 0x38, 0x22, 0x00,
	0x04, 0x10, 0x40, 0x00,
	0x06, 0x10, 0xC0, 0x00,
	0x1A, 0x10, 0xA0, 0x00,
	0x02, 0x10, 0x80, 0x00,
	0x01, 0x10, 0x07, 0x01,
	0x01, 0x90, 0x03, 0x01,
	0x01, 0xF0, 0x00, 0x01,
	0x05, 0x30, 0x40, 0x01,
	0x01, 0x18, 0x00, 0x01,
	0x01, 0x10, 0x00, 0x01,
	0x01, 0x00, 0x00, 0x01,
	0x02, 0x00, 0x80, 0x00,
	0x0A, 0x00, 0xA0, 0x00,
	0x06, 0x00, 0xE0, 0x00,
	0x04, 0x00, 0x40, 0x00,
	0x08, 0x00, 0x20, 0x00,
	0x90, 0x00, 0x12, 0x00,
	0x60, 0x10, 0x0C, 0x00,
	0xC0, 0x01, 0x07, 0x00,
	0x00, 0xFE, 0x00, 0x00,
};

const uint8_t WARNING_ICON[] U8G_PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xFE, 0xFF, 0x01, 0x00, 0x00,
	0x00, 0x80, 0xFF, 0xFF, 0x07, 0x00, 0x00,
	0x00, 0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00,
	0x00, 0xF0, 0x00, 0x00, 0x38, 0x00, 0x00,
	0x00, 0xF8, 0x00, 0x00, 0x7C, 0x00, 0x00,
	0x00, 0xFC, 0x01, 0x00, 0xFC, 0x00, 0x00,
	0x00, 0xFE, 0x01, 0x00, 0xFE, 0x01, 0x00,
	0x00, 0xFF, 0x03, 0x00, 0xFE, 0x03, 0x00,
	0x00, 0xFF, 0x07, 0x00, 0xFF, 0x07, 0x00,
	0x80, 0xFF, 0x07, 0x80, 0xFF, 0x07, 0x00,
	0xC0, 0xFF, 0x0F, 0x80, 0xFF, 0x0F, 0x00,
	0xC0, 0xFF, 0x0F, 0xC0, 0xFF, 0x0F, 0x00,
	0xC0, 0xFF, 0x1F, 0xC0, 0xFF, 0x1F, 0x00,
	0xE0, 0xFF, 0x3F, 0xE0, 0xFF, 0x1F, 0x00,
	0xE0, 0xFF, 0x3F, 0xF0, 0xFF, 0x3F, 0x00,
	0xE0, 0xFF, 0x7F, 0xF0, 0xFF, 0x3F, 0x00,
	0xF0, 0xFF, 0x7F, 0xF8, 0xFF, 0x3F, 0x00,
	0xF0, 0xFF, 0xFF, 0xF8, 0xFF, 0x3F, 0x00,
	0xF0, 0xFF, 0xFF, 0xFC, 0xFF, 0x3F, 0x00,
	0xF0, 0xFF, 0xFF, 0xFD, 0xFF, 0x3F, 0x00,
	0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00,
	0x70, 0x00, 0x00, 0x03, 0x00, 0x30, 0x00,
	0x70, 0x00, 0x00, 0x07, 0x00, 0x38, 0x00,
	0xF0, 0x00, 0x80, 0x07, 0x00, 0x3C, 0x00,
	0xE0, 0x01, 0x80, 0x0F, 0x00, 0x3C, 0x00,
	0xE0, 0x01, 0xC0, 0x0F, 0x00, 0x3E, 0x00,
	0xE0, 0x03, 0xE0, 0x1F, 0x00, 0x1E, 0x00,
	0xC0, 0x03, 0xE0, 0x3F, 0x00, 0x1F, 0x00,
	0xC0, 0x07, 0xF0, 0x3F, 0x00, 0x0F, 0x00,
	0xC0, 0x07, 0xF0, 0x7F, 0x80, 0x0F, 0x00,
	0x80, 0x0F, 0xF8, 0x7F, 0xC0, 0x07, 0x00,
	0x00, 0x1F, 0xF8, 0xFF, 0xC0, 0x07, 0x00,
	0x00, 0x1F, 0xFC, 0xFF, 0xE0, 0x03, 0x00,
	0x00, 0x3E, 0xFE, 0xFF, 0xE1, 0x01, 0x00,
	0x00, 0x3C, 0xFE, 0xFF, 0xF3, 0x00, 0x00,
	0x00, 0x78, 0xFF, 0xFF, 0x7B, 0x00, 0x00,
	0x00, 0xF0, 0xFF, 0xFF, 0x3F, 0x00, 0x00,
	0x00, 0xC0, 0xFF, 0xFF, 0x1F, 0x00, 0x00,
	0x00, 0x80, 0xFF, 0xFF, 0x07, 0x00, 0x00,
	0x00, 0x00, 0xFE, 0xFF, 0x01, 0x00, 0x00,
	0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t OK_ICON[] U8G_PROGMEM = {
	0x00, 0x00, 0xC0, 0xFF, 0x3F, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xF8, 0xFF, 0xFF, 0x01, 0x00, 0x00,
	0x00, 0x00, 0xFE, 0x00, 0xF0, 0x07, 0x00, 0x00,
	0x00, 0x80, 0x1F, 0x00, 0x80, 0x1F, 0x00, 0x00,
	0x00, 0xE0, 0x03, 0x00, 0x00, 0x7C, 0x00, 0x00,
	0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00,
	0x00, 0x78, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x00,
	0x00, 0x1C, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00,
	0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00,
	0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00,
	0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00,
	0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
	0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
	0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00,
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01,
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01,
	0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01,
	0x1C, 0x00, 0x00, 0x00, 0x00, 0x60, 0x80, 0x03,
	0x0C, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x03,
	0x0E, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x07,
	0x0E, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x07,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x06,
	0x06, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x06,
	0x07, 0x00, 0x00, 0x00, 0x80, 0x0F, 0x00, 0x0E,
	0x07, 0x00, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x0E,
	0x07, 0x00, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x0E,
	0x07, 0x00, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x0E,
	0x03, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x0C,
	0x03, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x0C,
	0x03, 0x00, 0x06, 0x00, 0x3E, 0x00, 0x00, 0x0C,
	0x07, 0x00, 0x0F, 0x00, 0x1F, 0x00, 0x00, 0x0E,
	0x07, 0x00, 0x1F, 0x80, 0x0F, 0x00, 0x00, 0x0E,
	0x07, 0x00, 0x3E, 0xC0, 0x07, 0x00, 0x00, 0x0E,
	0x07, 0x00, 0x7C, 0xE0, 0x03, 0x00, 0x00, 0x0E,
	0x06, 0x00, 0xF8, 0xF0, 0x01, 0x00, 0x00, 0x06,
	0x06, 0x00, 0xF0, 0xF9, 0x00, 0x00, 0x00, 0x06,
	0x0E, 0x00, 0xE0, 0x7F, 0x00, 0x00, 0x00, 0x07,
	0x0E, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0x07,
	0x0C, 0x00, 0x80, 0x1F, 0x00, 0x00, 0x00, 0x03,
	0x1C, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x80, 0x03,
	0x18, 0x00, 0x00, 0x06, 0x00, 0x00, 0x80, 0x01,
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01,
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01,
	0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00,
	0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
	0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
	0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00,
	0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00,
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00,
	0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
	0x00, 0x1C, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00,
	0x00, 0x78, 0x00, 0x00, 0x00, 0xE0, 0x01, 0x00,
	0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00,
	0x00, 0xE0, 0x03, 0x00, 0x00, 0x7C, 0x00, 0x00,
	0x00, 0x80, 0x1F, 0x00, 0x80, 0x1F, 0x00, 0x00,
	0x00, 0x00, 0xFE, 0x00, 0xF0, 0x07, 0x00, 0x00,
	0x00, 0x00, 0xF8, 0xFF, 0xFF, 0x01, 0x00, 0x00,
	0x00, 0x00, 0xC0, 0xFF, 0x3F, 0x00, 0x00, 0x00
};



/*const uint8_t WARNING_ICON[] U8G_PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,

0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00,

0x00, 0x00, 0x80, 0x07, 0x00, 0x00, 0x00,

0x00, 0x00, 0xC0, 0x0F, 0x00, 0x00, 0x00,

0x00, 0x00, 0xE0, 0x1F, 0x00, 0x00, 0x00,

0x00, 0x00, 0xE0, 0x1C, 0x00, 0x00, 0x00,

0x00, 0x00, 0xF0, 0x3C, 0x00, 0x00, 0x00,

0x00, 0x00, 0x70, 0x38, 0x00, 0x00, 0x00,

0x00, 0x00, 0x78, 0x70, 0x00, 0x00, 0x00,

0x00, 0x00, 0x38, 0x70, 0x00, 0x00, 0x00,

0x00, 0x00, 0x1C, 0xE0, 0x00, 0x00, 0x00,

0x00, 0x00, 0x9E, 0xE7, 0x01, 0x00, 0x00,

0x00, 0x00, 0xCE, 0xCF, 0x01, 0x00, 0x00,

0x00, 0x00, 0xCF, 0xCF, 0x03, 0x00, 0x00,

0x00, 0x00, 0xC7, 0x8F, 0x03, 0x00, 0x00,

0x00, 0x80, 0xC7, 0x8F, 0x07, 0x00, 0x00,

0x00, 0x80, 0xC3, 0x0F, 0x07, 0x00, 0x00,

0x00, 0xC0, 0xC1, 0x0F, 0x0E, 0x00, 0x00,

0x00, 0xE0, 0xC1, 0x0F, 0x1E, 0x00, 0x00,

0x00, 0xE0, 0xC0, 0x0F, 0x1C, 0x00, 0x00,

0x00, 0xF0, 0xC0, 0x07, 0x3C, 0x00, 0x00,

0x00, 0x70, 0xC0, 0x07, 0x38, 0x00, 0x00,

0x00, 0x78, 0x80, 0x07, 0x78, 0x00, 0x00,

0x00, 0x3C, 0x80, 0x07, 0x70, 0x00, 0x00,

0x00, 0x1C, 0x80, 0x07, 0xE0, 0x00, 0x00,

0x00, 0x1E, 0x80, 0x07, 0xE0, 0x01, 0x00,

0x00, 0x0E, 0x80, 0x07, 0xC0, 0x01, 0x00,

0x00, 0x0F, 0x80, 0x07, 0xC0, 0x03, 0x00,

0x00, 0x07, 0x80, 0x03, 0x80, 0x03, 0x00,

0x80, 0x07, 0x00, 0x00, 0x80, 0x07, 0x00,

0xC0, 0x03, 0x00, 0x00, 0x00, 0x07, 0x00,

0xC0, 0x01, 0x00, 0x03, 0x00, 0x0E, 0x00,

0xE0, 0x01, 0xC0, 0x0F, 0x00, 0x1E, 0x00,

0xE0, 0x00, 0xC0, 0x0F, 0x00, 0x1C, 0x00,

0xF0, 0x00, 0xC0, 0x0F, 0x00, 0x3C, 0x00,

0x70, 0x00, 0xC0, 0x0F, 0x00, 0x38, 0x00,

0x78, 0x00, 0xC0, 0x07, 0x00, 0x78, 0x00,

0x3C, 0x00, 0x00, 0x03, 0x00, 0x70, 0x00,

0x1C, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00,

0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,

0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01,

0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};*/

#endif