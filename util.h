#pragma once

# include <graphics.h>
# include "atlas.h"
# include "camera.h"

namespace ut {

	inline void flip_image(IMAGE* src, IMAGE* dst) {
		int w = src->getwidth();
		int h = src->getheight();
		Resize(dst, w, h);
		DWORD* src_buffer = GetImageBuffer(src);
		DWORD* dst_buffer = GetImageBuffer(dst);
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				int idx_src = y * w + x;
				int idx_dst = y * w + (w - x - 1);
				dst_buffer[idx_dst] = src_buffer[idx_src];
			}
		}
	}

	void flip_atlas(Atlas& src, Atlas& dst);

	inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img) {
		int w = img->getwidth();
		int h = img->getheight();
		AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
			GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
	}

	inline void putimage_alpha(int dst_x, int dst_y, int width, int height, IMAGE* img, int src_x, int src_y) {
		int w = width > 0 ? width : img->getwidth();
		int h = height > 0 ? height : img->getheight();
		AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
			GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
	}

	inline void putimage_alpha(const Camera& camera,int dst_x, int dst_y, IMAGE* img) {
		int w = img->getwidth();
		int h = img->getheight();
		const Vector2& pos_camera = camera.get_position();
		AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x - pos_camera.x), (int)(dst_y - pos_camera.y), w, h,
			GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
	}

	inline void draw_line(const Camera& camera, int x1, int y1, int x2, int y2) {
		const Vector2& pos_camera = camera.get_position();
		line(x1 - pos_camera.x, y1 - pos_camera.y, x2 - pos_camera.x, y2 - pos_camera.y);
	}
}

