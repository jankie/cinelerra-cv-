
/*
 * CINELERRA
 * Copyright (C) 2008 Adam Williams <broadcast at earthling dot net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 */

#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H






#include "bchash.inc"
#include "fourier.h"
#include "guicast.h"
#include "mutex.h"
#include "pluginaclient.h"
#include "pluginwindow.h"
#include "vframe.inc"




class Spectrogram;
class SpectrogramFFT;


class SpectrogramLevel : public BC_FPot
{
public:
	SpectrogramLevel(Spectrogram *plugin, int x, int y);
	int handle_event();
	Spectrogram *plugin;
};


class SpectrogramWindow : public PluginWindow
{
public:
	SpectrogramWindow(Spectrogram *plugin, int x, int y);
	~SpectrogramWindow();

	void create_objects();
	void update_gui();

	SpectrogramLevel *level;
	Spectrogram *plugin;
	int done;
	BC_SubWindow *canvas;
};



PLUGIN_THREAD_HEADER(Spectrogram, SpectrogramThread, SpectrogramWindow)



class SpectrogramFFT : public CrossfadeFFT
{
public:
	SpectrogramFFT(Spectrogram *plugin);
	~SpectrogramFFT();
	
	int signal_process();
	int read_samples(int64_t output_sample, 
		int samples, 
		double *buffer);

	Spectrogram *plugin;
};


class SpectrogramConfig
{
public:
	SpectrogramConfig();
	double level;
};


class Spectrogram : public PluginAClient
{
public:
	Spectrogram(PluginServer *server);
	~Spectrogram();
	
	int is_realtime();
	int process_buffer(int64_t size, 
		double *buffer,
		int64_t start_position,
		int sample_rate);
	int load_defaults();
	int save_defaults();
	void read_data(KeyFrame *keyframe);
	void save_data(KeyFrame *keyframe);
	void update_gui();
	void render_gui(void *data, int size);	
	
	void reset();

	int done;

	int need_reconfigure;
	SpectrogramFFT *fft;
	float *data;
	int total_windows;
	PLUGIN_CLASS_MEMBERS(SpectrogramConfig, SpectrogramThread)
};


#endif
