#pragma once

#include <algorithm>
#include <vector>

void printVector(std::vector<int> v);

int randomIndex(int size);

int partition(std::vector<int> &v, int pivot);

void swap(int i, int j, std::vector<int> &v);

int medianOfMedians(std::vector<int> &v);

void chunk(int chunkSize, std::vector<std::vector<int>> &chunks, std::vector<int> &v);

int median(std::vector<int> set);

int randSelect(std::vector<int> v, int rankIndex);

int findIndex(std::vector<int> &v);
