#pragma once

#include <string>
#include <vector>

#include "../SingleUser/SingleUser.h"

enum AllocationMethod
{
	FCFS, BestFit
};

struct MemoryPartition
{
	int size;
	int address;
	std::string accessingJob;
	Status status;
};

class FixedPartitions
{
protected:
	// Memory
	std::vector<MemoryPartition> memory;
	AllocationMethod allocationMethod;

	void readPartitionConfs();
	int getAvailablePartitionIndex(int, AllocationMethod);
public:
	FixedPartitions();

	void printMemoryContents();
	bool loadNewJob(std::string, int);
	bool terminateJob(std::string);
};
