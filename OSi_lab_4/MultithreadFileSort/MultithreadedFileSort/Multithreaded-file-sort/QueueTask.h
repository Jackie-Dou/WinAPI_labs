#pragma once
#include <functional>
#include <mutex>
#include <queue>
#include <string>

using namespace std;

typedef function<void()> Task;

class QueueTask
{
private:
	mutex mutex;
	queue<Task>* tasks = new queue<Task>;

public:
	QueueTask();
	Task getTask();
	void setTask(Task task);
};

