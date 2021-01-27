#include "QueueTask.h"

QueueTask::QueueTask() {};

Task QueueTask::getTask()
{
	Task task;

	mutex.lock();
	if (tasks->empty()) {
		task = NULL;
	}
	else {
		task = tasks->front();
		tasks->pop();
	}
	mutex.unlock();

	return task;
}

void QueueTask::setTask(Task task)
{
	mutex.lock();
	tasks->push(task);
	mutex.unlock();
}
