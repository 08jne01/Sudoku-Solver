#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

template <class T> void readCSV(const std::string filename, std::vector<std::vector<T>>& dataVector, int columns, int ignoreLine)

{
	std::ifstream in(filename);
	std::string line;
	std::string data;

	std::vector<std::vector<T>> tempVec;

	if (!in.is_open())

	{
		std::cout << "Failed to open data!" << std::endl;
		//char arr[20];
		//char* arr = strerror(errno);
		//std::cout << "Error: " << arr << std::endl;
		return;
	}
	while (in.good())

	{
		std::vector<T> buffer;

		for (int i = 0; i < columns; i++)

		{
			if (i < columns - 1) getline(in, data, ',');

			else getline(in, data, '\n');
			std::stringstream os(data);
			T temp;
			os >> temp;
			buffer.push_back(temp);
			//std::cout << data << std::endl;
		}

		if (ignoreLine != 1) tempVec.push_back(buffer);
		ignoreLine = 0;
	}

	tempVec.pop_back();

	dataVector = tempVec;
}