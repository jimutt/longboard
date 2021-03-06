/*
 * button_lib.c
 *
 * Created: 2015-10-19 15:03:24
 *  Author: peol0071
 */ 
#include <asf.h>
#include "button_lib.h"

void button_init(button_lib_t * make_me_normal, uint8_t pin)
{
	struct system_pinmux_config config;
	system_pinmux_get_config_defaults(&config);
	
	config.direction   = SYSTEM_PINMUX_PIN_DIR_INPUT;
	config.input_pull   = SYSTEM_PINMUX_PIN_PULL_UP;
	config.mux_position = SYSTEM_PINMUX_GPIO;
	
	
	make_me_normal->gpio_pin = pin;
	system_pinmux_pin_set_config(make_me_normal->gpio_pin, &config);	//Todo, set this to read from struct

	make_me_normal->pressed = false;
	make_me_normal->read = false;
	make_me_normal->active_high = false;
	make_me_normal->button_debounce = false;
	

}

//Read and handle buttonpress
bool button_read_button(button_lib_t * read_me)
{
	if (read_me->pressed && !read_me->read)
	{
		read_me->read = true;
		return true;
	}
	return false;
}

//Wait for button on display to be pressed
void wait_for_button_press(const button_lib_t * read_me)
{
	while (!button_read_button(read_me));
}


//Handler for button 
inline void button_handler(button_lib_t * btn_to_read)
{
	//Read button! Handle debounce and scroll
	//Read.?
	if (port_pin_get_input_level(btn_to_read->gpio_pin) == btn_to_read->active_high)
	{
		btn_to_read->button_debounce++;
		if (btn_to_read->button_debounce >= 35 && !btn_to_read->pressed)
		{
			btn_to_read->pressed = true;
			btn_to_read->read = false;
		}
		
		}else{
		if (btn_to_read->read)
		{
			btn_to_read->pressed = false;
		}
		btn_to_read->button_debounce = 0;
	}
}