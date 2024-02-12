// File Name: PA2.cpp
//
// Author: Elliot Sonoqui
// Collaborators: None
// Date: 2/7/2024
// Assignment Number: 2
// CS 2308 Spring 2024
//
// This program will allow a user to access the results from a time-trial 
//bike race.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


struct Result {
    int bibNumber;
    string name;
    double distance;
    string time;
};

void readDataset(ifstream& in, Result results[], int &size); 
void displayDataset(Result results[], int size);
int linearSearchByName(Result results[], int size, string targetName);
int binarySearchByNumber(Result results[], int size, int targetNumber);
void sortByNumber(Result results[], int size);
void sortByDistanceTime(Result results[], int size);


//***********************************************************
// displayHeader: outputs the header of the display table
//***********************************************************

void displayHeader(){
    cout << "\n"<< left
    << setw(7) << "BibNum"
    << setw(18) << "Name"
    << right
    << setw(8) << "Distance"
    << setw(10) << "Time  "
    << endl;
}

//***********************************************************
// displayMenu: short description of what the function does.
//***********************************************************

void displayMenu(){
    cout << "\nMenu\n\n";
    cout << "1. Display Results sorted by bib number\n";
    cout << "2. Display Results sorted by distance, then time\n";
    cout << "3. Lookup a bib number given a name\n";
    cout << "4. Lookup a result by bib number\n";
    cout << "5. Quit the Program\n\n";
    cout << "Enter your choice: ";
}


int main(){

const int SIZE = 100;
Result results[SIZE] = {
    {10, "John Smith", 122.0, "05:40:52"},
    {20, "Gary Benson", 115.9, "05:50:40"},
    {25, "David Myers", 103.7, "05:53:16"},
};

int size = 0;

string filename;
cout << "Filename: ";
cin >> filename;

ifstream fin(filename);
readDataset(fin, results, size);

int number;
string nameToLookup;

displayMenu();

do{
    cin >> number;

    switch(number){         
        case 1: 
            sortByNumber(results, size);
            displayDataset(results, size);
            displayMenu();
            break;
        case 2:
            sortByDistanceTime(results, size);
            displayDataset(results, size);
            displayMenu();
            break;         
        case 3:
            {cout << "Enter name of a racer to look for: " << endl;
            cin.ignore();
            getline(cin, nameToLookup);
            int racerIndex = linearSearchByName(results, SIZE, nameToLookup);
            if(racerIndex != -1){
                cout << "The number of the racer with name " << nameToLookup 
                << " is: " << results[racerIndex].bibNumber << endl;
                displayMenu();
            }
            else{
                cout << "No racer found with name: " << nameToLookup << endl;
                displayMenu();
            }
            break;}
        case 4:
            {int targetNumber;
            cout << "Enter number of a racer to look for: " << endl;
            cin >> targetNumber;
            int index = binarySearchByNumber(results, size, targetNumber);

            if (index != -1) {
                cout << left
                << setw(7) << results[index].bibNumber
                << setw(18) << results[index].name
                << right
                << setw(8) << results[index].distance
                << setw(10) << results[index].time
                << endl;
            } else {
                cout << "No racer found with number: " << targetNumber << endl;
            }
                displayMenu();
                break;}
        case 5: 
            cout << "Exiting the program..." << endl;
            break;
        default:
            cout << "Please, enter 1, 2, 3, 4 or 5: ";
            break;
        }
}while(number != 5);

return 0;
}

//***********************************************************
// displayDataset: prints results array
//
// Result results[]: this is the array in the struct Result
// int size: takes the size of the array
// returns: a table with the values in Struct 
//***********************************************************

void displayDataset(Result results[], int size) {
    displayHeader();
    for(int i = 0; i < size; i++){
        cout << left
        << setw(7) << results[i].bibNumber
        << setw(18) << results[i].name
        << right
        << fixed << setprecision(1) << setw(8) << results[i].distance
        << setw(10) << results[i].time
        << endl;
    }
};

//***********************************************************
// linearSearchByName: finds the index of a racer's result by their
// name using a linear search.
//
// Result results[]: this is the array in the struct Result
//int SIZE: size of array capacity
//targetName: number to find
// returns: -1 if racer does not exist or returns index
//***********************************************************

int linearSearchByName(Result results[], int SIZE, string targetName) {
    int position = -1;
    for(int i = 0; i < SIZE; i++){
        if(results[i].name == targetName){
            position = i;
        }
        }
    return position;
};

//***********************************************************
// sortByNumber: sorts results by bibNumber field in ascending 
//order using a bubble sort
//
// Result results[]: this is the array in the struct Result
// int SIZE: size of array capacity
//***********************************************************

void sortByNumber(Result results[], int SIZE){
    bool swap;
    Result temp; 
    do{
        swap = false;
        for(int i = 0; i < (SIZE - 1); i++){
            if(results[i].bibNumber > results[i+1].bibNumber){
                temp = results[i];
                results[i] = results[i+1];
                results[i+1] = temp;
                swap = true;
            }
        }
    }while(swap);
};

//***********************************************************
// readDataset: read results into results array from the "in" 
//file stream (opened in main). Updates size
//
// ifsream& in: 
// Result results[]: this is the array in the struct Result
// int &size: takes the size of the array
//***********************************************************

void readDataset(ifstream& in, Result results[], int &size){
    while (in >> results[size].bibNumber >> ws) {
        getline(in >> ws, results[size].name);
        in >> results[size].distance >> results[size].time;
        size++;
    }
};

//***********************************************************
// sortByDistanceTime: orders the racer results by distance
//than time using selection sort algorithm
//
// Result results[]: this is the array in the struct Result
// int SIZE: size of array capacity
//***********************************************************

void sortByDistanceTime(Result results[], int SIZE) {
    for (int i = 0; i < SIZE - 1; i++) {
        int smallestIndex = i;
        for (int j = i + 1; j < SIZE; j++) {
            if (results[j].distance > results[smallestIndex].distance ||
                (results[j].distance == results[smallestIndex].distance &&
                 results[j].time < results[smallestIndex].time)) {
                smallestIndex = j;
            }
        }
        if (smallestIndex != i) {
            Result temp = results[i];
            results[i] = results[smallestIndex];
            results[smallestIndex] = temp;
        }
    }
};

//***********************************************************
// binarySearchByNumber: short description of what the function does.
//
// Result results[]: this is the array in the struct Result
// int size: takes the size of the array
// targetNumber: number to search for in array
// returns: the index of the tagret number
//***********************************************************

int binarySearchByNumber(Result results[], int size, int targetNumber){
    int first = 0;
    int last = size - 1;
    int middle;

    while(first <= last){
        middle = (first + last) / 2;
        if(results[middle].bibNumber == targetNumber){
            return middle;
        }
        else if(targetNumber < results[middle].bibNumber){
            last = middle - 1;
        }
        else{
            first = middle + 1;
        }
    }
    return -1;
};