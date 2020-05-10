#include <iostream>
#include <cstdlib>
#include <vector>

#include "randSelect.h"

using namespace std;


void printVector(std::vector<int> v) {
    std::cout << "[ ";
    for (int i : v)
        std::cout << i << " ";
    std::cout << "]\n";
}

int partition(std::vector<int> &v, int pivot){
	int smaller = 0;

    swap(0, pivot, v); 
	for (auto i = 1; i < (int)v.size(); i++){
    	if(v[i] <= v[0]){
    		swap(smaller + 1, i, v);
    		smaller++;
    	}
	}
	swap(smaller, 0, v);

	return smaller;
}

int randomIndex(int size){
	return (rand() % size);
}

void swap(int i, int j, std::vector<int> &v){
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;

	return;
}

int randSelect(std::vector<int> v, int rankIndex) {
	if (v.size() == 0){
		return 1;
	}
    int pivot = randomIndex((int)v.size());
    int pivotRank = partition(v, pivot);
    int sum = 0;
    if (pivotRank == rankIndex){
    	sum = sum + v[rankIndex];
    }
    else if (pivotRank < rankIndex){
    	rankIndex = rankIndex - pivotRank - 1; 
    	std::vector<int> vPrime(v.begin() + pivotRank + 1, v.end());
    	sum = sum + randSelect(vPrime, rankIndex);
    }
    else{
    	std::vector<int> vPrimeA(v.begin(), v.begin() + pivotRank);
    	sum = sum + randSelect(vPrimeA, rankIndex);
    }
    return sum;
}
