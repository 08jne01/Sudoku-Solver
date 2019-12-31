#include "BackTracker.h"
#include "Clock.h"

void getPuzzle(std::vector<unsigned char>& input)

{
	std::vector <std::vector<int>> dataVector;
	readCSV<int>("puzzle.txt", dataVector, 9, 0);
	for (int i = 0; i < dataVector.size(); i++)

	{
		for (int j = 0; j < dataVector[i].size(); j++)

		{
			input.push_back(dataVector[i][j]);
		}


	}
}

void outputSolution(const SGrid& grid, std::string filename)

{
	std::ofstream file(filename);

	for (int i = 0; i < 81; i++)

	{
		char c = ',';

		if ((i+1) % 9 == 0 && (i+1) != 0) c = '\n';

		file << (int)grid[i] << c;
	}

	file << "\n\n" << grid << std::endl;
}

bool solvePuzzle(SGrid& grid, bool print = false)

{
	//SGrid grid(starting);

	int index;
	for (index = 0;; index++)

	{
		if (!grid[index])
			break;
	}

	if (print) std::cout << "Starting index " << index << std::endl;
	if (print) grid.draw();
	if (print) std::cout << std::endl;


	Clock clock;

	std::vector<std::shared_ptr<BackTracker>> stack;
	std::shared_ptr<BackTracker> b = std::shared_ptr<BackTracker>(new BackTracker(grid, index, 255, nullptr, &stack));
	stack.push_back(b);

	std::shared_ptr<BackTracker> solution;

	int counter = 0;
	bool solutionFound = false;
	while (stack.size() > 0)

	{
		std::shared_ptr<BackTracker> popped = stack.back();
		stack.pop_back();
		if (popped->move())

		{
			solution = popped;
			solutionFound = true;
			stack.clear();
			break;
		}
		counter++;

		if (stack.size() == 0)
			popped->printGrid();
	}

	if (solutionFound)

	{
		if (print)

		{
			std::cout << "Solution Found in " << clock.elapsed().inMiliSeconds() << " ms" << std::endl << std::endl;
			solution->printGrid();
			outputSolution(solution->getGrid(), "solution.txt");
		}
		grid = solution->getGrid();
		return true;
	}

	else

	{

		if (print) std::cout << "No solution found!" << std::endl;
		return false;
	}
}

int main(int argc, char** argv)

{
	std::vector<unsigned char> starting;

	std::string commandSolve = "solve";
	std::string commandGenerate = "generate";
	if (argc > 1 && argv[1] == commandSolve)

	{
		std::cout << "Getting from file!" << std::endl;
		getPuzzle(starting);
		std::cout << "Check there is a newline character at the end of the file if it doesn't read correctly!" << std::endl;

		SGrid grid(starting);
		solvePuzzle(grid, true);
	}

	else if (argc > 1 && argv[1] == commandGenerate)

	{
		int seed, preFilled;
		std::cout << "Please enter seed: ";
		std::cin >> seed;
		std::cout << "Please enter number of pre-filled squares (up to 81): ";
		std::cin >> preFilled;
		srand(seed);
		bool valid = false;
		SGrid start;
		SGrid solution;
		int count = 0;
		while (!valid)

		{
			start = SGrid(preFilled);
			solution = start;
			valid = solvePuzzle(solution);
			count++;
			std::cout << "Number of tries: " << count << std::endl;
		}

		std::cout << "Start Grid" << std::endl;
		std::cout << start << std::endl;

		outputSolution(start, "start_sudoku.txt");
		outputSolution(solution, "solution.txt");
	}

	else

	{
		std::vector<Point> points =

		{
			Point(0, 0, 8),
			Point(2, 1, 3),
			Point(1, 2, 7),
			Point(3, 1, 6),
			Point(4, 2, 9),
			Point(6, 2, 2),
			Point(1, 3, 5),
			Point(5, 3, 7),
			Point(4, 4, 4),
			Point(5, 4, 5),
			Point(3, 5, 1),
			Point(6, 4, 7),
			Point(7, 5, 3),
			Point(2, 6, 1),
			Point(2, 7, 8),
			Point(1, 8, 9),
			Point(3, 7, 5),
			Point(7, 6, 6),
			Point(8, 6, 8),
			Point(7, 7, 1),
			Point(6, 8, 4),
		};

		std::vector<unsigned char> initGrid =

		{
			5,3,0,0,7,0,0,0,0,
			6,0,0,1,9,5,0,0,0,
			0,9,8,0,0,0,0,6,0,
			8,0,0,0,6,0,0,0,3,
			4,0,0,8,0,3,0,0,1,
			7,0,0,0,2,0,0,0,6,
			0,6,0,0,0,0,2,8,0,
			0,0,0,4,1,9,0,0,5,
			0,0,0,0,8,0,0,7,9
		};

		std::vector<unsigned char> initGrid2 =

		{
			1,0,0,0,0,2,7,0,0,
			0,4,0,0,0,0,0,8,0,
			0,0,0,0,9,0,0,0,0,
			9,0,0,0,7,0,3,0,0,
			0,8,0,0,0,0,0,0,5,
			0,0,4,2,0,0,0,6,0,
			2,0,0,9,0,0,1,0,0,
			0,0,5,0,3,1,0,0,0,
			0,0,0,0,2,7,0,0,6,
		};

		starting = initGrid;
	}

	

	
	
	
	return 0;
}