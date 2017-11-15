#pragma once

#include "../DynamicPartitions/DynamicPartitions.h"

class RelocatableDynamicPartitions : public DynamicPartitions
{
protected:

public:
	RelocatableDynamicPartitions();

	void compact();
};

