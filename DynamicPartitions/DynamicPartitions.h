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

	AllocationMethod allocationMethod;

	// Memory Partition operations
	void readConfs();
	std::list<MemoryPartition>::iterator getAvailablePartitionIter(int, AllocationMethod);
	void mergeEmptyPartitions();

public:
	// Constructors
	DynamicPartitions();

	// Public methods
	void printMemoryContents();
	bool loadNewJob(std::string, int);
	bool terminateJob(std::string);
};
