# include "util.h"
#pragma comment(lib,"MSIMG32.LIB")

namespace ut {
	
	void flip_atlas(Atlas& src, Atlas& dst) {
		dst.clear();
		for (int i = 0; i < src.get_size(); i++) {
			IMAGE img_flipped;
			flip_image(src.get_image(i), &img_flipped);
			dst.add_image(img_flipped);
		}
	}
}