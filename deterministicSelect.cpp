#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <vector>

using namespace std;

#define CHUNK_SIZE 5

/* Name: Swap
 * Parameters: 2 integers & a vector of integers
 * Purpose: Swap the values associated at the indices i and j 
 * of the vector v. 
 */ 
void swap(int i, int j, std::vector<int> &v){
	int temp = v[i];
	v[i] = v[j];
	v[j] = temp;
	return;
}

/*
 * I didn't make this function :)
 */
void printVector(std::vector<int> v) {
    std::cout << "[ ";
    for (int i : v)
        std::cout << i << " ";
    std::cout << "]\n";
}

/* Name: partition
 * Parameters: integer vector and integer
 * Purpose: partitions the elements of vector v around the 
 * value at the index pivot. Elements smaller than or equal to  
 * v[pivot] are placed to its left. Larger to its right. 
 */
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

/* 
 * Generates a random integer value... no longer in use
 * thanks to median of medians being used instead.
 */
int randomIndex(int size){
	return (rand() % size);
}

/* Name: chunk
 * Parameters: integer, an integer vector, and a int vector vector.
 * Purpose: divide the contents of vector v into groups of chunkSize 
 * and copy them into vector chunks.
 */
void chunk(int chunkSize, std::vector<std::vector <int>> &chunks, std::vector<int> &v){
	int total = ((int)v.size() / chunkSize) * chunkSize;
	chunks.resize(total/chunkSize);
	for (int i = 0; i < total; i++){
		chunks[i/chunkSize].push_back(v[i]);
	}
	chunks.shrink_to_fit();
}

/*
 * Name: median
 * Parameters: integer vector
 * Purpose: calculates the median of vector set.
 */
int median(std::vector<int> set){
    std::sort(set.begin(), set.end());
    return set[(int)set.size()/2];
}

/* Name: findIndex
 * Parameters: integer vector, integer
 * Purpose: returns the index of a given value in vector v.
 * Returns -1 if the element does not exist in v. 
 */
int findIndex(std::vector<int> &v, int value){
	int size = (int)v.size();
	for (int i = 0; i < size; i++){
		if (v[i] == value)
			return i;
	}
	return -1;
}

/* Name: medianOfMedians
 * Parameters: integer vector
 * Purpose: recursively solves for the median of medians
 * in the vector v.
 */
int medianOfMedians(std::vector<int> &v){
	//check base case and solve by brute force
	if (v.size() <= 5){
		return median(v);
	}
	std::vector<std::vector <int>> chunks;
	std::vector<int> medians; 
	//make groups of CHUNK_SIZE
	chunk(CHUNK_SIZE, chunks, v);
	int size = (int)chunks.size();
	//find the median value of each group
	for (int i = 0; i < size; i++){
		medians.push_back(median(chunks[i]));
	}
	//Recursive on the medians of the groups
	return medianOfMedians(medians);
}

/* Name: randSelect
 * Parameters: integer vector, integer
 * Purpose: returns the value of the rankIndex'th smallest element
 * in vector v.
 */
int randSelect(std::vector<int> v, int rankIndex) {
	if (v.size() == 0){
		return -1;
	}
	//retrieve the median of medians of the vector v
    int pivot = findIndex(v, medianOfMedians(v));
    
    cout << "Looking for value with rank " << rankIndex << " in the array:" << endl;
    printVector(v);
    cout << "Selected " << pivot << " as the pivot;";
    //partition around the pivot
    int pivotRank = partition(v, pivot);
    cout << " its rank is " << pivotRank << ";";
    int sum = 0;
    //Selected 1 as the  pivot; its  rank is 0; Thus , we  recurse  on right.
    //check to see if the correct element was selected
    if (pivotRank == rankIndex){
    	cout << " Thus, we recurse on nothing. We are done." << endl;
    	sum = sum + v[rankIndex];
    }


    // PRINT RECURSIONS

    //determine which side of the partitioned vector to recurse on
    else if (pivotRank < rankIndex){
    	cout << " Thus, we recruse on right." << endl;
    	rankIndex = rankIndex - pivotRank - 1; 
    	std::vector<int> vPrime(v.begin() + pivotRank + 1, v.end());
    	sum = sum + randSelect(vPrime, rankIndex);
    }
    else{
    	cout << " Thus, we recurse on left." << endl;
    	std::vector<int> vPrimeA(v.begin(), v.begin() + pivotRank);
    	sum = sum + randSelect(vPrimeA, rankIndex);
    }
    return sum;
}
