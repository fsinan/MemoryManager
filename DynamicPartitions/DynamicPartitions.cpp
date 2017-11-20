#include "DynamicPartitions.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

DynamicPartitions::DynamicPartitions()
{
	readConfs();
}

void DynamicPartitions::printMemoryContents()
{
	for (auto it : memory)
	{
		std::cout << std::setw(20) << std::left << "Size: " + std::to_string(it.size) + " KB"
			<< std::setw(20) << "Address: " + std::to_string(it.address) + " KB"
			<< std::setw(25) << "Accessing Job: " + it.accessingJob
			<< std::setw(20) << "Status: " + std::string(it.status == Busy ? "Busy" : "Free") << std::endl;
	}
}

void DynamicPartitions::readConfs()
{
	// In case no given
	allocationMethod = FCFS;

	const char* filePath = "conf.dat";
	std::ifstream in(filePath);
	std::string currentLine;

	while (std::getline(in, currentLine))
	{
		currentLine.erase(std::remove(currentLine.begin(), currentLine.end(), ' '), currentLine.end());

		if (currentLine[0] == '+')
		{
			std::string cmd = currentLine.substr(1, currentLine.find('=') - 1);
			std::string val = currentLine.substr(currentLine.find('=') + 1, currentLine.length());

			if (cmd == "allocation_method")
			{
				if (val == "FCFS")
				{
					allocationMethod = FCFS;
				}
				else if (val == "BestFit")
				{
					allocationMethod = BestFit;
				}
			}
			else if (cmd == "mem_size")
			{
				memory.clear();

				memorySize = std::stoi(val);

				MemoryPartition newPartition{ memorySize, 0, "", Free };
				memory.push_back(newPartition);
			}
		}
	}
}

std::list<MemoryPartition>::iterator DynamicPartitions::getAvailablePartitionIter(int size, AllocationMethod allocationMethod)
{
	if (allocationMethod == FCFS)
	{
		auto it = memory.begin();

		for (; it != memory.end(); it++)
		{
			if (size <= it->size && it->status == Free)
			{
				return it;
			}
		}
	}
	else if (allocationMethod == BestFit)
	{
		int minSize = INT_MAX;
		auto it = memory.begin();
		auto best = memory.end();

		for (; it != memory.end(); it++)
		{
			if (size <= it->size && it->size < minSize && it->status == Free)
			{
				best = it;
			}
		}

		return best;
	}

	return memory.end();
}

void DynamicPartitions::mergeEmptyPartitions()
{
	auto it1 = memory.begin();
	auto it2 = it1;

	int address, size;

	for (; it1 != memory.end();)
	{
		if (it1->status == Free)
		{
			it2 = it1;

			address = it1->address;
			size = it1->size;

			while ((++it2) != memory.end() && (it2)->status != Busy)
			{
				size += it2->size;
			}

			it1 = memory.erase(it1, it2);

			MemoryPartition newPartition{ size, address, "", Free };

			memory.insert(it1, newPartition);

			if (it1 == memory.end())
				return;
		}
		else
		{
			it1++;
		}
	}
}

bool DynamicPartitions::loadNewJob(std::string name, int size)
{
	auto it = getAvailablePartitionIter(size, allocationMethod);

	if (it == memory.end())
	{
		std::cout << "The job " << name << " cannot be loaded." << std::endl;

		return false;
	}

	if (it->size == size)
	{
		it->accessingJob = name;
		it->status = Busy;
	}
	else
	{
		MemoryPartition partition;

		partition.accessingJob = name;
		partition.size = size;
		partition.address = it->address;
		partition.status = Busy;

		int newSize = it->size - size;
		int newAddress = it->address + size;

		memory.insert(it, partition);

		// Changing the values for the free space
		it->address = newAddress;
		it->size = newSize;
	}

	return true;
}

bool DynamicPartitions::terminateJob(std::string name)
{
	auto it = memory.begin();

	for (; it != memory.end(); it++)
	{
		if (it->accessingJob == name)
		{
			it->accessingJob = "";
			it->status = Free;

			mergeEmptyPartitions();

			return true;
		}
	}

	std::cout << "Cannot find the job specified." << std::endl;

	return false;
}
