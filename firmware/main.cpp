
// had to remove ": Print" from U8glib.h and "#include <Print.h>" in Linux in order for it to compile there

#include <U8glib.h>
#include "gui.h"

#ifdef SDL
int u8g_sdl_get_key(void);

U8GLIB u8g(&u8g_dev_sdl_8bit);
#else
//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
U8GLIB_SH1106_128X64_2X u8g(A1, A0, 4);
#endif // SDL

extern unsigned char current_screen;
extern screen_type_t screens[MAX_SCREENS];
extern unsigned char edit_mode;

settings_t settings, eeprom_settings;
uint8_t exposure_begun;
int first_countdown;
int time_left;
uint32_t exposure_start_time;
uint8_t finished_exposing;

void save_settings()
{
#ifndef SDL
	for (int i = 0; i < sizeof(settings); i++) {
		if (((unsigned char *) &eeprom_settings)[i] != ((unsigned char *) &settings)[i]) {
			DEBUG("changed");
			((unsigned char *) &eeprom_settings)[i] = ((unsigned char *) &settings)[i];
			EEPROM.write(i, ((unsigned char *)&settings)[i]);
		}
	}
#endif // SDL
}

void load_settings()
{
#ifndef SDL
	for (int i = 0; i < sizeof(settings); i++) {
		((unsigned char *) &settings)[i] = EEPROM.read(i);
	}

	for (int i = 0; i < 3; i++) {
		if (settings.timers[i] > MAX_TIMER) {
			settings.timers[i] = MAX_TIMER;
		}
		else if (settings.timers[i] < 60) {
			settings.timers[i] = 60;
		}
	}

	if (settings.mute > 1) {
		settings.mute = 1;
	}

	if (settings.brightness > MAX_BRIGHTNESS) {
		settings.brightness = MAX_BRIGHTNESS;
	}
	else if (settings.brightness < 0) {
		settings.brightness = 0;
	}

	memcpy(&eeprom_settings, &settings, sizeof(settings));
#endif // SDL
}

void set_brightness()
{
	int value;

	if (settings.brightness < 70) {
		//value = map(settings.brightness, 0, 255, 0, 255);
		value = settings.brightness;

	}
	else {
		value = map(settings.brightness, 0, MAX_BRIGHTNESS, 0, 255);
	}

	analogWrite(BRIGHTNESS_PIN, value);
}

void program_init()
{
#if defined(DBG) && !defined(SDL)
	Serial.begin(9600);
#endif
	DEBUG("program_init()");

	u8g.setDefaultForegroundColor();
	current_screen = 0;
	edit_mode = 0;
	exposure_begun = 0;
	time_left = 0;
	first_countdown = -1;
	load_settings();

	pinMode(OLED_PIN, OUTPUT); // OLED VCC
	digitalWrite(OLED_PIN, HIGH);

	set_brightness();
}

void gui_draw()
{
	u8g.firstPage();
	do {
		draw_main();
	} while (u8g.nextPage());
}

void start_button_pressed()
{
	if (finished_exposing) {
		finished_exposing = 0;
		return;
	}

	if (exposure_begun) {
		exposure_begun = 0;
		first_countdown = -1;
		time_left = 0;
		analogWrite(LED_FAN_PIN, 0);
		analogWrite(UV_LED_PIN, 0);
		set_brightness();
	}
	else if (screens[current_screen] == Timer && !edit_mode) {
		time_left = settings.timers[current_screen];
		first_countdown = 9;
		exposure_begun = 1;
		exposure_start_time = millis();
		analogWrite(LED_FAN_PIN, 255);
	}
}

void edit_button_pressed()
{
	if (finished_exposing) {
		finished_exposing = 0;
		return;
	}

	if (!exposure_begun) {
		if (screens[current_screen] == Sound) {
			settings.mute = !settings.mute;
			save_settings();
		}
		else {
			if (edit_mode) {
				save_settings();
			}

			edit_mode = !edit_mode;
		}
	}
}

void up_button_pressed()
{
	if (finished_exposing) {
		finished_exposing = 0;
		return;
	}

	if (!exposure_begun) {
		if (edit_mode) {
			if (screens[current_screen] == Timer) {
				settings.timers[current_screen] += 60;

				if (settings.timers[current_screen] > MAX_TIMER) {
					settings.timers[current_screen] = 60;
				}
			}
			else if (screens[current_screen] == Light) {
				settings.brightness += 10;

				if (settings.brightness > MAX_BRIGHTNESS) {
					settings.brightness = MAX_BRIGHTNESS;
				}

				set_brightness();
			}
		}
		else if (current_screen > 0) {
			current_screen--;
		}
	}
}

void down_button_pressed()
{
	if (finished_exposing) {
		finished_exposing = 0;
		return;
	}

	if (!exposure_begun) {
		if (edit_mode) {
			if (screens[current_screen] == Timer) {
				settings.timers[current_screen] -= 60;

				if (settings.timers[current_screen] < 60) {
					settings.timers[current_screen] = MAX_TIMER;
				}
			}
			else if (screens[current_screen] == Light) {
				settings.brightness -= 10;

				if (settings.brightness < 0) {
					settings.brightness = 0;
				}

				set_brightness();
			}
		}
		else if (current_screen < MAX_SCREENS - 1) {
			current_screen++;
		}
	}
}

#ifdef SDL
int main(void)
{  
	program_init();
	display_intro();

	while (1) {
		char key = u8g_sdl_get_key();

		if (key == 's') {
			down_button_pressed();
		} 
		else if (key == 'w') {
			up_button_pressed();
		}
		else if (key == 'q') {
			edit_button_pressed();
		}
		else if (key == 'a') {
			start_button_pressed();
		} else if (key > 0) {
			exit(0);
		}

		gui_draw();
		delay(SDL_SCREEN_UPDATE_DELAY);
	}
}
#endif // SDL