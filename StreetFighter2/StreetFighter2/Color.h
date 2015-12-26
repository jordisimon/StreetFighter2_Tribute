#pragma once
class Color
{
public:
	enum class Predefined
	{
		RED,
		GREEN, 
		BLUE,
		BLACK,
		WHITE,
		YELLOW,
		CYAN,
		MAGENTA
	};

	Color();
	Color(Predefined col);
	~Color();

	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
};

