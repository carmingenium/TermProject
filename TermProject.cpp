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
    for (int i = 0; i < size; i++) {
        if (table[i].getName() == "") {
            // if empty do nothing
        }
        else {
            cout << table[i].getName() << endl;
            cout << table[i].getVisit() << endl;
        }
        cout << endl;
    }
}

int main() {
    // create my hash table
    HashTable hashTable(19999);
    // Read from the text file
    string newLine;
    ifstream logFile("access_log");
    // Use a while loop together with the getline() function to read the file line by line
    // Inserting into my hash table.
   // while (getline(logFile, newLine)) {  
   //     // first, check if GET is in the line
   //     string get = "GET";
   //     size_t found = newLine.find(get);
   //     if (found != string::npos) {
   //         // get file name after get
   //         char* line = new char[newLine.length() + 1];
   //         strcpy_s(line,newLine.size()+1, newLine.c_str());
   //         // read until first dot (.)
   //         while (*line != '.') {
   //             line++;
   //         }
   //         // read backwards until first space
   //         while (*line != ' ') {
   //             line--;
   //         }
   //         // read forwards until first space and save it as link
   //         char* link = new char[newLine.length() + 1];
   //         int count = 0;
   //         line++;
   //         while (*line != ' ' && *line != '\0') {
   //             link[count] = *line;
			//	count++;
			//	line++;
			//}
   //         link--;
   //         link[count] = '\0';

   //         string linkString(link);
   //         // create dataholder object
   //         DataHolder data(linkString);
   //         // insert into hashtable
   //         hashTable.insert(data);
   //         cout << data.getName() << " - visits: " << data.getVisit() << endl;
   //     }
   //     else
   //         continue;
   // }

    // create unordered map to store file names and their visit count
    unordered_map<int, std::string> hashTable2;

    int itemCounter = 0; // to test if insertion works
    // read from the text file
    string newLine2;
    ifstream logFile2("access_log");
    // use a while loop together with the getline() function to read the file line by line
    // inserting into my unordered map
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
            // check how this works, I might need to change it in a way that it first gets value from hashtable two and then increments it and then puts it back in the hashtable
			hashTable2.insert({ data.getVisit(), data.getName() });
            

		}
		else
			continue;
	}



    cout << "done" << endl;
    return 0;
}