#include "FixedPartitions.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>

void FixedPartitions::readPartitionConfs()
{
	// In case no given
	allocationMethod = FCFS;
	// The address for the partitions
	int currentAddress = 0;

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
			else if (cmd == "partition_size")
			{
				MemoryPartition newPartition{ std::stoi(val), currentAddress, "", Free };
				memory.push_back(newPartition);

				currentAddress += newPartition.size;
			}
		}
	}
}

FixedPartitions::FixedPartitions()
{
	readPartitionConfs();
}

void FixedPartitions::printMemoryContents()
{
	for (auto it : memory)
	{
		std::cout << std::setw(20) << std::left << "Size: " + std::to_string(it.size) + " KB"
			<< std::setw(20) << "Address: " + std::to_string(it.address) + " KB"
			<< std::setw(25) << "Accessing Job: " + it.accessingJob
			<< std::setw(20) << "Status: " + std::string(it.status == Busy ? "Busy" : "Free") << std::endl;
	}
}

bool FixedPartitions::loadNewJob(std::string name, int size)
{
	int partitionIndex = getAvailablePartitionIndex(size, allocationMethod);

	if (partitionIndex == -1)
	{
		std::cout << "Cannot load job " << name << "." << std::endl;

		return false;
	}

	memory[partitionIndex].accessingJob = name;
	memory[partitionIndex].status = Busy;

	return true;
}

bool FixedPartitions::terminateJob(std::string name)
{
	for (int i = 0; i < memory.size(); i++)
	{
		if (memory[i].accessingJob == name)
		{
			memory[i].accessingJob = "";
			memory[i].status = Free;

			return true;
		}
	}

	std::cout << "Cannot find the job specified." << std::endl;

	return false;
}

int FixedPartitions::getAvailablePartitionIndex(int size, AllocationMethod allocationMethod)
{
	if (allocationMethod == FCFS)
	{
		for (int i = 0; i < memory.size(); i++)
		{
			if (size <= memory[i].size && memory[i].status == Free)
			{
				return i;
			}
		}
	}
	else if (allocationMethod == BestFit)
	{
		int minSize = INT_MAX;
		int bestIndex = -1;

		for (int i = 0; i < memory.size(); i++)
		{
			if (size <= memory[i].size && memory[i].size < minSize && memory[i].status == Free)
			{
				minSize = memory[i].size;
				bestIndex = i;
			}
		}

		return bestIndex;
	}

	return -1;
}
