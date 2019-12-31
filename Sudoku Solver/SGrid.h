#pragma once
#include "Point.h"
#include "FileHelper.h"

inline int randomi(int min, int max)

{
	return rand() % (max - min + 1) + min;
}

class SGrid

{
public:
	SGrid();
	SGrid(unsigned char number);
	SGrid(const std::vector<Point>& points);
	SGrid(const std::vector<unsigned char>& points);
	void setupBlankGrid();
	void draw();
	static void drawCharacter(char c, unsigned int multiple)

	{
		for (int i = 0; i < multiple; i++)

		{
			std::cout << c;
		}
	}

	//y: 0 -> 8
	bool validateRow(unsigned char y);
	//x: 0 -> 8
	bool validateColumn(unsigned char x);
	//i: 0 -> 2, j: 0 -> 2
	bool validateSquare(unsigned char i, unsigned char j);

	bool validatePos(unsigned char i, unsigned char j);
	bool validatePos(unsigned char i);

	bool validateBoard();

	bool finished();

	//Setters and Getters
	inline unsigned char& operator()(unsigned char i, unsigned char j)

	{
		return m_grid[index(i, j)];
	}
	inline unsigned char operator()(unsigned char i, unsigned char j) const

	{
		return m_grid[index(i, j)];
	}
	inline unsigned char operator[](unsigned char i) const

	{
		return m_grid[i];
	}

	inline unsigned char& operator[](unsigned char i)

	{
		return m_grid[i];
	}
	inline void setGrid(unsigned char i, unsigned char j, unsigned char value)

	{
		m_grid[index(i, j)] = value;
	}

private:
	//Private index function
	inline unsigned char index(const unsigned char i, const unsigned char j) const

	{
		return (i + j * 9);
	}
	void posFromIndex(const unsigned char index, unsigned char& i, unsigned char& j)

	{
		i = index % 9;
		j = index / 9;
	}
	//Grid member variable
	unsigned char m_grid[81];
};



inline std::ostream& operator<<(std::ostream& os, const SGrid& grid)

{
	for (int j = 0; j < 10; j++)

	{
		if (j % 3 == 0)

		{
			os << '+';
			for (int i = 0; i < 17; i++)

			{
				os << '-';
			}
			//SGrid::drawCharacter('-', 17);
			os << '+' << std::endl;
		}

		if (j < 9)
			os << '|';
		for (int i = 0; i < 9; i++)

		{


			if (i < 9 && j < 9)

			{

				char endChar = ' ';

				if (i % 3 == 2)
					endChar = '|';


				unsigned char c = grid(i, j);

				if (c == 0)
					os << '.' << endChar;
				else
					os << (int)c << endChar;
			}

		}
		os << std::endl;
	}

	return os;
}