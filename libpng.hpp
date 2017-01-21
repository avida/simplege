#include <png.h>
#include <string>

class LibPng
{
public:
	LibPng(const std::string path);
	LibPng() = default;
	~LibPng();
	int Load();
	int Load(const std::string path);
	int GetWidth() {return m_width;};
	int GetHeight() {return m_height;};
	void *GetData() {return row_pointers;};

private:
	std::string m_path;
	int m_height, m_width;
	png_byte color_type;
	png_byte bit_depth;
	png_byte *row_pointers;	
};