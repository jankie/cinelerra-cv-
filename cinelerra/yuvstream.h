#include <stdio.h>

#include "guicast.h"

#ifndef HAVE_STDINT_H
#define HAVE_STDINT_H
#endif /* HAVE_STDINT_H */

#include <mjpegtools/yuv4mpeg.h>
#include <mjpegtools/mpegconsts.h>

class YUVStream {
 public:
	YUVStream();
	~YUVStream();

	int open_read(char *path);
	int open_write(char *path);  // opened as pipe if path contains '|'
	void close_fd(); 

	int read_frame(uint8_t *yuv[3]);
	int read_frame_raw(uint8_t *data, long frame_size);
		
	int write_frame(uint8_t *yuv[3]);
	int write_frame_raw(uint8_t *data, long frame_size);

	int make_index();
	int seek_frame(int64_t frame_number);

	int read_header();
	int write_header();

	int get_width();
	void set_width(int width);

	int get_height();
	void set_height(int height);

	double get_frame_rate();
	void set_frame_rate(double frame_rate);

	double get_aspect_ratio();
	void set_aspect_ratio(double aspect_ratio);

	long frame_count;

 private: 
	y4m_stream_info_t stream_info;
	y4m_frame_info_t frame_info;
	int stream_fd;  // used for pipes
	FILE *stream_file; // used for files
	int sigpipe;
	ArrayList<off_t> *frame_index;
};
