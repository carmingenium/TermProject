// TermProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
using namespace std;
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono>

class DataHolder {
public:
    DataHolder() {
		fileName = "";
        numberOfVisit = 0;
    }
    DataHolder(string name) {
        fileName = name;
		numberOfVisit = 1;
    }
    DataHolder(string name, int visit) {
        fileName = name;
        numberOfVisit = visit;
    }
    int getVisit() {
		return numberOfVisit;
	}
    void setVisit(int visit) {
        numberOfVisit = visit;
    }
    string getName() {
        return fileName;
    }
    void setName(string name) {
		fileName = name;
	}
    void incrementVisit() {
        numberOfVisit += 1;
    }
private:
    string fileName;
    int numberOfVisit;
};

// hash table with linear probing
class HashTable {
public:
    HashTable(int size);
    int hashFunction(string name);
    void insert(DataHolder data);
    bool search(DataHolder data);
    void remove(DataHolder data);
    void printTop10();

private:
    DataHolder* table;
    int size;
    int count;
};

HashTable::HashTable(int size) : size(size) {
    table = new DataHolder[size];
    count = 0;
}

// To use names as keys, convert each character to its ASCII value and add them up
int HashTable::hashFunction(string name) {
    int conversion = 0;
    for (char c : name) {
        conversion += static_cast<int>(c);
    }
    return conversion % size;
}

void HashTable::insert(DataHolder data) {
    if (count == size) { // if table is full dont insert
        cout << "table is full" << endl;
        return;
    }
    // if table is not full, insert by linear probing
    int index = hashFunction(data.getName());
    // while table[index] is not empty ("") keep probing
    while (table[index].getName() != "") {
        if (table[index].getName() ==  data.getName()) { // if data is already in table, increment visit count // this doesnt work !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        	table[index].incrementVisit();
        	return;
        }
        else {
            index += 1;
            if (index == size) { // if index is out of bounds, wrap around
                index = 0;
            }
        }
    }
    table[index] = data;
    count += 1;
}

bool HashTable::search(DataHolder data) {
    int index = hashFunction(data.getName());
    while (table[index].getName() != data.getName()) {
		index += 1;
		if (index == size) { // if index is out of bounds, wrap around
        	index = 0;
        }
		if (table[index].getName() == "" ) { // if table[index] is empty, key is not in table
        	return false;
        }
	}
    return table[index].getName() == data.getName();
}

// not really needed, could be removed anytime !!!!!!!!!!!!!!!!!!!!!!!!!!!
void HashTable::remove(DataHolder data) {
    
    int index = hashFunction(data.getName());
    table[index].setName("");
    table[index].setVisit(0);
    count -= 1;
}

// need to change this function to show only the top 10 most visited files !!!!!!!!!!!!!!!!!!!!!!!!!!!!
void HashTable::printTop10() {
    // visit every element in the table
    DataHolder* top10 = new DataHolder[10];
    for (int i = 0; i < 10; i++) {
        top10[i] = DataHolder();
    }
    for (int i = 0; i < size; i++) {
        if (table[i].getName() == "") {
            // if empty do nothing
        }
        else {
            // check for each element in top10 that current elements visit amount is higher than that element
            for (int j = 0; j < 10; j++) {
                if (table[i].getVisit() > top10[j].getVisit()) {
					// if it is, shift the elements in top10 down by 1 and insert current element into top10
                    for (int k = 9; k > j; k--) {
						top10[k] = top10[k - 1];
					}
					top10[j] = table[i];
					break;
				}
            }
        }
    }
    cout << "Top 10 visited sites: " << endl;
    for (int i = 0; i < 10; i++) {
		cout << top10[i].getName() << " - visits: " << top10[i].getVisit() << endl;
	}
}

unordered_map<int, std::pair<int, string>> unOrderedMapInsert(unordered_map<int, std::pair<int, string> > table, DataHolder data, int counter) {
    // first check if data is already in the table
    // if it is, increment the int value by 1
    // if it is not, insert it into the table with int value 1
    for (auto& x : table) {
        if (x.second.second == data.getName()) {
            DataHolder temp = DataHolder(x.second.second, x.second.first+1); // increment visit count
            int key = x.first;
            table.erase(x.first);
            pair<int, string> p = make_pair(temp.getVisit(), temp.getName());
            table.insert({ key, p });
			return table;
		}  
	}
    pair <int, string> p2 = make_pair(1, data.getName());
    table.insert({counter , p2 });
    return table;
}
void unOrderedMapTop10(unordered_map<int, std::pair<int, string> > table) {
	// visit every element in the table
	DataHolder* top10 = new DataHolder[10];
    for (int i = 0; i < 10; i++) {
		top10[i] = DataHolder();
	}
    for (auto& x : table) {
        if (x.second.second == "") {
			// if empty do nothing
		}
        else {
			// check for each element in top10 that current elements visit amount is higher than that element
            for (int j = 0; j < 10; j++) {
                if (x.first > top10[j].getVisit()) {
					// if it is, shift the elements in top10 down by 1 and insert current element into top10
                    for (int k = 9; k > j; k--) {
						top10[k] = top10[k - 1];
					}
					top10[j] = DataHolder(x.second.second, x.second.first);
					break;
				}
			}
		}
	}
	cout << "Top 10 visited sites: " << endl;
    for (int i = 0; i < 10; i++) {
		cout << top10[i].getName() << " - visits: " << top10[i].getVisit() << endl;
	}


}
int main() {
    // start timer1
    auto start = chrono::high_resolution_clock::now();
    // create my hash table
    HashTable hashTable(19999);
    // Read from the text file
    string newLine;
    ifstream logFile("access_log_test.txt");
     // Use a while loop together with the getline() function to read the file line by line
     // Inserting into my hash table.
    while (getline(logFile, newLine)) {  
        // first, check if GET is in the line
        string get = "GET";
        size_t found = newLine.find(get);
        if (found != string::npos) {
            // set up char array to read the line character by character
            char* line = new char[newLine.length() + 1];
            strcpy_s(line,newLine.size()+1, newLine.c_str());
            // read until first dot (.)
            while (*line != '.') {
                line++;
            }
            // read backwards until first space
            while (*line != ' ') {
                line--;
            }
            // read forwards until first space and save it as link
            char* link = new char[newLine.length() + 1];
            int count = 0;
            line++;
            while (*line != ' ' && *line != '\0') {
                link[count] = *line;
				count++;
				line++;
			}
            link--;
            link[count] = '\0';
            string linkString(link);
            // create dataholder object
            DataHolder data(linkString);
            // insert into hashtable
            hashTable.insert(data);
        }
        else
            continue;
    }

     // print top 10 most visited files
     hashTable.printTop10();


    // stop timer1
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Time taken by the actions with hashtable1: " << duration.count() << " microseconds" << endl;
    // FIRST TABLE END !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


    // start timer2
    auto start2 = chrono::high_resolution_clock::now();
    // create unordered map to store file names and their visit count
    unordered_map<int, std::pair<int, string> > hashTable2;

    
    // read from the text file
    string newLine2;
    ifstream logFile2("access_log_test.txt");
    // use a while loop together with the getline() function to read the file line by line
    // inserting into my unordered map
    int hashCounter = 0;
    while (getline(logFile2, newLine2)) {
        // first, check if GET is in the line
		string get = "GET";
		size_t found = newLine2.find(get);
        if (found != string::npos) {
			// get file name after get
			char* line = new char[newLine2.length() + 1];
			strcpy_s(line, newLine2.size() + 1, newLine2.c_str());
			// read until first dot (.)
            while (*line != '.') {
				line++;
			}
			// read backwards until first space
            while (*line != ' ') {
				line--;
			}
			// read forwards until first space and save it as link
			char* link = new char[newLine2.length() + 1];
			int count = 0;
			line++;
            while (*line != ' ' && *line != '\0') {
				link[count] = *line;
				count++;
				line++;
			}
			link--;
			link[count] = '\0';
			string linkString(link);
			// create dataholder object
			DataHolder data(linkString);
			// insert into unordered map
            // hashTable2.insert({ 3, "test3"}); // INSERTION ONLY WORKS IF THE KEY IS NOT ALREADY IN THE TABLE
            hashTable2 = unOrderedMapInsert(hashTable2,data, hashCounter);
            hashCounter++;
		}
		else
			continue;
	}

    // print top 10 most visited files
    unOrderedMapTop10(hashTable2);
    
    auto stop2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(stop2 - start2);
    cout << "Time taken by the actions with hashtable2: " << duration2.count() << " microseconds" << endl;

    

    // SECOND TABLE END !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    return 0;
}