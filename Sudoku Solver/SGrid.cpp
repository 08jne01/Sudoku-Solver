#include "SGrid.h"

SGrid::SGrid()

{
	setupBlankGrid();
}

SGrid::SGrid(unsigned char number)

{
	bool valid = false;

	while (!valid)

	{

		for (int i = 0; i < number; i++)

		{
			bool validPosition = false;
			unsigned char index;
			while (!validPosition)

			{
				index = randomi(0, 80);
				if (!(*this)[index])
					validPosition = true;
			}
			(*this)[index] = randomi(1, 9);
		}

		if (validateBoard())
			valid = true;
		else

		{
			for (int i = 0; i < 81; i++)

			{
				(*this)[i] = 0;
			}
		}
	}
}

SGrid::SGrid(const std::vector<unsigned char>& points)

{
	for (int i = 0; i < 81; i++)

	{
		if (i < points.size())
			(*this)[i] = points[i];
	}
}

SGrid::SGrid(const std::vector<Point>& points)

{
	setupBlankGrid();

	for (int i = 0; i < points.size(); i++)

	{
		(*this)(points[i].m_x, points[i].m_y) = points[i].m_value;
	}
}

void SGrid::setupBlankGrid()

{
	for (int i = 0; i < 9; i++)

	{
		for (int j = 0; j < 9; j++)

		{
			(*this)(i, j) = 0;
		}
	}
}



void SGrid::draw()

{
	std::cout << (*this) << std::endl;
	/*for (int j = 0; j < 10; j++)

	{
		if (j % 3 == 0)

		{
			std::cout << '+';
			drawCharacter('-', 17);
			std::cout << '+' << std::endl;
		}

		if (j < 9)
			std::cout << '|';
		for (int i = 0; i < 9; i++)

		{
			

			if (i < 9 && j < 9)

			{

				char endChar = ' ';

				if (i % 3 == 2)
					endChar = '|';


				unsigned char c = (*this)(i, j);

				if (c == 0)
					std::cout << '.' << endChar;
				else
					std::cout << (int)c << endChar;
			}
				
		}

		std::cout << std::endl;
	}*/
}

bool SGrid::validateRow(unsigned char y)

{
	unsigned char row[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 9; i++)

	{
		unsigned char c = (*this)(i, y);
		if (c)

		{
			row[c-1]++;
			if (row[c-1] > 1)
				return false;
		}
	}

	return true;
}

bool SGrid::validateColumn(unsigned char x)

{
	unsigned char col[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 0; i < 9; i++)

	{
		unsigned char c = (*this)(x, i);
		if (c)

		{
			col[c - 1]++;
			if (col[c - 1] > 1)
				return false;
		}
			

		
	}

	return true;
}

bool SGrid::validateSquare(unsigned char iBox, unsigned char jBox)

{
	unsigned char box[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = iBox * 3; i < (iBox + 1) * 3; i++)

	{
		for (int j = jBox * 3; j < (jBox + 1) * 3; j++)

		{
			unsigned char c = (*this)(i, j);
			if (c)

			{
				box[c-1]++;
				if (box[c-1] > 1)
					return false;
			}
		}
	}
	return true;
}

bool SGrid::validatePos(unsigned char i, unsigned char j)

{
	if (!validateColumn(i))
		return false;
	if (!validateRow(j))
		return false;
	if (!validateSquare(i / 3, j / 3))
		return false;

	return true;
}

bool SGrid::validatePos(unsigned char index)

{
	unsigned char i, j;
	posFromIndex(index, i, j);
	return validatePos(i, j);
}

bool SGrid::validateBoard()

{
	for (int i = 0; i < 9; i++)

	{
		if (!validateRow(i))
			return false;
	}

	for (int i = 0; i < 9; i++)

	{
		if (!validateColumn(i))
			return false;
	}

	for (int i = 0; i < 3; i++)

	{
		for (int j = 0; j < 3; j++)

		{
			if (!validateSquare(i, j))
				return false;
		}
	}

	return true;
}

bool SGrid::finished()

{
	for (int i = 0; i < 81; i++)

	{
		if (!(*this)[i])
			return false;
	}
	return validateBoard();
}