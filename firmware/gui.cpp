#include <U8glib.h>
#include "gui.h"

const char *STRONG_STR = "\xbc\xbe\xc9\xbd\xcb\xb9"; // "MOSHNIY"
const char *DANGER_STR = "\xbe\xbf\xb0\xc1\xbd\xbe"; // "OPASNO"
const char *ULTRA_STR = "\xc3\xbb\xcc\xc2\xc0\xb0-"; // "ULTRA-"
const char *VIOLETT_STR = "\xc4\xb8\xbe\xbb\xb5\xc2"; // "FIOLET"
const char *UV_PARAMS_STR = "";

const char *TIMER_STR = "\xc2\xd0\xd9\xdc\xd5\xe0"; // "Taimer"
const char *LIGHT_STR = "\xbf\xde\xd4\xe1\xd2\xd5\xe2\xda\xd0"; // "Podsvetka"
const char *SOUND_STR = "\xb7\xd2\xe3\xda"; // "Zvuk"

const char *ON_STR = "\xb2\xda\xdb\xee\xe7\xd5\xdd"; // "Vkliuchen"
const char *OFF_STR = "\xb2\xeb\xda\xdb\xee\xe7\xd5\xdd"; // "Vykliuchen"

int intro_anim_offset;
intro_phase_t intro_phase;

screen_type_t screens[MAX_SCREENS] = { Timer, Timer, Timer, Light, Sound };
unsigned char current_screen;
unsigned char edit_mode;
extern settings_t settings;
extern uint8_t exposure_begun;
extern int first_countdown;
extern int time_left;
extern uint8_t finished_exposing;

void draw_up_arrow(uint16_t x, uint16_t y)
{
	u8g.drawTriangle(x, y + 6, x + 5, y, x + 11, y + 6);
}

void draw_down_arrow(uint16_t x, uint16_t y)
{
	u8g.drawTriangle(x, y, x + 5, y + 6, x + 11, y);
}

#define TITLE_ICON_X_POS 2
#define TITLE_ICON_Y_POS 10
#define TITLE_TEXT_X_POS (TITLE_ICON_X_POS + TITLE_ICON_WIDTH + 6)
#define TITLE_TEXT_Y_POS 2
#define CALC_TITLE_TEXT_X_POS(x) (TITLE_TEXT_X_POS + ((SCREEN_WIDTH - TITLE_TEXT_X_POS) / 2) - (u8g.getStrWidth(x) / 2))

void draw_title()
{
	char buf[32];

	u8g.setFont(u8g_font_unifont_0_8);

	switch (current_screen) {
		case 0:
		case 1:
		case 2:
			u8g.drawXBMP(TITLE_ICON_X_POS, TITLE_ICON_Y_POS, TITLE_ICON_WIDTH, TITLE_ICON_HEIGHT, STOPWATCH_ICON);

			sprintf(buf, "%s %d", TIMER_STR, current_screen + 1);
			u8g.drawStr(CALC_TITLE_TEXT_X_POS(buf), TITLE_TEXT_Y_POS + u8g.getFontLineSpacing(), buf);
			break;

		case 3:
			u8g.drawXBMP(TITLE_ICON_X_POS, TITLE_ICON_Y_POS, TITLE_ICON_WIDTH, TITLE_ICON_HEIGHT, LIGHT_ICON);
			u8g.drawStr(CALC_TITLE_TEXT_X_POS(LIGHT_STR), TITLE_TEXT_Y_POS + u8g.getFontLineSpacing(), LIGHT_STR);
			break;

		case 4:
			u8g.drawXBMP(TITLE_ICON_X_POS, TITLE_ICON_Y_POS, TITLE_ICON_WIDTH, TITLE_ICON_HEIGHT, SOUND_ICON);
			u8g.drawStr(CALC_TITLE_TEXT_X_POS(SOUND_STR), TITLE_TEXT_Y_POS + u8g.getFontLineSpacing(), SOUND_STR);
			break;
	}

}

#define ARROW_X_POS 83
#define ARROW_UP_Y_POS 20
#define ARROW_DOWN_Y_POS 58

#define ACTIVE_AREA_X_POS 54
#define ACTIVE_AREA_Y_POS 32
#define ACTIVE_AREA_WIDTH 68
#define ACTIVE_AREA_HEIGHT 20

void draw_brightness()
{
	int bars;

	u8g.drawFrame(ACTIVE_AREA_X_POS, ACTIVE_AREA_Y_POS, ACTIVE_AREA_WIDTH, ACTIVE_AREA_HEIGHT);

	bars = settings.brightness / 10;

	for (int x = ACTIVE_AREA_X_POS + 4; x < ACTIVE_AREA_X_POS + ACTIVE_AREA_WIDTH - 3; x += 7) {
		if (bars > 0) {
			u8g.drawBox(x, ACTIVE_AREA_Y_POS + 3, 4, ACTIVE_AREA_HEIGHT - 6);
			bars--;
		}
		else {
			break;
		}
	}
}

void draw_active_area()
{
	if (screens[current_screen] == Timer) {
		char buf[32];

		u8g.setFont(u8g_font_freedoomr10r);
		u8g.setScale2x2();
		sprintf(buf, "%02d:00", settings.timers[current_screen] / 60);
		u8g.drawStr(ACTIVE_AREA_X_POS / 2, 28, buf);
		u8g.undoScale();
	}
	else if (screens[current_screen] == Light) {
		draw_brightness();
	}
	else if (screens[current_screen] == Sound) {
		u8g.setFont(u8g_font_unifont_0_8);

		if (settings.mute == 1) {
			u8g.drawStr(CALC_TITLE_TEXT_X_POS(OFF_STR), ACTIVE_AREA_Y_POS + u8g.getFontLineSpacing(), OFF_STR);
		}
		else {
			u8g.drawStr(CALC_TITLE_TEXT_X_POS(ON_STR), ACTIVE_AREA_Y_POS + u8g.getFontLineSpacing(), ON_STR);
		}
	}

	if (edit_mode) {
		//u8g.drawBox(ACTIVE_AREA_X_POS, ACTIVE_AREA_Y_POS - 6, ACTIVE_AREA_WIDTH, 2);
		//u8g.drawBox(ACTIVE_AREA_X_POS, ACTIVE_AREA_Y_POS + ACTIVE_AREA_HEIGHT + 4, ACTIVE_AREA_WIDTH, 2);

		//u8g.drawBox(ACTIVE_AREA_X_POS, ACTIVE_AREA_Y_POS - 5, ACTIVE_AREA_WIDTH, 2);
		//u8g.drawBox(ACTIVE_AREA_X_POS, ACTIVE_AREA_Y_POS + ACTIVE_AREA_HEIGHT + 3, ACTIVE_AREA_WIDTH, 2);

		for (int i = ACTIVE_AREA_X_POS; i < ACTIVE_AREA_X_POS + ACTIVE_AREA_WIDTH; i += 10) {
			u8g.drawBox(i, ACTIVE_AREA_Y_POS - 6, 6, 2);
			u8g.drawBox(i, ACTIVE_AREA_Y_POS + ACTIVE_AREA_HEIGHT + 4, 6, 2);
		}
	}
	else {
		if (current_screen != 0) {
			draw_up_arrow(ARROW_X_POS, ARROW_UP_Y_POS);
		}

		if (current_screen != MAX_SCREENS - 1) {
			draw_down_arrow(ARROW_X_POS, ARROW_DOWN_Y_POS);
		}
	}
}

void draw_main()
{
	if (finished_exposing) {
		u8g.drawXBMP((SCREEN_WIDTH / 2) - (WARNING_ICON_WIDTH / 2), 2, 60, 59, OK_ICON);
		return;
	}

	if (exposure_begun) {
		if (first_countdown > -1) {
			char buf[16];

			u8g.setFont(u8g_font_freedoomr25n);
			u8g.setScale2x2();
			sprintf(buf, "%d", first_countdown);
			u8g.drawStr(23, 30, buf);
			u8g.undoScale();
		}
		else {
			char buf[16];

			u8g.setFont(u8g_font_freedoomr25n);
			sprintf(buf, "%02d:%02d", time_left / 60, time_left % 60);
			u8g.drawStr(20, 45, buf);
		}
	}
	else {
		draw_title();
		draw_active_area();
	}
}

void draw_intro()
{
	u8g.setFont(u8g_font_unifont_0_8);
	u8g.drawXBMP((SCREEN_WIDTH / 2) - (WARNING_ICON_WIDTH / 2) + intro_anim_offset,
	             WARNING_ICON_Y_POS,
		         WARNING_ICON_WIDTH,
		         WARNING_ICON_HEIGHT,
		         WARNING_ICON);
	u8g.drawStr((SCREEN_WIDTH / 2) - (u8g.getStrWidth(DANGER_STR) / 2) + intro_anim_offset,
		        WARNING_ICON_Y_POS + WARNING_ICON_HEIGHT + u8g.getFontLineSpacing(),
		        DANGER_STR);

	if (intro_phase == ShowingText) {
		u8g.drawStr(WARNING_ICON_Y_POS + WARNING_ICON_WIDTH + 6, WARNING_ICON_Y_POS + u8g.getFontLineSpacing() + 2, STRONG_STR);
		u8g.drawStr(WARNING_ICON_Y_POS + WARNING_ICON_WIDTH + 6, WARNING_ICON_Y_POS + (u8g.getFontLineSpacing() * 2) + 4, ULTRA_STR);
		u8g.drawStr(WARNING_ICON_Y_POS + WARNING_ICON_WIDTH + 6, WARNING_ICON_Y_POS + (u8g.getFontLineSpacing() * 3) + 6, VIOLETT_STR);
		//u8g.drawStr(WARNING_ICON_Y_POS + WARNING_ICON_WIDTH + 6, WARNING_ICON_Y_POS + (u8g.getFontLineSpacing() * 3), UV_PARAMS_STR);
	}
}


void display_intro()
{
	intro_phase = Started;
	intro_anim_offset = 0;

	while (intro_phase != Finished) {
		u8g.firstPage();
		do {
			draw_intro();
		} while (u8g.nextPage());
		delay(SDL_SCREEN_UPDATE_DELAY);

		switch (intro_phase) {
			case Started:
				delay(INTRO_PHASE1_DELAY);
				intro_phase = MovingAnimation;
				break;

			case MovingAnimation:
				// Check if Warning icon animation reached the edge
				if (((SCREEN_WIDTH / 2) - (WARNING_ICON_WIDTH / 2) + intro_anim_offset) <= WARNING_ICON_FINAL_X_EDGE) {
					intro_phase = ShowingText;
				}

				intro_anim_offset -= 3;
				delay(INTRO_ANIMATION_DELAY);
				break;

			case ShowingText:
				delay(INTRO_WARNING_TEXT_DELAY);
				intro_phase = Finished;
				break;
		}
	}

}