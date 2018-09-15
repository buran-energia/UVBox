#include <U8glib.h>
#include <EEPROM.h>
//#include <Thread.h>
//#include <ThreadController.h>
#include "gui.h"

#define BUTTON_EDIT_PIN 7
#define BUTTON_UP_PIN 8
#define BUTTON_DOWN_PIN A2
#define BUTTON_START_PIN A3

#define BUTTON_EDIT 0
#define BUTTON_UP 1
#define BUTTON_DOWN 2
#define BUTTON_START 3

void program_init();
void gui_draw();

void edit_button_pressed();
void up_button_pressed();
void down_button_pressed();
void start_button_pressed();

void set_brightness();

typedef __attribute__((__packed__)) struct {
	unsigned long time;
	uint8_t state;
} button_state_t;

button_state_t buttons[4];

/*Thread gui_thread;
Thread buttons_thread;
ThreadController thread_controller = ThreadController();*/

extern uint8_t exposure_begun;
extern int first_countdown;
extern int time_left;
extern uint32_t exposure_start_time;
extern unsigned char current_screen;
extern settings_t settings;
extern uint8_t finished_exposing;

void read_buttons()
{
	uint8_t edit_state, up_state, down_state, start_state;

	edit_state = digitalRead(BUTTON_EDIT_PIN);
	up_state = digitalRead(BUTTON_UP_PIN);
	down_state = digitalRead(BUTTON_DOWN_PIN);
	start_state = digitalRead(BUTTON_START_PIN);

	if (edit_state != buttons[BUTTON_EDIT].state) {
		if (edit_state == HIGH) {
			buttons[BUTTON_EDIT].time = millis();
			buttons[BUTTON_EDIT].state = HIGH;
		}
		else {
			buttons[BUTTON_EDIT].state = LOW;

			if (millis() - buttons[BUTTON_EDIT].time > 20) {
				edit_button_pressed();
			}
		}
	}

	if (up_state != buttons[BUTTON_UP].state) {
		if (up_state == HIGH) {
			buttons[BUTTON_UP].time = millis();
			buttons[BUTTON_UP].state = HIGH;
		}
		else {
			buttons[BUTTON_UP].state = LOW;

			if (millis() - buttons[BUTTON_UP].time > 20) {
				up_button_pressed();
			}
		}
	}

	if (down_state != buttons[BUTTON_DOWN].state) {
		if (down_state == HIGH) {
			buttons[BUTTON_DOWN].time = millis();
			buttons[BUTTON_DOWN].state = HIGH;
		}
		else {
			buttons[BUTTON_DOWN].state = LOW;

			if (millis() - buttons[BUTTON_DOWN].time > 20) {
				down_button_pressed();
			}
		}
	}

	if (start_state != buttons[BUTTON_START].state) {
		if (start_state == HIGH) {
			buttons[BUTTON_START].time = millis();
			buttons[BUTTON_START].state = HIGH;
		}
		else {
			buttons[BUTTON_START].state = LOW;

			if (millis() - buttons[BUTTON_START].time > 20) {
				start_button_pressed();
			}
		}
	}

}
/*
void setup_threads()
{
	buttons_thread = Thread();
	buttons_thread.enabled = true;
	buttons_thread.setInterval(10);
	buttons_thread.onRun(read_buttons);

	gui_thread = Thread();
	gui_thread.enabled = true;
	gui_thread.setInterval(100);
	gui_thread.onRun(gui_draw);

	thread_controller.add(&buttons_thread);
	thread_controller.add(&gui_thread);
}*/

void setup() 
{
	memset(&buttons, 0, sizeof(buttons));

	pinMode(BUTTON_EDIT_PIN, INPUT);
	pinMode(BUTTON_UP_PIN, INPUT);
	pinMode(BUTTON_DOWN_PIN, INPUT);
	pinMode(BUTTON_START_PIN, INPUT);

	program_init();

	display_intro();
	//setup_threads();
}

void loop() 
{
	gui_draw();
	read_buttons();
	//thread_controller.run();

	if (exposure_begun) {
		if (first_countdown > -1) {
			first_countdown = 9 - ((millis() - exposure_start_time) / 1000);

			if (first_countdown == -1) {
				exposure_start_time = millis();
				analogWrite(BRIGHTNESS_PIN, 0);
				analogWrite(UV_LED_PIN, 255);
			}
		}
		else if (time_left > -1) {
			time_left = settings.timers[current_screen] - (millis() - exposure_start_time) / 1000;

			if (time_left < 0) {
				exposure_begun = 0;
				finished_exposing = 1;
				analogWrite(LED_FAN_PIN, 0);
				analogWrite(UV_LED_PIN, 0);
				set_brightness();
			}
		}
	}
}

