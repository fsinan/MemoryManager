#include <iostream>
#include <sstream>

#include "FixedPartitions.h"

void mainLoop(FixedPartitions& manager)
{
	std::string command, firstWord;

	while (true)
	{
		std::cout << "$ ";
		std::getline(std::cin, command);
		std::istringstream str(command);

		str >> firstWord;

		// A new job
		if (firstWord == "new-job")
		{
			std::string name;
			int size;

			str >> name >> size;

			manager.loadNewJob(name, size);
		}
		// Ending the current job
		else if (firstWord == "end-job")
		{
			std::string name;

			str >> name;

			manager.terminateJob(name);
		}
		// Displaying the status of the memory
		else if (firstWord == "show-stat")
		{
			manager.printMemoryContents();
		}
		// Exit the simulation
		else if (firstWord == "exit")
		{
			std::cout << "Stopping the simulation" << std::endl;

			return;
		}
	}
}

int main()
{
	FixedPartitions manager;

	std::cout << "______Fixed Partitions System______" << std::endl;

	mainLoop(manager);

	system("pause");
	return 0;
}