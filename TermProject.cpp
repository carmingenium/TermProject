// TermProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
using namespace std;
#include <unordered_map>
#include <string>
#include <fstream>

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
    void printHashTable();

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
    // while table[index] is not empty ("" and null) keep probing
    while (table[index].getName() != "") { // && table[index] != NULL !!!!!!!!!!!!!!!!!!!!!!!! delete later
        if (table[index].getName() == data.getName()) { // if data is already in table, increment visit count
        	table[index].setVisit(table[index].getVisit() + 1);
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
		if (table[index].getName() == "" ) { // if table[index] is empty, key is not in table // || table[index] == NULL !!!!!!!!!!!!!!!!!!!!! delete later
        	return false;
        }
	}
    return table[index].getName() == data.getName();
}

void HashTable::remove(DataHolder data) {
    int index = hashFunction(data.getName());
    table[index].setName("");
    table[index].setVisit(0);
    count -= 1;
}

void HashTable::printHashTable() {
    for (int i = 0; i < size; i++) {
        cout << i << ": ";
        if (table[i].getName() == "") {
            cout << "EMPTY";
        }
        else {
            cout << table[i].getName() << endl;
            cout << table[i].getVisit() << endl;
        }
        cout << endl;
    }
}

int main() {
    HashTable hashTable(19999);
    // Read from the text file
    string newLine;
    ifstream MyReadFile("access_log");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, newLine)) {  
        // first, check if GET is in the line
        string get = "GET";
        size_t found = newLine.find(get);
        if (found != string::npos) {
            cout << newLine << endl;
            // get file name after get
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

    cout << "done" << endl;
    return 0;
}