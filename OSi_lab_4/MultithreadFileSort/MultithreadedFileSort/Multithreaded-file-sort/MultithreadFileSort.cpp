#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "QueueTask.h"
#include "HandleTask.h"
#include "MultithreadFileSort.h"

using namespace std;

vector<vector<string>*> dataParts;

int main()
{
	vector<string> data = GetText(FILE_PATH);
	int threadsCount;
	cout << "It was: " << endl;
	for (string str : data) {
		cout << str << endl;
	}
	cout << endl;
	//cout << "Pls enter thread number: ";
	//cin >> threadsCount;
	//cout << endl;
	threadsCount = THREADS_COUNT;
	if (threadsCount > data.size()) {
		threadsCount = data.size();
	}
	QueueTask* taskQueue = FormTaskQueue(data, threadsCount);
	HandleTask* taskHandler = new HandleTask(taskQueue);
	taskHandler->sortTasks(threadsCount);
	vector<string> sortedData = MergeBlocks(dataParts);
	cout << "It is: " << endl;
	for (string str : sortedData) {
		cout << str << endl;
	}
}

QueueTask* FormTaskQueue(vector<string> data, int threadsCount) {
	int part = data.size() / threadsCount;
	QueueTask* taskQueue = new QueueTask();

	for (int i = 0; i < threadsCount; i++) {
		vector<string>* dataPart = new vector<string>();
		for (int j = 0; j < part; j++) {
			string str = data[i * part + j];
			dataPart->push_back(str);
		}
		dataParts.push_back(dataPart);
		taskQueue->setTask([dataPart]() { sort(dataPart->begin(), dataPart->end()); });
	}
	return taskQueue;
}

vector<string> MergeBlocks(vector<vector<string>*> dataParts) {
	vector<string> sortedData;
	vector<string> lines;
	for (int i = 0; i < dataParts.size(); i++)
	{
		lines.push_back(dataParts[i]->front());
		dataParts[i]->erase(dataParts[i]->begin());
	}
	while (!dataParts.empty()) {
		string minLine = lines[0];
		int minIndex = 0;
		for (int i = 1; i < lines.size(); i++) {
			if (strcmp(lines[i].c_str(), minLine.c_str()) < 0) {
				minLine = lines[i];
				minIndex = i;
			}
		}
		sortedData.push_back(minLine);
		if (dataParts[minIndex]->empty()) {
			dataParts.erase(dataParts.begin() + minIndex);
			lines.erase(lines.begin() + minIndex);
		}
		else {
			lines[minIndex] = dataParts[minIndex]->front();
			dataParts[minIndex]->erase(dataParts[minIndex]->begin());
		}
	}
	return sortedData;
}

vector<string> GetText(string filename) {
	vector<string> data;
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Error open file!" << filename << endl;
		return vector<string>();
	}
	string line;
	while (getline(file, line)) {
		if (line.length() != 0) {
			data.push_back(line);
		}
	}
	return data;
}
