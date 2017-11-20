#include "RelocatableDynamicPartitions.h"

void RelocatableDynamicPartitions::compact()
{
	auto it = memory.begin();

	int offset;

	for (offset = 0; it != memory.end();)
	{
		if (it->status == Busy)
		{
			it->address -= offset;
			it++;
		}
		else
		{
			offset += it->size;
			it = memory.erase(it);
		}
	}

	if (!memory.empty() && memory.back().address + memory.back().size < memorySize)
	{
		MemoryPartition emptyPartition{ offset, 0 , "", Free };
		emptyPartition.address = memory.back().address + memory.back().size;
		memory.push_back(emptyPartition);
	}

	if (memory.empty())
	{
		MemoryPartition emptyPartition{ memorySize, 0 , "", Free };
		memory.push_back(emptyPartition);
	}
}

RelocatableDynamicPartitions::RelocatableDynamicPartitions()
{
	
}

