// TermProject.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
using namespace std;

//Task1: You must implement a hash table as your main data structure.You should implement your own hash table, 
//you cannot use a hash table implementation from a library.
//This implementation should be a proper C++ class.
//You should use this hash table for storing the filenames and the corresponding number of visits of that page(filename).
//There is no restriction on the choice of the hash function and collision resolution method.
//
//Task2 : Use std::unordered_map data structure for storing the filenames and the corresponding number of visits.
//Task 3 : In order to compare the efficiency of your own hash table implementation and std::unordered_map, write a program which measures the total time it takes starting from reading access_log file until the end of printing the top 10 most visited pages.There is no need to ask user input.
//Note1 : For finding the top 10 most visited pages try to find an efficient method.Hint : you can use the heap data structures.
//Note2 : Other than the hash table implementation, you can use C++ standard library for your needs.


// Implement a hash table that stores the filenames and the corresponding number of visits of that page(filename).
// to do this, we need two classes: one for the hash table and one for the nodes in the hash table

template <class elemType>
class hashT
{
public:
    void insert(int hashIndex, const elemType& rec);
    //Function to insert an item in the hash table. The first
    //parameter specifies the initial hash index of the item to 
    //be inserted. The item to be inserted is specified by the 
    //parameter rec.
    //Postcondition: If an empty position is found in the hash
    //   table, rec is inserted and the length is incremented by
    //   one; otherwise, an appropriate error message is
    //   displayed.

    void search(int& hashIndex, const elemType& rec, bool& found) const;
    //Function to determine whether the item specified by the
    //parameter rec IS IN!! the hash table. The parameter hashIndex
    //specifies the initial hash index of rec.
    //Postcondition: If rec is found, found is set to true and
    //   hashIndex specifies the position where rec is found;
    //   otherwise, found is set to false.

    bool isItemAtEqual(int hashIndex, const elemType& rec) const;
    //Function to determine whether the item specified by the
    //parameter rec IS THE SAME AS!! the item in the hash table 
    //at position hashIndex.
    //Postcondition: Returns true if HTable[hashIndex] == rec;
    //   otherwise, returns false.

    void retrieve(int hashIndex, elemType& rec) const;
    //Function to retrieve the item at position hashIndex.
    //Postcondition: If the table has an item at position
    //   hashIndex, it is copied into rec.

    void remove(int hashIndex, const elemType& rec);
    //Function to remove an item from the hash table.
    //Postcondition: Given the initial hashIndex, if rec is found
    //   in the table it is removed; otherwise, an appropriate
    //   error message is displayed.

    void print() const;
    //Function to output the data.

    hashT(int size = 101);
    //constructor
    //Postcondition: Create the arrays HTTable and indexStatusList;
    //   initialize the array indexStatusList to 0; length = 0;
    //   HTSize = size; and the default array size is 101.

private:
    elemType* HTable;   //pointer to the hash table
    int* indexStatusList;  //pointer to the array indicating the
    //status of a position in the hash table
    int length;    //number of items in the hash table
    int HTSize;    //maximum size of the hash table
};


int main()
{
    std::cout << "Hello World!\n";
}