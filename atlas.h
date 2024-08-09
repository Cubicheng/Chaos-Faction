#pragma once

# include <vector>
# include <graphics.h>

class Atlas {
public:
	Atlas() = default;
	~Atlas() = default;

	void load_from_file(LPCTSTR path_template, int num) {
		img_list.clear();
		img_list.resize(num);

		TCHAR path_file[256];
		for (int i = 0; i < num; i++) {
			_stprintf_s(path_file, path_template, i + 1);
			loadimage(&img_list[i], path_file);
		}
	}

	void clear() {
		img_list.clear();
	}

	int get_size() {
		return (int)img_list.size();
	}

	IMAGE* get_image(int index) {
		if (index<0 || index>img_list.size() - 1) {
			return nullptr;
		}
		return &img_list[index];
	}

	void add_image(const IMAGE& img) {
		img_list.push_back(img);
	}

private:
	std::vector<IMAGE> img_list;
};