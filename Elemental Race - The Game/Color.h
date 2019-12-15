
#pragma once

struct Color
{
	float r, g, b, a;
	
	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{}

	Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a)
	{}

	void Set(float r, float g, float b, float a = 1.0f)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	float* operator & ()
	{
		return (float*)this;
	}
};

extern Color Red;
extern Color Green;
extern Color Blue;
extern Color Black;
extern Color White;
extern Color Purple;
extern Color Yellow;

extern Color Red_T;
extern Color Green_T;
extern Color Yellow_T;
extern Color Blue_T;
extern Color Black_T;
extern Color White_T;
extern Color Grey_T;
extern Color Grey2_T;
extern Color Brown_T;
extern Color DarkBrown_T;
extern Color Blue2_T;
extern Color Skin_T;
extern Color Skin2_T;
extern Color DarkBlue_T;
extern Color Grey3_T;
extern Color Green2_T;
extern Color DarkOrange_T;