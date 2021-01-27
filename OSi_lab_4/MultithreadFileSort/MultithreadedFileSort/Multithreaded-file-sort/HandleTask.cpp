#include "HandleTask.h"

HandleTask::HandleTask(QueueTask* taskQueue)
{
	this->taskQueue = taskQueue;
}

void HandleTask::sortTasks(int threadCounts)
{
	vector<thread> threadList;
	for (int i = 0; i < threadCounts; i++)
	{
		Task task = taskQueue->getTask();
		if (task != NULL) {
			thread thread(task);
			threadList.push_back(move(thread));
		}
	}

	for(thread &thread : threadList)
	{
		thread.join();
	}
}
