#ifndef BCSLIDER_H
#define BCSLIDER_H

#include "bcbitmap.inc"
#include "bcsubwindow.h"

class BC_ISlider;
class BC_FSlider;
class BC_PercentageSlider;

class BC_Slider : public BC_SubWindow
{
public:
	BC_Slider(int x, 
		int y, 
		int pixels, 
		int pointer_motion_range,  
		VFrame **images,
		int show_number, 
		int vertical,
		int use_caption);
	virtual ~BC_Slider();

	friend class BC_ISlider;
	friend class BC_FSlider;
	friend class BC_PercentageSlider;

	virtual int handle_event() { return 0; };

	int initialize();
	int get_button_pixels();
	virtual int value_to_pixel() { return 0; };
	int keypress_event();
	int cursor_enter_event();
	int cursor_leave_event();
	int button_press_event();
	int button_release_event();
	int get_pointer_motion_range();
	int cursor_motion_event();
	int repeat_event(long repeat_id);
	int reposition_window(int x, int y, int w = -1, int h = -1);
	int activate();
	int deactivate();
	virtual int increase_value() { return 0; };
	virtual int decrease_value() { return 0; };
	virtual char* get_caption() { return caption; };

private:

#define SLIDER_UP 0
#define SLIDER_HI 1
#define SLIDER_DN 2
#define SLIDER_BG_UP 0
#define SLIDER_BG_HI 1
#define SLIDER_BG_DN 2
#define SLIDER_IMAGES 6

	virtual int init_selection(int cursor_x, int cursor_y) { return 0; };
	virtual int update_selection(int cursor_x, int cursor_y) { return 0; };
	int set_images(VFrame **images);
	int draw_face();
	void show_value_tooltip();

	VFrame **images;
	BC_Pixmap **pixmaps;
	int show_number, vertical, pointer_motion_range, pixels;
	int keypress_tooltip_timer;
	int button_pixel;
	int status;
	int button_down;
	int min_pixel, max_pixel;
	int text_line, text_height;
	int use_caption;
	char caption[BCTEXTLEN];
	char temp_tooltip_text[BCTEXTLEN];
	int active;
	int enabled;
};


class BC_ISlider : public BC_Slider
{
public:
	BC_ISlider(int x, 
			int y,
			int vertical,
			int pixels, 
			int pointer_motion_range, 
			long minvalue, 
			long maxvalue, 
			long value,
			int use_caption = 0,
			VFrame **data = 0,
			int *output = 0);

	int update(long value);
	int update(int pointer_motion_range, long value, long minvalue, long maxvalue);
	long get_value();
	long get_length();
	int increase_value();
	int decrease_value();
	virtual int handle_event();
	char* get_caption();

private:
	int value_to_pixel();
	int init_selection(int cursor_x, int cursor_y);
	int update_selection(int cursor_x, int cursor_y);
	long minvalue, maxvalue, value;
	int *output;
};

class BC_FSlider : public BC_Slider
{
public:
	BC_FSlider(int x, 
			int y,
			int vertical,
			int pixels, 
			int pointer_motion_range, 
			float minvalue, 
			float maxvalue, 
			float value,
			int use_caption = 0,
			VFrame **data = 0);

	friend class BC_PercentageSlider;

	int update(float value);
	int update(int pointer_motion_range, float value, float minvalue, float maxvalue);
	float get_value();
	float get_length();
	virtual int increase_value();
	virtual int decrease_value();
	virtual char* get_caption();
	void set_precision(float value);

private:
	int value_to_pixel();
	int init_selection(int cursor_x, int cursor_y);
	int update_selection(int cursor_x, int cursor_y);
	float minvalue, maxvalue, value;
	float precision;
};

class BC_PercentageSlider : public BC_FSlider
{
public:
	BC_PercentageSlider(int x, 
			int y,
			int vertical,
			int pixels, 
			int pointer_motion_range, 
			float minvalue, 
			float maxvalue, 
			float value,
			int use_caption = 0,
			VFrame **data = 0);

	virtual int increase_value();
	virtual int decrease_value();
	char* get_caption();
private:
};


#endif