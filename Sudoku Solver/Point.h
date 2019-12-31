#pragma once
struct Point

{
	Point(unsigned char x,
		unsigned char y,
		unsigned char value
	):
		m_x(x),
		m_y(y),
		m_value(value)

	{

	}

	unsigned char m_x, m_y, m_value;
};