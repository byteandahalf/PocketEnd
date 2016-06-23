#pragma once

struct Color
{
	float r, g, b, a;

	static Color BLACK;
	static Color WHITE;

	Color(float r, float g, float b, float a)
	{
		this->r=r, this->g=g, this->b=b, this->a=a;
	}
};
