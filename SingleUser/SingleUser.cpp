#include "SingleUser.h"

#include <iostream>

void SingleUser::acceptNewJob(Job newJob)
{
	status = Busy;
	this->currentJob = newJob;
}

SingleUser::SingleUser()
{
	status = Free;
	currentJob = { "", 0 };
}

SingleUser::SingleUser(int memorySize)
{
	this->memorySize = memorySize;
	status = Free;
}

void SingleUser::printMemoryStatus()
{
	std::cout << "______Single User System______" << std::endl;
	std::cout << "Memory size: " << memorySize << "KB" << std::endl;

	if (status == Free)
	{
		std::cout << "Status: Free" << std::endl;
	}
	else
	{
		std::cout << "Status: Busy" << std::endl;
		std::cout << "Running: " << currentJob.name << std::endl;
		std::cout << "Occupied Memory: " << currentJob.occupiedMemory << "KB ";
		std::cout << "Free Memory: " << memorySize - currentJob.occupiedMemory << "KB" << std::endl;
		std::cout << "Internal Fragmentation" << std::endl;
	}
}

bool SingleUser::loadNewJob(Job job)
{
	return loadNewJob(job.name, job.occupiedMemory);
}

bool SingleUser::loadNewJob(std::string name, int size)
{
	if (status == Free)
	{
		if (size <= memorySize)
		{
			status = Busy;
			currentJob = { name, size };

			return true;
		}

		std::cout << "There is no sufficient memory space to run this job" << std::endl;
	}
	else
	{
		std::cout << "The system is busy." << std::endl;
	}

	return false;
}
