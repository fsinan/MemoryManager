#pragma once

#include <list>
#include <algorithm>

struct MemoryPartition
{
	int size;
	int address;
	std::string accessingJob;
	bool busy;
};

class DynamicPartitions
{
protected:
	// Memory Size in Kilobytes
	int memorySize = 100;

	// Memory partitions
	std::list<MemoryPartition> memory;

	// Memory Partition operations
	void allocatePartition(int, int, std::string, bool);

public:
	// Constructors
	DynamicPartitions();
	DynamicPartitions(int);

	// Public methods
	void printMemoryContents();
};
