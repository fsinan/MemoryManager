#pragma once

#include <string>
#include <vector>

enum Status
{
	Free, Busy
};

enum AllocationMethod
{
	FCFS, BestFit
};

struct Job
{
	std::string name;
	int occupiedMemory;
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
public:
	FixedPartitions();

	void printMemoryContents();
	bool loadNewJob(std::string, int);
	bool terminateJob(std::string);
	int getAvailablePartitionIndex(int, AllocationMethod);
};
