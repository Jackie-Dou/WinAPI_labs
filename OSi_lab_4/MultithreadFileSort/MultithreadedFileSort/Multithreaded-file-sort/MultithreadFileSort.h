#pragma once

#define FILE_PATH "testtext.txt"
#define THREADS_COUNT 4

vector<string> MergeBlocks(vector<vector<string>*> dataParts);
QueueTask* FormTaskQueue(vector<string> data, int threadsCount);
vector<string> GetText(string filename);
