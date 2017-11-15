#pragma once

#include <list>
#include <algorithm>

#include "../SingleUser/SingleUser.h"
#include "../FixedPartitions/FixedPartitions.h"

class DynamicPartitions
{
protected:
	// Memory Size in Kilobytes
	int memorySize = 100;

	// Memory partitions
	std::list<MemoryPartition> memory;

	// Memory Partition operations
	void allocatePartition(int, int, std::string, Status);

public:
	// Constructors
	DynamicPartitions();
	DynamicPartitions(int);

	// Public methods
	void printMemoryContents();
};
