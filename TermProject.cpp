// TermProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
using namespace std;

//Task1: You must implement a hash table as your main data structure.You should implement your own hash table, 
//you cannot use a hash table implementation from a library.
//This implementation should be a proper C++ class.
//You should use this hash table for storing the filenames and the corresponding number of visits of that page(filename).
//There is no restriction on the choice of the hash function and collision resolution method.
//
//Task2 : Use unordered_map data structure for storing the filenames and the corresponding number of visits.
//Task 3 : In order to compare the efficiency of your own hash table implementation and unordered_map, write a program which measures the total time it takes starting from reading access_log file until the end of printing the top 10 most visited pages.There is no need to ask user input.
//Note1 : For finding the top 10 most visited pages try to find an efficient method.Hint : you can use the heap data structures.
//Note2 : Other than the hash table implementation, you can use C++ standard library for your needs.


#include <iostream>
#include <unordered_map>
#include <string>

// Define a custom class MyClass
class MyClass {
public:
    int id;
    string name;
    MyClass(int id, string name) : id{ id }, name{ name } {}
};

// Define a struct to represent a hash table entry
struct HashEntry {
    MyClass value;
    HashEntry* next;
};

// Define a class to represent the hash table
class HashMap {
private:
    // Mapping from keys to hash entries
    unordered_map<string, HashEntry*> table;

    // Size of the hash table
    int capacity;

    // Number of elements in the hash table
    int count;

public:
    // Constructor to initialize the hash table with a given capacity
    HashMap(int capacity = 9999) : capacity{ capacity }, count{ 0 } {}

    // Returns true if the key exists in the hash table, false otherwise
    bool containsKey(const string& key);

    // Inserts a new key-value pair into the hash table
    void insert(const string& key, const MyClass& value);

    // Searches for a key in the hash table and returns its associated value
    const MyClass* find(const string& key);

    // Removes a key-value pair from the hash table
    void remove(const string& key);

    // Clears all key-value pairs from the hash table
    void clear();

    // Resizes the hash table to accommodate more elements
    void resize(int newCapacity);

private:
    // Calculates the hash value for a given key
    int hash(const string& key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue += c;
        }
        return hashValue % capacity; // this problem is because of static function, find a workaround the function
    }

    // Retrieves the hash entry for a given key
    HashEntry* getHashEntry(const string& key);

    // Inserts a new hash entry into the hash table
    void insertHashEntry(const string& key, const MyClass& value);

    // Updates the next pointer of a hash entry
    void updateNextPointer(HashEntry* entry, HashEntry* newNext);

    // Removes a hash entry from the hash table
    void removeHashEntry(HashEntry* entry);
};

// Implementation details
bool HashMap::containsKey(const string& key) {
    int hashValue = hash(key);
    HashEntry* entry = table[hashValue];
    while (entry != nullptr) {
        if (entry->value.name == key) {
            return true;
        }
        entry = entry->next;
    }
    return false;
}

void HashMap::insert(const string& key, const MyClass& value) {
    int hashValue = hash(key);
    HashEntry* entry = table[hashValue];
    while (entry != nullptr) {
        if (entry->value.name == key) {
            // Key already exists, just update the value
            entry->value = value;
            return;
        }
        entry = entry->next;
    }
    // No matching key found, create a new hash entry
    HashEntry* newEntry = new HashEntry{ value, nullptr };
    table[hashValue] = newEntry;
    count++;
}

const MyClass* HashMap::find(const string& key) {
    int hashValue = hash(key);
    HashEntry* entry = table[hashValue];
    while (entry != nullptr) {
        if (entry->value.name == key) {
            return &entry->value;
        }
        entry = entry->next;
    }
    return nullptr;
}

void HashMap::remove(const string& key) {
    int hashValue = hash(key);
    HashEntry* entry = table[hashValue];
    HashEntry* previous = nullptr;
    while (entry != nullptr) {
        if (entry->value.name == key) {
            // Remove the entry
            if (previous != nullptr) {
                previous->next = entry->next;
            }
            else {
                table[hashValue] = entry->next;
            }
            delete entry;
            count--;
            return;
        }
        previous = entry;
        entry = entry->next;
    }
}

void HashMap::clear() {
    for (auto& entry : table) {
        while (entry.second != nullptr) {
            HashEntry* temp = entry.second;
            entry.second = entry.second->next;
            delete temp;
        }
    }
    count = 0;
}

void HashMap::resize(int newCapacity) {
    // Save the old table for traversal
    unordered_map<string, HashEntry*> oldTable = table;

    // Reset the table to the new capacity
    table.clear();
    table.rehash(newCapacity);
    capacity = newCapacity;
    count = 0;

    // Rehash all entries from the old table into the new table
    for (auto& entry : oldTable) {
        while (entry.second != nullptr) {
            HashEntry* temp = entry.second;
            entry.second = entry.second->next;
            insertHashEntry(temp->value.name, temp->value);
            delete temp;
        }
    }
}

HashEntry* HashMap::getHashEntry(const string& key) {
    int hashValue = hash(key);
    HashEntry* entry = table[hashValue];
    while (entry != nullptr) {
        if (entry->value.name == key) {
            return entry;
        }
        entry = entry->next;
    }
    return nullptr;
}

void HashMap::insertHashEntry(const string& key, const MyClass& value) {
    int hashValue = hash(key);
    HashEntry* newEntry = new HashEntry{ value, nullptr };
    if (table[hashValue] == nullptr) {
        table[hashValue] = newEntry;
    }
    else {
        HashEntry* entry = table[hashValue];
        while (entry->next != nullptr) {
            entry = entry->next;
        }
        entry->next = newEntry;
    }
    count++;
}

void HashMap::updateNextPointer(HashEntry* entry, HashEntry* newNext) {
    if (entry != nullptr) {
        entry->next = newNext;
    }
}

void HashMap::removeHashEntry(HashEntry* entry) {
    if (entry != nullptr) {
        delete entry;
        count--;
    }
}


int main()
{
    cout << "Hello World!\n";
}