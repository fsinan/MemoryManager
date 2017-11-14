#include "DynamicPartitions.h"

#include <iostream>
#include <iomanip>
#include <string>

DynamicPartitions::DynamicPartitions()
{
	allocatePartition(memorySize, 0, "", false);
}

DynamicPartitions::DynamicPartitions(int memorySize)
{
	this->memorySize = memorySize;
}

void DynamicPartitions::printMemoryContents()
{
	for (auto it : memory)
	{
		std::cout << std::setw(20) << std::left << "Size: " + std::to_string(it.size) + " KB"
			<< std::setw(20) << "Address: " + std::to_string(it.address) + " KB"
			<< std::setw(20) << "Accessing Job: " + it.accessingJob
			<< std::setw(20) << "Status: " + std::string((it.busy) ? "Busy" : "Free") << std::endl;
	}
}

void DynamicPartitions::allocatePartition(int size, int address, std::string job, bool busy)
{
	MemoryPartition partition{ size, address, job, busy };

	auto it = memory.begin();

	for (; it != memory.end(); it++)
	{
		if (address >= (*it).address)
		{
			break;
		}
	}

	memory.insert(it, partition);
}
