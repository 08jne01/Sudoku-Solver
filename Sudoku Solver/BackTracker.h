#pragma once
#include <memory>
#include "SGrid.h"

class BackTracker

{
public:
	BackTracker(
		SGrid grid,
		unsigned char index,
		unsigned char value,
		BackTracker* parent,
		std::vector<std::shared_ptr<BackTracker>>* stack_
	):
		m_grid(grid),
		m_index(index),
		m_value(value),
		m_parent(parent),
		stack(stack_)

	{
		/*for (int i = 0; i < 81; i++)

		{
			for (int j = 0; j < 9; j++)

			{
				moves[i][j] = -1;
			}
		}*/
	}

	~BackTracker()

	{

	}

	//Move to all possible squares and place all possible values
	bool move()

	{
		if (m_grid[m_index] && m_parent != nullptr)
			return false;

		if (m_value != 255) 
			m_grid[m_index] = m_value;

		if (!m_grid.validatePos(m_index))
			return false;

		if (m_grid.finished())

		{
			return true;
		}
			

		bool valid = false;
		int nextIndex = m_index + 1;
		while (!valid)

		{
			if (!m_grid[nextIndex])
				valid = true;
			else
				nextIndex++;
		}

		if (m_value == 255)
			nextIndex = m_index;

		if (nextIndex >= 81)
			return false;

		for (int j = 1; j < 10; j++)

		{
			if (!m_grid[nextIndex])

			{
				SGrid tempGrid = m_grid;
				tempGrid[nextIndex] = j;

				if (tempGrid.validatePos(nextIndex))

				{
					stack->push_back(std::shared_ptr<BackTracker>(new BackTracker(m_grid, nextIndex, j, this, stack)));
				}
			}
		}

		return false;
	}

	void printGrid()

	{
		m_grid.draw();
	}

	SGrid& getGrid()

	{
		return m_grid;
	}

private:
	SGrid m_grid;
	std::vector<std::shared_ptr<BackTracker>>* stack;
	unsigned char m_index, m_value;
	BackTracker* m_parent = nullptr;
};