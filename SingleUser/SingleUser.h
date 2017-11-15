#pragma once

#include <string>

enum Status
{
	Free, Busy
};

struct Job
{
	std::string name;
	int occupiedMemory;
};

class SingleUser
{
protected:
	// Memory size in Kilobytes
	int memorySize = 100;

	Status status;

	Job currentJob;

	void acceptNewJob(Job);
public:
	SingleUser();
	SingleUser(int);

	void printMemoryStatus();
	bool loadNewJob(Job);
	bool loadNewJob(std::string, int);
	bool terminateCurrentJob();
};
