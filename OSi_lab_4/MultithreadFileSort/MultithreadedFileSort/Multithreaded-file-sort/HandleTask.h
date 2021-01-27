#pragma once
#include "QueueTask.h"
#include <thread>
#include <string>

class HandleTask
{
private:
	QueueTask* taskQueue;

public:
	HandleTask(QueueTask* taskQueue);
	void sortTasks(int threadCounts);
};

