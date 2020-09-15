/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************

vector<process_stats> stats;

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	stats.clear();

	ifstream infile;
	infile.open(filename);
	if (!infile.is_open()) return COULD_NOT_OPEN_FILE;

	string line;

	if (ignoreFirstRow) getline(infile, line);

	while (getline(infile, line)){
		stringstream lineStream(line);
		process_stats s;
		string f1, f2, f3, f4;
		getline(lineStream, f1, ',');
		getline(lineStream, f2, ',');
		getline(lineStream, f3, ',');
		getline(lineStream, f4, ',');

		if (f1.length() < 1 || f2.length() < 1 || f3.length() < 1 || f4.length() < 1) continue;

		s.process_number = stoi(f1);
		s.start_time = stoi(f2);
		s.cpu_time = stoi(f3);
		s.io_time = stoi(f4);

		stats.push_back(s);
	}

	infile.close();

	return SUCCESS;
}

bool cpuSort (process_stats i, process_stats j){
	return (i.cpu_time < j.cpu_time);
}

bool processSort (process_stats i, process_stats j){
	return (i.process_number < j.process_number);
}

bool startSort (process_stats i, process_stats j){
	return (i.start_time < j.start_time);
}

bool ioSort (process_stats i, process_stats j){
	return (i.io_time < j.io_time);
}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder){
		case CPU_TIME:
			sort(stats.begin(), stats.end(), cpuSort);
			break;
		case PROCESS_NUMBER:
			sort(stats.begin(), stats.end(), processSort);
			break;
		case START_TIME:
			sort(stats.begin(), stats.end(), startSort);
			break;
		case IO_TIME:
			sort(stats.begin(), stats.end(), ioSort);
			break;
	}
}

process_stats getNext() {
	process_stats myFirst;
	if (stats.size() < 1) return myFirst;
	myFirst = stats.front();
	stats.erase(stats.begin());
	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}


