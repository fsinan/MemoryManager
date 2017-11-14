#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "SingleUser.h"

void mainLoop(SingleUser& manager)
{
	std::string command, firstWord;

	while (true)
	{
		std::cout << "$ ";
		std::getline(std::cin, command);
		std::istringstream str(command);

		str >> firstWord;

		// A new job
		if (firstWord.compare("new-job") == 0)
		{
			std::string name;
			int size;

			str >> name >> size;

			manager.loadNewJob(name, size);
		}
		// Ending the current job
		else if (firstWord.compare("end-job") == 0)
		{
			manager.terminateCurrentJob();
		}
		// Displaying the status of the memory
		else if (firstWord.compare("show-stat") == 0)
		{
			manager.printMemoryStatus();
		}
		// Exit the simulation
		else if (firstWord.compare("exit") == 0)
		{
			std::cout << "Stopping the simulation" << std::endl;

			return;
		}
	}
}

int main()
{
	const char* filePath = "conf.dat";
	std::ifstream in(filePath);
	std::string currentLine;
	int memSize;

	while (std::getline(in, currentLine))
	{
		if (currentLine[0] == '+')
		{
			std::string cmd = currentLine.substr(1, currentLine.find('='));
			std::string val = currentLine.substr(currentLine.find('=') + 1, currentLine.length());

			memSize = std::stoi(val);
		}
	}

	SingleUser memoryManager(memSize);

	std::cout << "______Single-User System______" << std::endl;
	
	mainLoop(memoryManager);

	system("pause");
	return 0;
}