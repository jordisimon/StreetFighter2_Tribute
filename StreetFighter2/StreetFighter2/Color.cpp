#include "Color.h"

Color::Color() : red{ 0 }, green{ 0 }, blue{ 0 }, alpha{ 255 }
{
}

Color::Color(Predefined col) : red{ 0 }, green{ 0 }, blue{ 0 }, alpha{ 255 }
{
	switch (col)
	{
	case Predefined::RED:
		red = 255;
		break;

	case Predefined::GREEN:
		green = 255;
		break;

	case Predefined::BLUE:
		blue = 255;
		break;

	case Predefined::WHITE:
		red = green = blue = 255;
		break;
	}
}

Color::~Color()
{
}
