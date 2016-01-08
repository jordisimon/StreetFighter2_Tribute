#pragma once

template<class TYPE>
class Rect
{
public:

	TYPE x, y, w, h;

	Rect()
	{}
	Rect(TYPE x, TYPE y, TYPE w, TYPE h) : x(x), y(y), w(w), h(h)
	{}

	// Operators ------------------------------------------------
	Rect operator -(const Rect &v) const
	{
		Rect r;

		r.x = x - v.x;
		r.y = y - v.y;
		r.w = w - v.w;
		r.h = h - v.h;

		return (r);
	}

	Rect operator +(const Rect &v) const
	{
		Rect r;

		r.x = x + v.x;
		r.y = y + v.y;
		r.w = w + v.w;
		r.h = h + v.h;

		return(r);
	}

	const Rect& operator -=(const Rect &v)
	{
		x -= v.x;
		y -= v.y;
		w -= v.w;
		h -= v.h;

		return(*this);
	}

	const Rect& operator +=(const Rect &v)
	{
		x += v.x;
		y += v.y;
		w += v.w;
		h += v.h;

		return(*this);
	}

	bool operator ==(const Rect& v) const
	{
		return (x == v.x && y == v.y && w == v.w && h == v.h);
	}

	bool operator !=(const Rect& v) const
	{
		return (x != v.x || y != v.y || w != v.w || h != v.h);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0 && w == 0 && h == 0);
	}

	Rect& SetToZero()
	{
		x = y = w = h = 0;
		return(*this);
	}

	bool Intersects(const Rect& v) const
	{
		return (x <= v.x + v.w) &&
			(x + w >= v.x) &&
			(y <= v.y + v.h) &&
			(y + h >= v.y);
	}

	Rect GetIntersectionRect(const Rect& v) const
	{
		Rect result{0,0,0,0};

		TYPE Amin, Amax, Bmin, Bmax;

		/* Horizontal intersection */
		Amin = x;
		Amax = Amin + w;
		Bmin = v.x;
		Bmax = Bmin + v.w;
		if (Bmin > Amin)
			Amin = Bmin;
		result.x = Amin;
		if (Bmax < Amax)
			Amax = Bmax;
		result.w = Amax - Amin;

		/* Vertical intersection */
		Amin = y;
		Amax = Amin + h;
		Bmin = v.y;
		Bmax = Bmin + v.h;
		if (Bmin > Amin)
			Amin = Bmin;
		result.y = Amin;
		if (Bmax < Amax)
			Amax = Bmax;
		result.h = Amax - Amin;

		return result;
	}
};

typedef Rect<int> iRect;
typedef Rect<float> fRect;